// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ThirdPersonCharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;

UCLASS()
class ZENITHBASE_API AThirdPersonCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AThirdPersonCharacterBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
		UStaticMeshComponent* MeshComp;


protected:

	void MoveForward(float value);
	void MoveRight(float value);
	void TurnAtRate(float value);
	void LookUpAtRate(float value);

	virtual void Landed(const FHitResult& Hit) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
		float BaseTurnRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
		float BaseLookUpAtRate;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION()
		void DoubleJump();
	UPROPERTY()
		int DoubleJumpCounter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float JumpHeight;

	UFUNCTION()
		void Sprint();
	UPROPERTY(EditAnywhere)
		float RunningSpeed;

	UFUNCTION()
		void Walk();
	UPROPERTY(EditAnywhere)
		float WalkingSpeed;
};
