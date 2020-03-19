// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UObject/NameTypes.h"
#include "On3DCharacter_Animation.generated.h"

/**
 * 
 */
UCLASS()
class ON3DFILTERTEST_API UOn3DCharacter_Animation : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage *MeleeAttackMontage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage *MeleeReceiveMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category  = States)
	bool bAcceptsSecondAttackInput;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category  = States)
	bool bReceiveFirstPunch;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category  = States)
	bool bReceiveSecondPunch;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category  = States)
	bool bDead;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float Direction;

public:

	void Attack();
	void ReceiveAttack();

	UFUNCTION(BlueprintCallable, Category = "Locomotion")
	void BindToMove(APawn* Pawn);

	UFUNCTION(BlueprintCallable, Category = Behaviour)
	void MakeDamage(ACharacter* Actor, FName SocketName);
};
