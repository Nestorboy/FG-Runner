// Fill out your copyright notice in the Description page of Project Settings.

#include "ObstacleBase.h"

#include "EngineUtils.h"
#include "FG_Runner/RunnerCharacter.h"

AObstacleBase::AObstacleBase()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	Mesh->SetupAttachment(RootComponent);
}

void AObstacleBase::BeginPlay()
{
	Super::BeginPlay();
	if (FMath::FRandRange(0.0f, 1.0f) > Probability)
	{
		SetActorEnableCollision(false);
		Mesh->SetVisibility(false, true);
		return;
	}
	
	const ARunnerCharacter* Character = nullptr;
	for (TActorIterator<ARunnerCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Character = Cast<ARunnerCharacter>(*ActorItr);
	}

	if (Character == nullptr)
	{
		return;
	}

	const int LaneIndex = FMath::Rand() % Character->LaneCount; // Is there an easier way to get a random integer?
	const float CenterLaneOffset = static_cast<float>(Character->LaneCount) * 0.5f - 0.5f;
	const FVector OldPosition = GetActorLocation();
	SetActorLocation(FVector(OldPosition.X, (static_cast<float>(LaneIndex) - CenterLaneOffset) * Character->LaneSpacing, OldPosition.Z));

	AddActorWorldRotation(FRotator(0.0f, FMath::FRandRange(-MaxAngleOffset, MaxAngleOffset), 0.0f));
}

void AObstacleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacleBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, __FUNCTION__);
	if (!bHasHitPlayer)
	{
		if (const auto Character = Cast<ARunnerCharacter>(OtherActor))
		{
			bHasHitPlayer = true;
			Character->Damage(Damage);
		}
	}
}


