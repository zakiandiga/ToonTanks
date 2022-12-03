// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTankGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
	CurrentGameMode = Cast<AToonTankGameMode>(UGameplayStatics::GetGameMode(this));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageSource)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s take damage from %s of %s"), *DamagedActor->GetActorNameOrLabel(), *DamageSource->GetActorNameOrLabel());
	UE_LOG(LogTemp, Warning, (TEXT("Bullet from %s hit %s for %d damage")), *DamageSource->GetActorNameOrLabel(), *DamagedActor->GetActorNameOrLabel(), (int32)Damage);

	CurrentHealth -= Damage;

	if (CurrentHealth <= 0)
	{
		CurrentGameMode->ActorDied(DamagedActor);
	}
}

void UHealthComponent::OnOwnerDie()
{
}
