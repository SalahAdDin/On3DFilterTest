// Fill out your copyright notice in the Description page of Project Settings.
#include "TestGameModeBase.h"
#include "On3DCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestGameModeBase::ATestGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/On3DCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
