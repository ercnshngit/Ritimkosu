// Fill out your copyright notice in the Description page of Project Settings.


#include "RitimTile.h"

// Sets default values
ARitimTile::ARitimTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RitimMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RitimMesh"));
	check(RitimMesh != nullptr);

	RitimMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARitimTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARitimTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARitimTile::ActivateTile() 
{
	ActivateTileBP();
}

void ARitimTile::DeactivateTile() 
{
	DeactivateTileBP();
}

