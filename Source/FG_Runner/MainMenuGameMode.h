// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

UCLASS()
class FG_RUNNER_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = UMG)
	TSubclassOf<UUserWidget> MainMenuClass;

	UPROPERTY(VisibleInstanceOnly, Category = Runtime)
	TObjectPtr<UUserWidget> MainMenu;
	
	virtual void BeginPlay() override;
};
