// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet\GameplayStatics.h"


void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Find the distance to the Tank
    if(CheckDistance(Tank, FireRange))
    {
        RotateTurret(Tank->GetActorLocation());
    }
    
    

    
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();

    Destroy();
}

void ATower::StopFire()
{
    GetWorldTimerManager().ClearAllTimersForObject(this);
}

void ATower::BeginPlay()
{
    Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
    if(CheckDistance(Tank, FireRange))
    {
        FireBullet();
    }
}

bool ATower::CheckDistance(AActor* Target, float Distance)
{
    if(Target)
    {
        float TargetDistance = FVector::Dist(GetActorLocation(), Target->GetActorLocation());

        if (TargetDistance <= Distance)
        {
            return true;
        }
    }
    return false;
}


