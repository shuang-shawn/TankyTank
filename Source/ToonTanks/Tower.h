// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();
	void StopFire();


protected:

	virtual void BeginPlay() override;

	

private:

	class ATank* Tank;

	UPROPERTY(EditAnywhere)
	float FireRange = 300;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	void CheckFireCondition();
	bool CheckDistance(AActor* Target, float Distance);

};
