// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
class UHealthComponent;
class USoundBase;
UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void Die();

protected:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UCapsuleComponent* BaseCapsule;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	USceneComponent* BulletSpawnPoint;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, Category = "Movement Properties")
	float TurretRotationSpeed = 10;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Attack Properties")
	float AttackSpeed = 1;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Attack Properties")
	float ReloadTime = 3;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Attack Properties")
	int32 MaxAmmo = 5;

	void RotateTurret(FVector TargetLook);

	void Attack();

public:

	virtual void Tick(float DeltaTime) override;

	void ReadyingAttack();

	//public getter refactoring for later
	/*	
	public getterand setter
	float GetAttackSpeed() const { return AttackSpeed; }
	float GetReloadTime() const { return ReloadTime; }
	int32 GetTotalAmmo() const { return TotalAmmo; }
	int32 GetRemainingAmmo() const { return RemainingAmmo; }
	bool AttackOnDelay() const { return AttackOnDelay; }

	//Setter
	void SetAttackOnDelay(bool value);
	void SetRemainingAmmo(int32 value);
	*/


private:

	UPROPERTY(EditDefaultsOnly, Category = "Attack Properties")
	TSubclassOf<class ABullet> BulletClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = " true"), Category = "Attack Properties")
	USoundBase* DieSound;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = " true"), Category = "Attack Properties")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = " true"), Category = "Attack Properties")
	class UParticleSystem* DeathParticle;

	FTimerHandle AttackFireTimer;
	FTimerHandle ReloadTimer;

	int32 RemainingAmmo = 0;
	bool bAttackOnDelay = false;

	void AmmoReloading();
};
