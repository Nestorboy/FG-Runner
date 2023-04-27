// Fill out your copyright notice in the Description page of Project Settings.

#include "PauseMenu.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UPauseMenu::NativeConstruct()
{
	#define BindButton(button, function) if (button) button->OnClicked.AddDynamic(this, function)
	BindButton(ContinueButton, &UPauseMenu::OnContinueClicked);
	BindButton(SettingsButton, &UPauseMenu::OnSettingsClicked);
	BindButton(RetryButton, &UPauseMenu::OnRetryClicked);
	BindButton(MainMenuButton, &UPauseMenu::OnMainMenuClicked);
}

void UPauseMenu::OnContinueClicked()
{
	// TODO: Add countdown.
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	RemoveFromParent();
}

void UPauseMenu::OnSettingsClicked()
{
	
}

void UPauseMenu::OnRetryClicked()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("RestartLevel"));
}

void UPauseMenu::OnMainMenuClicked()
{
	
}
