// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = false;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
		
	RootComponent = BulletMesh;
	ProjectileMovementComponent->MaxSpeed = 1500;
	ProjectileMovementComponent->InitialSpeed = 800;

}

void ABullet::BeginPlay()
{
	Super::BeginPlay();		

	BulletMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* Other, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	auto BulletOwner = GetOwner();

	if (BulletOwner == nullptr) return;

	auto OwnerInstigator = BulletOwner->GetInstigatorController();

	if (Other && Other != this && Other != BulletOwner)
	{
		UGameplayStatics::ApplyDamage(Other, DamageAmount, OwnerInstigator, BulletOwner, UDamageType::StaticClass());
	}

	Destroy();
}

