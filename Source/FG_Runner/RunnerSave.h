// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RunnerSave.generated.h"

UCLASS()
class FG_RUNNER_API URunnerSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<float> HighestScores;
};
