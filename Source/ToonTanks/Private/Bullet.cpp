// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = false;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System"));
		
	RootComponent = BulletMesh;
	ProjectileMovementComponent->MaxSpeed = 1500;
	ProjectileMovementComponent->InitialSpeed = 800;
	ParticleSystemComponent->SetupAttachment(RootComponent);

}

void ABullet::BeginPlay()
{
	Super::BeginPlay();		

	BulletMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);

	if (ShotSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ShotSound, GetActorLocation());
	}
}


void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* Other, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	AActor* BulletOwner = GetOwner();

	if (BulletOwner == nullptr) return;

	AController* OwnerInstigator = BulletOwner->GetInstigatorController();

	if (BulletOwner && Other && Other != this && Other != BulletOwner)
	{
		UGameplayStatics::ApplyDamage(Other, DamageAmount, OwnerInstigator, BulletOwner, UDamageType::StaticClass());

		if (HitParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());
		}	

		if (ImpactSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
		}

		if (ImpactCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(ImpactCameraShakeClass);
		}

	}

	Destroy();

}

