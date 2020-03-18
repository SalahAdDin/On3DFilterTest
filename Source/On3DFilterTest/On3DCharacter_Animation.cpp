// Fill out your copyright notice in the Description page of Project Settings.


#include "On3DCharacter_Animation.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Damage.h"
#include "PhysicsEngine/PhysicsSettings.h"

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

void UOn3DCharacter_Animation::MakeDamage(ACharacter* Actor, FName SocketName){
	
	float LengthTraceValue = 10.f;
	float DamageAmount = 1.f;

	FHitResult OutHit;

	const FVector SocketLocation = Actor->GetMesh()->GetSocketLocation(SocketName);
	FVector LengthTrace = Actor->GetActorForwardVector() * LengthTraceValue;
	FVector EndTrace = SocketLocation + LengthTrace;

	FCollisionQueryParams Params(FName(TEXT("KnockTraceSingle")), true,  Actor);
	Params.bReturnPhysicalMaterial = true;
	Params.bReturnFaceIndex = !UPhysicsSettings::Get()->bSuppressFaceRemapTable;

	// draw collision sphere
	// DrawDebugSphere(GetWorld(), SocketLocation, FCollisionShape::MakeSphere(LengthTraceValue).GetSphereRadius(), 4, FColor::Red, true);
	
	bool bIsHit = GetWorld()->SweepSingleByChannel(OutHit, SocketLocation, EndTrace, FQuat::Identity, ECC_WorldStatic, FCollisionShape::MakeSphere(LengthTraceValue), Params);

	// UE_LOG(LogTemp, Warning, TEXT("Is hit? %s"), bIsHit ? *FName("true").ToString() : *FName("false").ToString());
	
	// if(bIsHit)
	if(OutHit.bBlockingHit){
		UGameplayStatics::ApplyDamage(OutHit.GetActor(), DamageAmount, nullptr,Actor, UDamageType::StaticClass());
		UAISense_Damage::ReportDamageEvent(GetWorld(),OutHit.GetActor(), Actor, DamageAmount, OutHit.TraceStart, OutHit.Location);
	}

}