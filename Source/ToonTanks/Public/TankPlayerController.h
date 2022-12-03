// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:

	void SetPlayerEnabledState(bool bPlayerEnabled);
};
