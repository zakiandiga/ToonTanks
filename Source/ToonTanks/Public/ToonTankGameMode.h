// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameMode.generated.h"

UCLASS()
class TOONTANKS_API AToonTankGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	void ActorDied(AActor* DiedActor);

protected:
	void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Tank Game State Events")
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent, Category = "Tank Game State Events")
	void GameOver(bool bPlayerWin);
	
private:
	class APlayerTank* PlayerTank;
	class ATankPlayerController* TankPlayerController;

	float StartCountdown = 3;

	int32 EnemyCount = 0;

	void GameStart();

	void GameStartFollowUp();

	int32 GetEnemyCount();
};
