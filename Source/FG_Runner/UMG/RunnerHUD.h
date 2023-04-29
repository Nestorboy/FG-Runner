// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RunnerHUD.generated.h"

UCLASS()
class FG_RUNNER_API ARunnerHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = UMG)
	TSubclassOf<UUserWidget> GameHUDClass;

	UPROPERTY(VisibleInstanceOnly, Category = Runtime)
	TObjectPtr<ARunnerHUD> GameHUD;
	
	virtual void BeginPlay() override;
};
