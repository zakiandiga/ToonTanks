// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTankGameMode.h"
#include "BasePawn.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
	CurrentGameMode = Cast<AToonTankGameMode>(UGameplayStatics::GetGameMode(this));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageSource)
{

	CurrentHealth -= Damage;

	Cast<ABasePawn>(GetOwner())->DamageTakenFollowUp(CurrentHealth/MaxHealth);

	if (CurrentHealth <= 0)
	{
		CurrentGameMode->ActorDied(DamagedActor);
	}
}


