// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Bullet.h"
#include "HealthComponent.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BaseCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Base Capsule"));
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet Spawn Point"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	
	RootComponent = BaseCapsule;
	BodyMesh->SetupAttachment(BaseCapsule);
	TurretMesh->SetupAttachment(BodyMesh);
	BulletSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(FVector TargetLook)
{
	FVector ToTarget = TargetLook - GetActorLocation();

	FRotator LookRotation = FRotator::ZeroRotator;
	LookRotation.Yaw = ToTarget.Rotation().Yaw;

	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookRotation, UGameplayStatics::GetWorldDeltaSeconds(this), TurretRotationSpeed));
}

void ABasePawn::Attack()
{	
	//Shoot the bullet
	if (BulletClass)
	{	
		ABullet* BulletSpawned = GetWorld()->SpawnActor<ABullet>(BulletClass, BulletSpawnPoint->GetComponentLocation(), BulletSpawnPoint->GetComponentRotation());
		BulletSpawned->SetOwner(this);
	}		
}

int32 ABasePawn::GetPlayerHealth()
{	
	return HealthComponent->GetHealthPercentage();
}

void ABasePawn::Die()
{	
	if (DeathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation(), GetActorRotation());
	}
	
	if (DieSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DieSound, GetActorLocation());
	}

	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}




