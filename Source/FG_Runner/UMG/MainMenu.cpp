// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	#define BIND_BUTTON(button, function) if (button) button->OnClicked.AddDynamic(this, function)
	BIND_BUTTON(StartButton, &UMainMenu::OnStartClicked);
	BIND_BUTTON(ScoreButton, &UMainMenu::OnScoreClicked);
	BIND_BUTTON(SettingsButton, &UMainMenu::OnSettingsClicked);
	BIND_BUTTON(QuitButton, &UMainMenu::OnQuitClicked);
}

void UMainMenu::OnStartClicked()
{
	if (const auto World = GetWorld())
	{
		UGameplayStatics::OpenLevel(World, TEXT("L_MainLevel"));
	}
}

void UMainMenu::OnScoreClicked()
{
	
}

void UMainMenu::OnSettingsClicked()
{
	
}

void UMainMenu::OnQuitClicked()
{
	if (const auto World = GetWorld())
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("Quit"));
	}
}
