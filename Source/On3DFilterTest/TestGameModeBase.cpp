// Fill out your copyright notice in the Description page of Project Settings.
#include "TestGameModeBase.h"
#include "On3DCharacter.h"
#include "Containers/UnrealString.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ATestGameModeBase::ATestGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/BP_On3DCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATestGameModeBase::OnCharacterDead(AActor* Actor){
	UE_LOG(LogTemp, Warning, TEXT("Killed: %s"), *Actor->GetName());

	bool bIsRemoved = EnemyArray.Remove(Actor);
	bool bIsWin = EnemyArray.Num() <= 0 ? true : false;

	if(bIsRemoved && bIsWin){
		GameOver(FName(TEXT("Winner!")));
	UE_LOG(LogTemp, Warning, TEXT("Winner!"), )
	}
	else if(!bIsRemoved){
		GameOver(FName(TEXT("Loser!")));
	UE_LOG(LogTemp, Warning, TEXT("Loser!"), );
	}

}