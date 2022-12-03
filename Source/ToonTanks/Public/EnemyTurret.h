// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "EnemyTurret.generated.h"

class APlayerTank;
UCLASS()
class TOONTANKS_API AEnemyTurret : public ABasePawn
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	void Attack();


public:
	virtual void Tick(float DeltaTime) override;

	void Die();

private:
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Attack Properties")
	float AttackRange = 500;

	APlayerTank* Player;
	FTimerHandle TurretAttackDelay;

	bool bAttackReady;
	void SetAttackReady();
	bool CheckPlayerInRange();
};
