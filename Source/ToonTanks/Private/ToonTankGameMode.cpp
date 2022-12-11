// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TankPlayerController.h"
#include "PlayerTank.h"
#include "EnemyTurret.h"

void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();

	GameStart();
}

void AToonTankGameMode::GameStart()
{
	//EnemyCount = GetEnemyCount();

	PlayerTank = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (TankPlayerController)
	{
		TankPlayerController->SetPlayerEnabledState(false);

		GameStartCountDown();
	}
}

void AToonTankGameMode::GameStartCountDown()
{
	FTimerHandle EnablingPlayerTimer;
	FTimerDelegate GameStartTimerDelegate = FTimerDelegate::CreateUObject(TankPlayerController, &ATankPlayerController::SetPlayerEnabledState, true);
	GetWorldTimerManager().SetTimer(EnablingPlayerTimer, GameStartTimerDelegate, StartCountdown, false);
}

void AToonTankGameMode::ActorDied(AActor* DiedActor)
{
	if (DiedActor != PlayerTank)
	{
		AEnemyTurret* DestroyedEnemy = Cast<AEnemyTurret>(DiedActor);
		DestroyedEnemy->Die();

		if(GetEnemyCount() > 0)
			return;
	
		GameOver(true);	

		return;
	}
	
	if (TankPlayerController)
	{			
		TankPlayerController->SetPlayerEnabledState(false);
	}

	PlayerTank->Die();
	GameOver(false);
}

int32 AToonTankGameMode::GetEnemyCount()
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(this, TSubclassOf<AActor>(AEnemyTurret::StaticClass()), Enemies);

	return Enemies.Num();
}