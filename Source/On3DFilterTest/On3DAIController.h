// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "On3DAIController.generated.h"

/**
 * 
 */
UCLASS()
class ON3DFILTERTEST_API AOn3DAIController : public AAIController
{
	GENERATED_BODY()

public:

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Blackboard")
	void UpdateBlackboardEnemyKey(AActor* Actor, FAIStimulus Stimulus);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UAIPerceptionComponent* AIPerception;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blackboard")
	UBlackboardComponent* BlackboardComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
	UBlackboardData* BlackboardDataToUse;
	
	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
	UBehaviorTree* BehaviorTreeToUse;
	
};