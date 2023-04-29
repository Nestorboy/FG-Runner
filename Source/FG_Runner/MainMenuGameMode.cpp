// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuGameMode.h"

#include "Blueprint/UserWidget.h"

void AMainMenuGameMode::BeginPlay()
{
	if (MainMenuClass)
	{
		if (const auto Widget = CreateWidget(GetWorld(), MainMenuClass))
		{
			Widget->AddToViewport();
		}
	}
}
