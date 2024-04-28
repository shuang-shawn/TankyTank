// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera\CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


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

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
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
        UE_LOG(LogTemp, Warning, TEXT("Fire Triggered"));
    }
}

void ATank::Move(float Value)
{
    FVector CurrentLocation = GetActorLocation();
    SetActorLocation(CurrentLocation + FVector(Value, 0, 0));
    
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ATank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATank::Fire);
    };
}
