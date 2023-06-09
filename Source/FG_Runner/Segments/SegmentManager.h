// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GroundSegment.h"
#include "GameFramework/Actor.h"
#include "SegmentManager.generated.h"

UCLASS()
class FG_RUNNER_API ASegmentManager : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Transient)
	float MovedDistance;

	UPROPERTY(EditAnywhere, Category = Debug, BlueprintReadWrite, Transient)
	int ObstaclesToRemove;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PrewarmDistance = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "The speed of the segments in meters per second."))
	float SegmentSpeed = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SegmentMaxSpeed = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SegmentLength = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SegmentAcceleration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AGroundSegment> InitialSegment;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AGroundSegment>> SegmentBlueprints;

	UPROPERTY(VisibleAnywhere, Category = Debug, BlueprintReadWrite, Transient)
	TArray<TObjectPtr<AGroundSegment>> GroundSegments;
	
	UPROPERTY(VisibleAnywhere, Category = Debug, BlueprintReadWrite, Transient)
	int SegmentCurrentIndex;

	UPROPERTY(VisibleAnywhere, Category = Debug, BlueprintReadWrite, Transient)
	int SegmentBufferSize;
	
public:	
	ASegmentManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void UpdateSegments(float DeltaTime);

	virtual void MoveSegments(float DeltaTime);
	
	virtual void AddSegments();
	
	virtual void DeleteSegments();
};
