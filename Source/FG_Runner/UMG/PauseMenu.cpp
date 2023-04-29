// Fill out your copyright notice in the Description page of Project Settings.

#include "PauseMenu.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	#define BIND_BUTTON(button, function) if (button) button->OnClicked.AddDynamic(this, function)
	BIND_BUTTON(ContinueButton, &UPauseMenu::OnContinueClicked);
	BIND_BUTTON(SettingsButton, &UPauseMenu::OnSettingsClicked);
	BIND_BUTTON(RetryButton, &UPauseMenu::OnRetryClicked);
	BIND_BUTTON(MainMenuButton, &UPauseMenu::OnMainMenuClicked);
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
	if (const auto World = GetWorld())
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("RestartLevel"));
	}
}

void UPauseMenu::OnMainMenuClicked()
{
	if (const auto World = GetWorld())
	{
		UGameplayStatics::OpenLevel(World, TEXT("L_MainMenu"));
	}
}
