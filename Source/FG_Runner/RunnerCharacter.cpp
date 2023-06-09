// Fill out your copyright notice in the Description page of Project Settings.

#include "RunnerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FG_RunnerGameModeBase.h"
#include "RunnerGameState.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Obstacles/ObstacleBase.h"

ARunnerCharacter::ARunnerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	RemainingHealth = MaxHealth;
	LaneIndex = static_cast<float>(LaneCount) * 0.5f - 0.5f;
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	DodgeCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	DodgeCollider->SetupAttachment(RootComponent);
}

void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();
	DodgeCollider->OnComponentEndOverlap.AddDynamic(this, &ARunnerCharacter::EndDodgeOverlap);

	const auto Movement = GetCharacterMovement();
	Movement->bConstrainToPlane = true;
	Movement->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::X);
	
	PlayerCamera->AddWorldTransform(GetActorTransform());

	const float CenterLaneOffset = static_cast<float>(LaneCount) * 0.5f - 0.5f;
	const FVector OldLocation = GetActorLocation();
	const FVector NewLocation = FVector(OldLocation.X, (static_cast<float>(LaneIndex) - CenterLaneOffset) * LaneSpacing, OldLocation.Z);
	SetActorLocation(NewLocation);
}

void ARunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TryMove();
	
	if (bIsMoving)
	{
		if (MoveTime > 0.0f)
		{
			OnMove(DeltaTime);
		}
		else
		{
			OnEndMove();
		}
	}

	if (bIsGracePeriod)
	{
		GraceTime += DeltaTime;
		if (GraceTime >= GraceDuration)
		{
			bIsGracePeriod = false;
			GraceTime = GraceDuration;
		}
	}
}

void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const auto PlayerController = Cast<APlayerController>(Controller);

	if (const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!InputMapping.IsNull())
			{
				InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);
			}
		}
	}
	
	BindInputs(PlayerInputComponent);
}

void ARunnerCharacter::BindInputs(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &ARunnerCharacter::InputJump);
		Input->BindAction(MoveAction, ETriggerEvent::Started, this, &ARunnerCharacter::InputMove);
		Input->BindAction(DropAction, ETriggerEvent::Started, this, &ARunnerCharacter::InputDrop);
		Input->BindAction(AttackAction, ETriggerEvent::Started, this, &ARunnerCharacter::InputAttack);
	}
}

void ARunnerCharacter::InputJump(const FInputActionInstance& Instance)
{
	Super::Jump();
}

void ARunnerCharacter::InputMove(const FInputActionInstance& Instance)
{
	MoveValue = Instance.GetValue().Get<float>();
	bMoveConsumed = false;
}

void ARunnerCharacter::InputDrop(const FInputActionInstance& Instance)
{
	const auto Movement = GetMovementComponent();
	if (!bHasDropped && Movement->Velocity.Z > -1000.0f && Movement->IsFalling())
	{
		bHasDropped = true;
		const FVector DownwardForce {0.0f, 0.0f, -1000.0f};
		Movement->Velocity = DownwardForce;
	}
}

void ARunnerCharacter::Landed(const FHitResult& Hit)
{
	bHasDropped = false;
}


void ARunnerCharacter::InputAttack(const FInputActionInstance& Instance)
{
	
}

void ARunnerCharacter::TryMove()
{
	if (bIsMoving || bMoveConsumed)
	{
		return;
	}
	bMoveConsumed = true;
	
	const bool bMovingLeft = MoveValue < 0.0f;
	if (bMovingLeft)
	{
		if (LaneIndex <= 0)
			return;
	}
	else
	{
		if (LaneIndex >= LaneCount - 1)
			return;
	}
	
	OldLaneIndex = LaneIndex;
	LaneIndex += bMovingLeft ? -1 : 1;
	OnStartMove();
}

void ARunnerCharacter::OnStartMove()
{
	bIsMoving = true;
	MoveTime = MoveDuration;
}

void ARunnerCharacter::OnMove(float DeltaTime)
{
	const float CenterLaneOffset = static_cast<float>(LaneCount) * 0.5f - 0.5f;
	const FVector OldLocation = GetActorLocation();
	const float Alpha = FMath::SmoothStep(0.0f, 1.0f, 1.0f - MoveTime / MoveDuration);
	const FVector NewLocation = FVector(OldLocation.X, (FMath::Lerp(static_cast<float>(OldLaneIndex), static_cast<float>(LaneIndex), Alpha) - CenterLaneOffset) * LaneSpacing, OldLocation.Z);
	SetActorLocation(NewLocation);
	
	MoveTime -= DeltaTime;
}

void ARunnerCharacter::OnEndMove()
{
	const float CenterLaneOffset = static_cast<float>(LaneCount) * 0.5f - 0.5f;
	const FVector OldLocation = GetActorLocation();
	const FVector NewLocation = FVector(OldLocation.X, (static_cast<float>(LaneIndex) - CenterLaneOffset) * LaneSpacing, OldLocation.Z);
	SetActorLocation(NewLocation);
	
	bIsMoving = false;
}

void ARunnerCharacter::EndDodgeOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (bIsGracePeriod || !OtherActor->IsA(AObstacleBase::StaticClass()))
	{
		return;
	}

	OnCloseCall();
}

void ARunnerCharacter::OnCloseCall()
{
	DodgedObstacles++;
	if (FMath::FRand() < 0.25f)
	{
		if (const auto RunnerGameMode = Cast<AFG_RunnerGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			if (const auto SegmentManager = RunnerGameMode->SegmentManager)
			{
				SegmentManager->ObstaclesToRemove++;
			}
		}
	}
}

void ARunnerCharacter::Damage(int Value)
{
	if (bIsGracePeriod || bHasLost)
	{
		return;
	}
	
	RemainingHealth -= Value;
	if (RemainingHealth <= 0)
	{
		bHasLost = true;
		OnGameOver();
	}
	else
	{
		bIsGracePeriod = true;
		GraceTime = 0.0f;
	}
}

void ARunnerCharacter::OnGameOver()
{
	const auto GameState = Cast<ARunnerGameState>(GetWorld()->GetAuthGameMode()->GameState);
	GameState->WriteSaveGame();
	// TODO: GameOver -> Delay -> Lost Menu -> Retry Button -> Restart
	if (GameOverMenuWidget)
	{
		if (const auto Widget = CreateWidget(GetWorld(), GameOverMenuWidget))
		{
			Widget->AddToViewport();
		}
	}
	else
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("RestartLevel"));
	}
}



