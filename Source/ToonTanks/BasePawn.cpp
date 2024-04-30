// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Components\CapsuleComponent.h"
#include "Kismet\GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurrentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurrentMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurrentMesh);



}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();


	
}

void ABasePawn::RotateTurret(FVector TargetLocation)
{
	FVector ToTarget = TargetLocation - GetActorLocation();
	FRotator TargetRotation = FRotator(0, ToTarget.Rotation().Yaw, 0);
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	TurrentMesh->SetWorldRotation(FMath::RInterpTo(TurrentMesh->GetComponentRotation(), TargetRotation, DeltaTime, TurretRotatingSpeed));
}

void ABasePawn::FireBullet()
{
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	Projectile->SetOwner(this);
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

