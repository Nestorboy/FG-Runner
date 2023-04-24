// Fill out your copyright notice in the Description page of Project Settings.

#include "SegmentManager.h"

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

	const auto NewSegment = GetWorld()->SpawnActor<AGroundSegment>(SegmentBlueprint);
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
	for (int i = 0; i < SegmentBufferSize; i++)
	{
		const int BufferIndex = (SegmentCurrentIndex + i) % GroundSegments.Max();
		GroundSegments[BufferIndex]->Move(SegmentSpeed * DeltaTime * 100.0f);
	}
}

void ASegmentManager::AddSegments()
{
	int LastIndex = (SegmentCurrentIndex + SegmentBufferSize - 1) % GroundSegments.Max();
	auto LastSegment = GroundSegments[LastIndex];
	FVector LastExit = LastSegment->GetExitPosition();
	while (SegmentBufferSize < GroundSegments.Max() && LastExit.X < PrewarmDistance)
	{
		const auto NewSegment = GetWorld()->SpawnActor<AGroundSegment>(SegmentBlueprint, FVector(10000.0f, 0.0f, 0.0f), FRotator::ZeroRotator);
		NewSegment->SetEntryPosition(LastExit);
		LastIndex = (LastIndex + 1) % GroundSegments.Max();
		GroundSegments[LastIndex] = NewSegment;
		LastSegment = NewSegment;
		LastExit = NewSegment->GetExitPosition();
		
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
		FirstIndex = ++FirstIndex % GroundSegments.Max();
		FirstSegment = GroundSegments[FirstIndex];
		FirstExit = FirstSegment->GetExitPosition();

		SegmentCurrentIndex = (SegmentCurrentIndex + 1) % GroundSegments.Max();
		SegmentBufferSize--;
	}
}

