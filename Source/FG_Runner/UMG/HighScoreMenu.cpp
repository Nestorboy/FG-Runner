// Fill out your copyright notice in the Description page of Project Settings.

#include "HighScoreMenu.h"

#include "FG_Runner/RunnerGameState.h"

void UHighScoreMenu::NativeConstruct()
{
	const auto GameState = Cast<ARunnerGameState>(GetWorld()->GetGameState());
	GameState->ReadSaveGame();
	const TArray<float> HighScores = GameState->HighScores;
	int ScoreIndex = 0;
	for (int TextIndex = 0; TextIndex < 5; TextIndex++)
	{
		// wtf?
		UTextBlock* Text;
		switch (TextIndex)
		{
		case 0:
			Text = ScoreText0;
			break;
		case 1:
			Text = ScoreText1;
			break;
		case 2:
			Text = ScoreText2;
			break;
		case 3:
			Text = ScoreText3;
			break;
		case 4:
			Text = ScoreText4;
			break;
		default:
			Text = nullptr;
			break;
		}
		if (Text)
		{
			if (ScoreIndex >= HighScores.Num())
			{
				Text->SetText(FText::FromString(TEXT("")));
				continue;
			}
			
			const auto Score = FMath::FloorToInt(HighScores[HighScores.Num() - ScoreIndex - 1]);
			Text->SetText(FText::FromString(FString::FromInt(Score)));
			ScoreIndex++;
		}
	}
}


