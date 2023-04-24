// Fill out your copyright notice in the Description page of Project Settings.

#include "RunnerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

ARunnerCharacter::ARunnerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	RemainingHealth = MaxHealth;
	LaneIndex = static_cast<float>(LaneCount) * 0.5f - 0.5f;
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
}

void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("BeginPlay()"));
	
	const auto Movement = GetCharacterMovement();
	Movement->bConstrainToPlane = true;
	Movement->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::X);
	
	PlayerCamera->AddWorldTransform(GetActorTransform());

	const float CenterLaneOffset = static_cast<float>(LaneCount) * 0.5f - 0.5f;
	const FVector OldLocation = GetActorLocation();
	const FVector NewLocation = FVector(OldLocation.X, (static_cast<float>(LaneIndex) - CenterLaneOffset) * LaneSpacing, OldLocation.Z);
	SetActorLocation(NewLocation);

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
}

void ARunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
}

void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	BindInputs(PlayerInputComponent);
}

void ARunnerCharacter::BindInputs(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &ARunnerCharacter::InputJump);
		Input->BindAction(MoveAction, ETriggerEvent::Started, this, &ARunnerCharacter::InputMove);
		Input->BindAction(AttackAction, ETriggerEvent::Started, this, &ARunnerCharacter::InputAttack);
	}
}

void ARunnerCharacter::InputJump(const FInputActionInstance& Instance)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(321, 5.0f, FColor::Magenta, TEXT("InputJump()"));

	Super::Jump();
}

void ARunnerCharacter::InputMove(const FInputActionInstance& Instance)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(4321, 5.0f, FColor::Magenta, TEXT("InputMove()"));

	if (bIsMoving)
	{
		return;
	}

	const bool bMovingLeft = Instance.GetValue().Get<float>() < 0.0f;
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

void ARunnerCharacter::InputAttack(const FInputActionInstance& Instance)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(54321, 5.0f, FColor::Magenta, TEXT("InputAttack()"));
}

void ARunnerCharacter::OnStartMove()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("OnStartMove()"));
	
	bIsMoving = true;
	MoveTime = MoveDuration;
}

void ARunnerCharacter::OnMove(float DeltaTime)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("OnMove()"));

	float CenterLaneOffset = static_cast<float>(LaneCount) * 0.5f - 0.5f;
	const FVector OldLocation = GetActorLocation();
	const FVector NewLocation = FVector(OldLocation.X, (FMath::Lerp(static_cast<float>(OldLaneIndex), static_cast<float>(LaneIndex), 1.0f - MoveTime / MoveDuration) - CenterLaneOffset) * LaneSpacing, OldLocation.Z);
	SetActorLocation(NewLocation);
	
	MoveTime -= DeltaTime;
}

void ARunnerCharacter::OnEndMove()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("OnEndMove()"));

	const float CenterLaneOffset = static_cast<float>(LaneCount) * 0.5f - 0.5f;
	const FVector OldLocation = GetActorLocation();
	const FVector NewLocation = FVector(OldLocation.X, (static_cast<float>(LaneIndex) - CenterLaneOffset) * LaneSpacing, OldLocation.Z);
	SetActorLocation(NewLocation);
	
	bIsMoving = false;
}

void ARunnerCharacter::Damage(int Value)
{
	RemainingHealth -= Value;
	if (RemainingHealth <= 0)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("Player Died"));
	}
}



