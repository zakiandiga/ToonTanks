// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UParticleSystemComponent;
class UParticleSystem;
class USoundBase;
class UCameraShakeBase;
UCLASS()
class TOONTANKS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Bullet")
	float InitialSpeed = 50;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Bullet")
	float MaxSpeed = 100;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Bullet")
	int32 DamageAmount = 2;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UStaticMeshComponent* BulletMesh;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = " true"), Category = "Bullet")
	UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = " true"), Category = "Bullet")
	USoundBase* ShotSound;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = " true"), Category = "Bullet")
	USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = " true"), Category = "Bullet")
	TSubclassOf<UCameraShakeBase> ImpactCameraShakeClass;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* Other, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void PlayHitParticle();
	void PlayImpactSound();
	void PlayImpactCameraShake();

};
