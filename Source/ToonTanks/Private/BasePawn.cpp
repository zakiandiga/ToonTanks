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
	RootComponent = BaseCapsule;
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet Spawn Point"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	BodyMesh->SetupAttachment(BaseCapsule);
	TurretMesh->SetupAttachment(BodyMesh);
	BulletSpawnPoint->SetupAttachment(TurretMesh);

	RemainingAmmo = MaxAmmo;
}



void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetWorldTimerManager().IsTimerActive(ReloadTimer) && RemainingAmmo < MaxAmmo)
	{
		GetWorldTimerManager().SetTimer(ReloadTimer, this, &ABasePawn::AmmoReloading, ReloadTime, false);
	}
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
	if (bAttackOnDelay || GetWorldTimerManager().IsTimerActive(AttackFireTimer) || RemainingAmmo <= 0) return;


	RemainingAmmo -= 1;
	bAttackOnDelay = true;
	GetWorldTimerManager().SetTimer(AttackFireTimer, this, &ABasePawn::ReadyingAttack, AttackSpeed, false);
	
	//Shoot the bullet
	if (BulletClass)
	{	
		ABullet* BulletSpawned = GetWorld()->SpawnActor<ABullet>(BulletClass, BulletSpawnPoint->GetComponentLocation(), BulletSpawnPoint->GetComponentRotation());
		BulletSpawned->SetOwner(this);
	}		
}

void ABasePawn::ReadyingAttack()
{
	if (bAttackOnDelay)
	{
		bAttackOnDelay = false;
	}
}

void ABasePawn::AmmoReloading()
{
	if (RemainingAmmo >= MaxAmmo)
	{
		RemainingAmmo = MaxAmmo;
		return;
	}

	RemainingAmmo += 1;
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




