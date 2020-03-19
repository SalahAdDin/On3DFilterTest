// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestGameModeBase.generated.h"

UCLASS(minimalapi)
class ATestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATestGameModeBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Players)
	TArray<AActor *> EnemyArray;
};
