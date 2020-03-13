// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite = States)
	bool bAcceptsSecondAttackInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite = States)
	bool bDead;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float Direction;

public:

	void Attack();

	UFUNCTION(BlueprintCallable, Category = "Locomotion")
	void BindToMove(APawn* Pawn);
};
