// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "GameHUD.generated.h"

UCLASS()
class FG_RUNNER_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Score Text

	// Health

	// Distance progress

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UMG)
	TSubclassOf<UUserWidget> PauseMenuWidget;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> PauseButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OnPauseClicked();
};