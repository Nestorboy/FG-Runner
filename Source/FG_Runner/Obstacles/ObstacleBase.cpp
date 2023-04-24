// Fill out your copyright notice in the Description page of Project Settings.

#include "ObstacleBase.h"
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
}

void AObstacleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacleBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, __FUNCTION__);
	if (const auto Character = Cast<ARunnerCharacter>(OtherActor))
	{
		Character->Damage(Damage);
	}
}


