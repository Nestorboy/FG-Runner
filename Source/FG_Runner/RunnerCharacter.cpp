// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"

// Sets default values
ARunnerCharacter::ARunnerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
}

// Called when the game starts or when spawned
void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("BeginPlay()"));
	}

	PlayerCamera->AddWorldTransform(GetActorTransform());
	
	auto PlayerController = Cast<APlayerController>(Controller);

	if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
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

// Called every frame
void ARunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	BindInputs(PlayerInputComponent);
}

void ARunnerCharacter::BindInputs(UInputComponent* PlayerInputComponent)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("BindInputs()"));
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ARunnerCharacter::InputJump);
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARunnerCharacter::InputMove);
		Input->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ARunnerCharacter::InputAttack);
	}
}

void ARunnerCharacter::InputJump(const FInputActionInstance& Instance)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(321, 5.0f, FColor::Magenta, TEXT("InputJump()"));
	}
}

void ARunnerCharacter::InputMove(const FInputActionInstance& Instance)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(4321, 5.0f, FColor::Magenta, TEXT("InputMove()"));
	}
}

void ARunnerCharacter::InputAttack(const FInputActionInstance& Instance)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(54321, 5.0f, FColor::Magenta, TEXT("InputAttack()"));
	}
}



