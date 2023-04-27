// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHUD.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UGameHUD::NativeConstruct()
{
	if (PauseButton)
	{
		PauseButton->OnClicked.AddDynamic(this, &UGameHUD::OnPauseClicked);
	}
	
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
}

void UGameHUD::OnPauseClicked()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	
	if (const auto Widget = CreateWidget(GetWorld(), PauseMenuWidget))
	{
		Widget->AddToViewport();
	}
}