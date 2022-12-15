#include "Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"
#include "Kismet/GameplayStatics.h"

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

	if (ShotSound == nullptr) return;
	
	UGameplayStatics::PlaySoundAtLocation(this, ShotSound, GetActorLocation());
}

void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* Other, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* BulletOwner = GetOwner();

	if (Other == nullptr || BulletOwner == nullptr || Other == this || Other == BulletOwner ) return;

	AController* OwnerInstigator = BulletOwner->GetInstigatorController();
	
	UGameplayStatics::ApplyDamage(Other, DamageAmount, OwnerInstigator, BulletOwner, UDamageType::StaticClass());

	PlayHitParticle();
	PlayImpactSound();
	PlayImpactCameraShake();	

	Destroy();
}

void ABullet::PlayHitParticle()
{
	if (HitParticle == nullptr) return;

	UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());
}

void ABullet::PlayImpactSound()
{
	if (ImpactSound == nullptr) return;

	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
}

void ABullet::PlayImpactCameraShake()
{
	if (ImpactCameraShakeClass == nullptr) return;

	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(ImpactCameraShakeClass);
}

