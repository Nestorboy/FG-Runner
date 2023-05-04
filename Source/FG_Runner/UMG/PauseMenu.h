// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PauseMenu.generated.h"

UCLASS()
class FG_RUNNER_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ContinueButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> RetryButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> SettingsButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> MainMenuButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> MainMenuLevel;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OnContinueClicked();
	UFUNCTION()
	virtual void OnSettingsClicked();
	UFUNCTION()
	virtual void OnRetryClicked();
	UFUNCTION()
	virtual void OnMainMenuClicked();
};
