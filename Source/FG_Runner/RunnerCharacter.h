// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Components/Button.h"
#include "GameFramework/Character.h"
#include "RunnerCharacter.generated.h"

class UCameraComponent;

UCLASS()
class FG_RUNNER_API ARunnerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> PlayerCamera;
	
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> DropAction;
	
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> AttackAction;

public:
	UPROPERTY(EditAnywhere)
	float LaneSpacing = 150.0f;
	
	UPROPERTY(EditAnywhere)
	int LaneCount = 3;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MoveDuration = 0.1f;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	int MaxHealth = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float GraceDuration = 2.0f;


	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UMG)
	TSubclassOf<UUserWidget> GameOverMenuWidget;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UUserWidget> GameOverMenu;
	
	UPROPERTY(EditAnywhere, Category = Debug, meta = (AllowPrivateAccess), Transient)
	int RemainingHealth;

	UPROPERTY(EditAnywhere, Category = Debug, meta = (AllowPrivateAccess), Transient)
	bool bHasLost;
	
	UPROPERTY(VisibleAnywhere, Category = Debug, BlueprintReadOnly, Transient)
	int LaneIndex;
	
	UPROPERTY(VisibleAnywhere, Category = Debug, BlueprintReadOnly, Transient)
	int OldLaneIndex = 0;
	
	UPROPERTY(VisibleAnywhere, Category = Debug, BlueprintReadOnly, Transient)
	float MoveValue = 0.0f;
	
	UPROPERTY(VisibleAnywhere, Category = Debug, BlueprintReadOnly, Transient)
	bool bMoveConsumed = true;
	
	UPROPERTY(VisibleAnywhere, Category = Debug, BlueprintReadOnly, Transient)
	bool bIsMoving = false;

	UPROPERTY(VisibleAnywhere, Category = Debug, BlueprintReadOnly, Transient)
	bool bHasDropped = false;

	UPROPERTY(VisibleAnywhere, Category = Debug, BlueprintReadOnly, Transient)
	bool bIsGracePeriod = false;
	
	UPROPERTY(VisibleAnywhere, Category = Debug, BlueprintReadOnly, Transient)
	float MoveTime = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = Debug, BlueprintReadOnly, Transient)
	float GraceTime = 0.0f;
	
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
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BindInputs(UInputComponent* PlayerInputComponent);
	
	virtual void InputJump(const FInputActionInstance& Instance);
	virtual void InputMove(const FInputActionInstance& Instance);
	virtual void InputDrop(const FInputActionInstance& Instance);
	virtual void InputAttack(const FInputActionInstance& Instance);

	virtual void TryMove();
	virtual void OnStartMove();
	virtual void OnMove(float DeltaTime);
	virtual void OnEndMove();

	virtual void Landed(const FHitResult& Hit) override;
	
	virtual void Damage(int Value);

	UFUNCTION(CallInEditor, Category = Debug)
	virtual void OnGameOver();
};
