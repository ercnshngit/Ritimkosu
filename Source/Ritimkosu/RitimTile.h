// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RitimTile.generated.h"

UCLASS()
class RITIMKOSU_API ARitimTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARitimTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* RitimMesh;

	UFUNCTION()
	void ActivateTile();

	UFUNCTION(BlueprintImplementableEvent)
	void ActivateTileBP();

	UFUNCTION()
	void DeactivateTile();

	UFUNCTION(BlueprintImplementableEvent)
	void DeactivateTileBP();




};
