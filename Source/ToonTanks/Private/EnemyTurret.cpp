// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTurret.h"
#include "PlayerTank.h"
#include "Kismet/GameplayStatics.h"


void AEnemyTurret::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	GetWorldTimerManager().SetTimer(TurretAttackDelay, this, &AEnemyTurret::SetAttackReady, AttackSpeed, false);
}

void AEnemyTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Player == nullptr ) return;
	
	if (CheckPlayerInRange() && Player->CheckPlayerAlive())
	{
		RotateTurret(Player->GetActorLocation());

		FHitResult HitResult;
		FCollisionShape CollisionShape = FCollisionShape::MakeSphere(10);

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
	bAttackReady = false;
	
	Super::Attack();

	AttackSpeed = FMath::FRandRange(1, 3);

	GetWorldTimerManager().SetTimer(TurretAttackDelay, this, &AEnemyTurret::SetAttackReady, AttackSpeed, false);
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

