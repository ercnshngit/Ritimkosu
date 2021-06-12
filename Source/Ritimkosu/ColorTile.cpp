// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorTile.h"

// Sets default values
AColorTile::AColorTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	check(TileMesh != nullptr);

	TileMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AColorTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AColorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

