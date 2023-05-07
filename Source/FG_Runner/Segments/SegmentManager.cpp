// Fill out your copyright notice in the Description page of Project Settings.

#include "SegmentManager.h"

#include "FG_Runner/RunnerGameState.h"

ASegmentManager::ASegmentManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASegmentManager::BeginPlay()
{
	Super::BeginPlay();
	//const float SegmentLength = SegmentBlueprint.GetDefaultObject()->SegmentLength;
	if (SegmentLength <= 0.0f)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Segment length."));
		return;
	}

	const float DistanceAhead = PrewarmDistance;
	const float DistanceBehind = 1000.0f;
	const int MaxSegments = FMath::CeilToInt(FMath::Max(2.0f, (DistanceAhead + DistanceBehind) / SegmentLength));
	GroundSegments.Init(nullptr, MaxSegments);

	TSubclassOf<AGroundSegment> InitSegment;
	if (InitialSegment)
	{
		InitSegment = InitialSegment;
	}
	else
	{
		const int RandomIndex = FMath::Rand() % SegmentBlueprints.Num();
		InitSegment = SegmentBlueprints[RandomIndex];
		if (!InitSegment)
		{
			UE_LOG(LogTemp, Error, TEXT("No valid initial Segment found."));
			return;
		}
		
		UE_LOG(LogTemp, Warning, TEXT("InitialSegment is missing."));
	}
	
	const auto NewSegment = GetWorld()->SpawnActor<AGroundSegment>(InitSegment);
	GroundSegments[0] = NewSegment;
	SegmentBufferSize++;
}

void ASegmentManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateSegments(DeltaTime);
}

void ASegmentManager::UpdateSegments(float DeltaTime)
{
	MoveSegments(DeltaTime);
	AddSegments();
	DeleteSegments();
}

void ASegmentManager::MoveSegments(float DeltaTime)
{
	SegmentSpeed = SegmentSpeed >= SegmentMaxSpeed ? SegmentMaxSpeed : SegmentSpeed + SegmentAcceleration * DeltaTime;
	const float SegmentMoveDistance = SegmentSpeed * DeltaTime * 100.0f;
	MovedDistance += SegmentMoveDistance;
	Cast<ARunnerGameState>(GetWorld()->GetGameState())->SetScore(MovedDistance); // Should probably be cached.
	for (int i = 0; i < SegmentBufferSize; i++)
	{
		const int BufferIndex = (SegmentCurrentIndex + i) % GroundSegments.Num();
		GroundSegments[BufferIndex]->Move(SegmentMoveDistance);
	}
}

void ASegmentManager::AddSegments()
{
	int LastIndex = (SegmentCurrentIndex + SegmentBufferSize - 1) % GroundSegments.Num();
	auto LastSegment = GroundSegments[LastIndex];
	FVector LastExit = LastSegment->GetExitPosition();
	while (SegmentBufferSize < GroundSegments.Num() && LastExit.X < PrewarmDistance)
	{
		const int RandomIndex = FMath::Rand() % SegmentBlueprints.Num();
		const auto NewSegment = GetWorld()->SpawnActor<AGroundSegment>(SegmentBlueprints[RandomIndex], FVector(10000.0f, 0.0f, 0.0f), FRotator::ZeroRotator);
		NewSegment->SetEntryPosition(LastExit);
		LastIndex = (LastIndex + 1) % GroundSegments.Num();
		GroundSegments[LastIndex] = NewSegment;
		LastSegment = NewSegment;
		LastExit = NewSegment->GetExitPosition();

		if (ObstaclesToRemove > 0)
		{
			ObstaclesToRemove--;
			NewSegment->DestroyObstacles();
		}
		
		SegmentBufferSize++;
	}
}

void ASegmentManager::DeleteSegments()
{
	int FirstIndex = SegmentCurrentIndex;
	auto FirstSegment = GroundSegments[FirstIndex];
	FVector FirstExit = FirstSegment->GetExitPosition();
	while (SegmentBufferSize >= 0 && FirstExit.X < -1000.0f)
	{
		FirstSegment->Destroy();
		FirstIndex = ++FirstIndex % GroundSegments.Num();
		FirstSegment = GroundSegments[FirstIndex];
		FirstExit = FirstSegment->GetExitPosition();

		SegmentCurrentIndex = (SegmentCurrentIndex + 1) % GroundSegments.Num();
		SegmentBufferSize--;
	}
}

