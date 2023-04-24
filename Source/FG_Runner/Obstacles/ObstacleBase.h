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
	
public:	
	AObstacleBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
