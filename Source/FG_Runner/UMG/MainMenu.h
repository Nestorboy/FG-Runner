// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenu.generated.h"

UCLASS()
class FG_RUNNER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> StartButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ScoreButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> SettingsButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> QuitButton;
	
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	virtual void OnStartClicked();
	UFUNCTION()
	virtual void OnScoreClicked();
	UFUNCTION()
	virtual void OnSettingsClicked();
	UFUNCTION()
	virtual void OnQuitClicked();
};
