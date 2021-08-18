// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ThirdPersonCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AThirdPersonCharacterBase::AThirdPersonCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	MeshComp->SetupAttachment(RootComponent);

	BaseTurnRate = 45.0f;
	BaseLookUpAtRate = 45.0f;

	JumpHeight = 600.0f;
	WalkingSpeed = 600.0f;
	RunningSpeed = 1000.0f;

}


void AThirdPersonCharacterBase::MoveForward(float value)
{
	if ((Controller) && (value != 0.0f)) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void AThirdPersonCharacterBase::MoveRight(float value)
{
	if ((Controller) && (value != 0.0f)) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

void AThirdPersonCharacterBase::TurnAtRate(float value)
{
	AddControllerYawInput(value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AThirdPersonCharacterBase::LookUpAtRate(float value)
{
	AddControllerPitchInput(value * BaseLookUpAtRate * GetWorld()->GetDeltaSeconds());
}

void AThirdPersonCharacterBase::Landed(const FHitResult& Hit)
{
	DoubleJumpCounter = 0;
}

void AThirdPersonCharacterBase::DoubleJump()
{
	if (DoubleJumpCounter <= 1) {
		ACharacter::LaunchCharacter(FVector(0, 0, JumpHeight), false, true);
		DoubleJumpCounter++;
	}
}

void AThirdPersonCharacterBase::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
}

void AThirdPersonCharacterBase::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
}

// Called to bind functionality to input
void AThirdPersonCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AThirdPersonCharacterBase::DoubleJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AThirdPersonCharacterBase::Sprint);
	PlayerInputComponent->BindAction("Walk", IE_Released, this, &AThirdPersonCharacterBase::Walk);

	PlayerInputComponent->BindAxis("MoveForward", this, &AThirdPersonCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThirdPersonCharacterBase::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AThirdPersonCharacterBase::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AThirdPersonCharacterBase::LookUpAtRate);



}





