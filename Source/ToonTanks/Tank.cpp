// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera\CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet\GameplayStatics.h"


ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
	
}

void ATank::BeginPlay()
{
    Super::BeginPlay();
    TankPlayerController  = Cast<APlayerController>(GetController());
    if (TankPlayerController)
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(TankPlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(TankMappingContext, 0);
        }
    }
}

void ATank::Fire(const FInputActionValue& Value)
{
    const bool CurrentValue = Value.Get<bool>();
    if (CurrentValue)
    {
        FireBullet();
    }
}

void ATank::Move(const FInputActionValue& Value)
{
    const float CurrentValue = Value.Get<float>();
    // UE_LOG(LogTemp, Warning, TEXT("Before Moving %f"), CurrentValue);
    if (CurrentValue)
    {
        float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
        // UE_LOG(LogTemp, Warning, TEXT("Moving %f"), CurrentValue);
        AddActorLocalOffset(FVector(CurrentValue * DeltaTime * Speed, 0, 0), true);
        
    }    
}

void ATank::Rotate(const FInputActionValue& Value)
{
    const float CurrentValue = Value.Get<float>();
    // UE_LOG(LogTemp, Warning, TEXT("Before Moving %f"), CurrentValue);
    if (CurrentValue)
    {
        float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
        // UE_LOG(LogTemp, Warning, TEXT("Moving %f"), CurrentValue);
        AddActorLocalRotation(FRotator(0, CurrentValue * DeltaTime * RotationSpeed, 0), true);
        
    }    
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (TankPlayerController)
    {
        if (TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult))
        {
            RotateTurret(HitResult.ImpactPoint);
            
            
        }
    }

}

void ATank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ATank::Fire);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);
        EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ATank::Rotate);
    };
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);


}
