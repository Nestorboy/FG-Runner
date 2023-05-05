// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RunnerSave.h"
#include "GameFramework/GameStateBase.h"
#include "RunnerGameState.generated.h"

UCLASS()
class FG_RUNNER_API ARunnerGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Transient)
	TArray<float> HighScores;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Transient)
	float Score;
	
	UPROPERTY()
	TObjectPtr<URunnerSave> HighScoreSave;
	
public:
	UFUNCTION()
	virtual void SetScore(float Value);
	
	UFUNCTION()
	virtual void WriteSaveGame();

	UFUNCTION()
	virtual void ReadSaveGame();
	
protected:
	virtual void BeginPlay() override;
};
