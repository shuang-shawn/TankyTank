// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"

/**
 * 
 */


UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

	public:
		ATank();


	private:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Super Duper Components", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Super Duper Components", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;
	
	protected:
		virtual void BeginPlay() override;

		APlayerController* TankPlayerController;

		FHitResult HitResult;

		UPROPERTY(EditAnywhere, Category = Movement)
		float Speed = 100;

		UPROPERTY(EditAnywhere, Category = Movement)
		float RotationSpeed = 100;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputMappingContext* TankMappingContext;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* FireAction;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* MoveAction;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* RotateAction;

		void Fire(const FInputActionValue& Value);
		
		void Move(const FInputActionValue& Value);

		void Rotate(const FInputActionValue& Value);

	public:	
		virtual void Tick(float DeltaTime) override;
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		void HandleDestruction();

		APlayerController* GetTankPlayerController() const { return TankPlayerController; }
};
