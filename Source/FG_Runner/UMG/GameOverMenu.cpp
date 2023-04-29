// Fill out your copyright notice in the Description page of Project Settings.

#include "GameOverMenu.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UGameOverMenu::NativeConstruct()
{
	Super::NativeConstruct();

	#define BIND_BUTTON(button, function) if (button) button->OnClicked.AddDynamic(this, function)
	BIND_BUTTON(ScoreButton, &UGameOverMenu::OnScoreClicked);
	BIND_BUTTON(RetryButton, &UGameOverMenu::OnRetryClicked);
	BIND_BUTTON(SettingsButton, &UGameOverMenu::OnSettingsClicked);
	BIND_BUTTON(MainMenuButton, &UGameOverMenu::OnMainMenuClicked);

	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
}

void UGameOverMenu::OnScoreClicked()
{

}

void UGameOverMenu::OnRetryClicked()
{
	if (const auto World = GetWorld())
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("RestartLevel"));
	}
}

void UGameOverMenu::OnSettingsClicked()
{
	
}

void UGameOverMenu::OnMainMenuClicked()
{
	if (const auto World = GetWorld())
	{
		UGameplayStatics::OpenLevel(World, TEXT("L_MainMenu"));
	}
}