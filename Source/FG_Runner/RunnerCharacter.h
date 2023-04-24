// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "RunnerCharacter.generated.h"

class UCameraComponent;

UCLASS()
class FG_RUNNER_API ARunnerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess))
	TObjectPtr<UCameraComponent> PlayerCamera;
	
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess))
	TSoftObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess))
	TObjectPtr<UInputAction> AttackAction;

protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	int MaxHealth = 3;
	
	UPROPERTY(EditAnywhere, Category = Debug, meta = (AllowPrivateAccess), Transient)
	int RemainingHealth;
	
	UPROPERTY(VisibleAnywhere, Category = Debug, BlueprintReadOnly, Transient)
	int LaneCount = 3;
	
	UPROPERTY(VisibleAnywhere, Category = Debug, BlueprintReadOnly, Transient)
	int LaneIndex;
	
	UPROPERTY(VisibleAnywhere, Category = Debug, BlueprintReadOnly, Transient)
	int OldLaneIndex = 0;
	
	UPROPERTY(VisibleAnywhere, Category = Debug, BlueprintReadOnly, Transient)
	bool bIsMoving = false;
	
	UPROPERTY(VisibleAnywhere, Category = Debug, BlueprintReadOnly)
	float MoveDuration = 0.1f;
	
	UPROPERTY(VisibleAnywhere, Category = Debug, BlueprintReadOnly, Transient)
	float MoveTime = 0.0f;
	
public:
	// Sets default values for this character's properties
	ARunnerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BindInputs(UInputComponent* PlayerInputComponent);
	
	virtual void InputJump(const FInputActionInstance& Instance);
	virtual void InputMove(const FInputActionInstance& Instance);
	virtual void InputAttack(const FInputActionInstance& Instance);

	virtual void OnStartMove();
	virtual void OnMove(float DeltaTime);
	virtual void OnEndMove();
};
