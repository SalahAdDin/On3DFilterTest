// Fill out your copyright notice in the Description page of Project Settings.


#include "On3DCharacter.h"

// Sets default values
AOn3DCharacter::AOn3DCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOn3DCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOn3DCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOn3DCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

