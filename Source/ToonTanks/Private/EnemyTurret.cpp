// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTurret.h"
#include "PlayerTank.h"
#include "Kismet/GameplayStatics.h"


void AEnemyTurret::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	FTimerHandle TurretLocalTimer;
	GetWorldTimerManager().SetTimer(TurretLocalTimer, this, &AEnemyTurret::SetAttackReady, AttackSpeed, false);
}

void AEnemyTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Player && CheckPlayerInRange())
	{
		RotateTurret(Player->GetActorLocation());

		FHitResult HitResult;
		FCollisionShape CollisionShape = FCollisionShape::MakeSphere(10);
		
		//bool FacePlayer = GetWorld()->SweepSingleByChannel(HitResult, BulletSpawnPoint->GetComponentLocation(), BulletSpawnPoint->GetForwardVector() * AttackRange, FQuat::Identity, ECC_EngineTraceChannel1, CollisionShape);
		if (bAttackReady)
		{
			Attack();
		}
	}
}

void AEnemyTurret::Die()
{
	Super::Die();

	Destroy();
}

void AEnemyTurret::Attack()
{
	if (!CheckPlayerInRange() && bAttackReady)
	{
		return;
	}

	bAttackReady = false;
	
	Super::Attack();

	AttackSpeed = FMath::FRandRange(1, 3);
	
	FTimerHandle TurretLocalTimer;
	GetWorldTimerManager().SetTimer(TurretLocalTimer, this, &AEnemyTurret::SetAttackReady, AttackSpeed, false);
}

void AEnemyTurret::SetAttackReady()
{
	bAttackReady = true;

}

bool AEnemyTurret::CheckPlayerInRange()
{
	if (!Player) return false;

	float distance = FVector::Dist(GetActorLocation(), Player->GetActorLocation());
	return Player && distance <= AttackRange;
}

