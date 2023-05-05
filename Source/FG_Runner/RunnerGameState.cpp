// Fill out your copyright notice in the Description page of Project Settings.

#include "RunnerGameState.h"

#include "Kismet/GameplayStatics.h"

#define SAVE_NAME TEXT("HighScoreSave")
#define SAVE_ID 0

void ARunnerGameState::SetScore(float Value)
{
	Score = Value / 1000.0f;
}

void ARunnerGameState::WriteSaveGame()
{
	if (!(HighScores.IsEmpty() || Score > HighScores[HighScores.Num() - 1]))
	{
		return;
	}
	
	HighScores.Add(Score); // Append value since the order is ascending.
	
	const auto SaveGame = Cast<URunnerSave>(UGameplayStatics::CreateSaveGameObject(URunnerSave::StaticClass()));
	SaveGame->HighestScores = HighScores;
	UGameplayStatics::SaveGameToSlot(SaveGame, SAVE_NAME, SAVE_ID);
}

void ARunnerGameState::ReadSaveGame()
{
	if (!UGameplayStatics::DoesSaveGameExist(SAVE_NAME, 0))
	{
		return;
	}
	
	HighScoreSave = Cast<URunnerSave>(UGameplayStatics::LoadGameFromSlot(SAVE_NAME, SAVE_ID));
	if (HighScoreSave)
	{
		HighScores = HighScoreSave->HighestScores;
		HighScores.Sort(); // Sort after read in case of offline manipulation.
	}
}

void ARunnerGameState::BeginPlay()
{
	ReadSaveGame();
}
