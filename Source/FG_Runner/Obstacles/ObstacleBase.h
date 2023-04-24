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
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	int Damage = 1;

protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
public:	
	AObstacleBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
