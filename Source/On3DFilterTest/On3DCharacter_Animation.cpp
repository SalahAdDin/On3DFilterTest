// Fill out your copyright notice in the Description page of Project Settings.


#include "On3DCharacter_Animation.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"

void UOn3DCharacter_Animation::Attack(){
    if (MeleeAttackMontage)
	{
		FName CurrentSection = Montage_GetCurrentSection(MeleeAttackMontage);
 
		if (CurrentSection.IsNone())
		{
			Montage_Play(MeleeAttackMontage);
		}
		else if (CurrentSection.IsEqual("Right") && bAcceptsSecondAttackInput)
		{
			Montage_JumpToSection(FName("Left"), MeleeAttackMontage);
		} 
	}
}

void UOn3DCharacter_Animation::ReceiveAttack(){
	if (MeleeReceiveMontage){
		FName CurrentSection = Montage_GetCurrentSection(MeleeReceiveMontage);
		if (CurrentSection.IsNone())
		{
			Montage_Play(MeleeReceiveMontage);
		}
		else if (bReceiveFirstPunch)
		{
			Montage_JumpToSection(FName("Right"), MeleeReceiveMontage);
		} 
		else if (bReceiveSecondPunch) {
			Montage_JumpToSection(FName("Left"), MeleeReceiveMontage);
		}
	}
}

void UOn3DCharacter_Animation::BindToMove(APawn* Pawn)
{
	const FVector Velocity = Pawn->GetVelocity();
	const FRotator Rotation = Pawn->GetActorRotation();

	Speed = Velocity.Size();

	Direction = CalculateDirection(Velocity, Rotation);
}