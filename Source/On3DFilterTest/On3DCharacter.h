// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "On3DCharacter.generated.h"

UCLASS()
class ON3DFILTERTEST_API AOn3DCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent *CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent *ThirdPersonCamera;

public:
	// Sets default values for this character's properties
	AOn3DCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

protected:
	void MoveForward(float Value);

	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable, Category = Behaviour)
	void Attack();

	UFUNCTION(BlueprintCallable, Category = Behaviour)
	bool IsDead();

	UFUNCTION(BlueprintCallable, Category = Behaviour)
	void CalculateDamage(int Damage);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

public:
	FORCEINLINE class USpringArmComponent *GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent *GetThirdPersonCamera() const { return ThirdPersonCamera; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Setup)
	int Health;
};
