// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RitimkosuGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RITIMKOSU_API ARitimkosuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death")
	bool bIsPlayerDeadRecently = false;

};
