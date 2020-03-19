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

void AOn3DAIController::UpdateBlackboardLastSeenLocation(AActor* Actor, FAIStimulus Stimulus){
    
    bool bIsEnemy = Actor->ActorHasTag(FName("Enemy"));
    bool bIsSuccessfullySensed = Stimulus.WasSuccessfullySensed();
    // bool bIsSuccessfullySensed = Stimulus->WasSuccessfullySensed();
    UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
    const FVector LastSeenLocation = Stimulus.StimulusLocation;

    if(Actor){

        if (!bIsEnemy)
            if (bIsSuccessfullySensed)
                BlackboardComponent->SetValueAsVector(FName("LastSeenLocation"), LastSeenLocation);
            else
                BlackboardComponent->ClearValue(FName("LastSeenLocation"));
    }
}

void AOn3DAIController::CompleteSenses(AActor* Actor, TArray<FAIStimulus> StimulusArray){
    for (auto index = 0; index < StimulusArray.Num(); index++){
        const FAIStimulus& LocalSense  = StimulusArray[index];
        switch (index){
            case 0:
                UpdateBlackboardEnemyKey(Actor, LocalSense);
                break;
            case 1:
                UpdateBlackboardLastSeenLocation(Actor, LocalSense);
                break;
            case 2:
            // TODO: LastSeenLocation brings him to the point he is and it finish, result, character does not turn around;
            // EnemyKey does not make him to rotate at the moment, and it blocks to sight stimulus to work
                UpdateBlackboardLastSeenLocation(Actor, LocalSense);
                break;
            default:
                break;
        }
    }
}
