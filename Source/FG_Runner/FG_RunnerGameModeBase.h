// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Segments/SegmentManager.h"
#include "FG_RunnerGameModeBase.generated.h"

UCLASS()
class FG_RUNNER_API AFG_RunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ASegmentManager> SegmentManager;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ASegmentManager> SegmentManagerClass;
	
	virtual void BeginPlay() override;
};
