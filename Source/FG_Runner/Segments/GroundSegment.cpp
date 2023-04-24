// Fill out your copyright notice in the Description page of Project Settings.

#include "GroundSegment.h"

AGroundSegment::AGroundSegment()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	Mesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
	Mesh->SetupAttachment(RootComponent);
}

void AGroundSegment::BeginPlay()
{
	Super::BeginPlay();
}

void AGroundSegment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGroundSegment::Move(float Distance)
{
	const FVector Offset = FVector(-Distance, 0.0f, 0.0f);
	AddActorWorldOffset(Offset);
}

void AGroundSegment::SetEntryPosition(FVector WorldPosition)
{
	const FVector CenterLocation = GetActorLocation();
	RootComponent->SetWorldLocation(WorldPosition + CenterLocation - EntryPoint);
}

FVector AGroundSegment::GetExitPosition()
{
	const FVector CenterLocation = GetActorLocation();
	return CenterLocation + ExitPoint;
}
