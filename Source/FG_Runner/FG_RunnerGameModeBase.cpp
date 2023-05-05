// Copyright Epic Games, Inc. All Rights Reserved.


#include "FG_RunnerGameModeBase.h"

void AFG_RunnerGameModeBase::BeginPlay()
{
	SegmentManager = GetWorld()->SpawnActor<ASegmentManager>(SegmentManagerClass);
}
