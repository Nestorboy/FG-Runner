// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleBase.generated.h"

UCLASS()
class FG_RUNNER_API AObstacleBase : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int Damage = 1;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float Probability = 0.65f;

protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bRandomLane = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bRandomAngle = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxAngleOffset = 5.0f;
	
	bool bHasHitPlayer;
	
public:	
	AObstacleBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	virtual void BeginComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
