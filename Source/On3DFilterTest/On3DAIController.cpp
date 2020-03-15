// Fill out your copyright notice in the Description page of Project Settings.


#include "On3DAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Perception/AIPerceptionComponent.h"

AOn3DAIController::AOn3DAIController()
{
    AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));;
}

void AOn3DAIController::BeginPlay(){
    Super::BeginPlay();

    UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
    if (!ensure(BlackboardDataToUse)) { return; }
	UseBlackboard(BlackboardDataToUse, BlackboardComponent);
	if (!ensure(BehaviorTreeToUse)) { return; }

	RunBehaviorTree(BehaviorTreeToUse);
}

void AOn3DAIController::UpdateBlackboardEnemyKey(AActor* Actor, FAIStimulus Stimulus){
    
    bool bIsEnemy = Actor->ActorHasTag(FName("Enemy"));
    bool bIsSuccessfullySensed = Stimulus.WasSuccessfullySensed();
    // bool bIsSuccessfullySensed = Stimulus->WasSuccessfullySensed();
    UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

    if(Actor){

        if (!bIsEnemy)
            if (bIsSuccessfullySensed)
                BlackboardComponent->SetValueAsObject(FName("Enemy"), Actor);
            else
                BlackboardComponent->ClearValue(FName("Enemy"));
    }
}
