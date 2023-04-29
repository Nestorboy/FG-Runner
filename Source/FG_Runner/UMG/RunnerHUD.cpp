// Fill out your copyright notice in the Description page of Project Settings.

#include "RunnerHUD.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ARunnerHUD::BeginPlay()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	if (const auto Widget = CreateWidget(GetOwningPlayerController(), GameHUDClass))
	{
		GameHUD = Cast<ARunnerHUD>(Widget);
		Widget->AddToViewport();
	}
}
