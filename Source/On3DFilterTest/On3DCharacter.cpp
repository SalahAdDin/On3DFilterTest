// Fill out your copyright notice in the Description page of Project Settings.

#include "On3DCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "On3DCharacter_Animation.h"

// Sets default values
AOn3DCharacter::AOn3DCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;

	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	ThirdPersonCamera->bUsePawnControlRotation = false;
}

void AOn3DCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AOn3DCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AOn3DCharacter::Attack()
{
	UOn3DCharacter_Animation *AnimInstanceRef = Cast<UOn3DCharacter_Animation>(GetMesh()->GetAnimInstance());
	if (AnimInstanceRef)
		AnimInstanceRef->Attack();
}

float AOn3DCharacter::TakeDamage(
    float DamageAmount,
    struct FDamageEvent const & DamageEvent,
    class AController * EventInstigator,
    AActor * DamageCauser
){
	Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);
	UOn3DCharacter_Animation *AnimInstanceRef = Cast<UOn3DCharacter_Animation>(GetMesh()->GetAnimInstance());
	if (AnimInstanceRef)
		AnimInstanceRef->ReceiveAttack();
	CalculateDamage((int)DamageAmount);
	return DamageAmount;
}

bool AOn3DCharacter::IsDead()
{
	return Health <= 0;
}

void AOn3DCharacter::CalculateDamage(int DamageAmount)
{
	Health -= DamageAmount;
	// if (IsDead() && GetController())
	// 	GetController()->UnPossess();
}

// Called to bind functionality to input
void AOn3DCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	// Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AOn3DCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AOn3DCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Knock", IE_Pressed, this, &AOn3DCharacter::Attack);
}
