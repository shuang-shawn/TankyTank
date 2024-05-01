// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "Tank.h"


void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    if (bPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
        Cast<ATank>(GetPawn())->SetCanMove(bPlayerEnabled);
    }
    else{
        GetPawn()->DisableInput(this);
        Cast<ATank>(GetPawn())->SetCanMove(bPlayerEnabled);
    }

    bShowMouseCursor = bPlayerEnabled;
}
