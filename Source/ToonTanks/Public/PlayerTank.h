// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PlayerTank.generated.h"

UCLASS()
class TOONTANKS_API APlayerTank : public ABasePawn
{
	GENERATED_BODY()

public:
	APlayerTank();

	void Die();

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

public:
	// Called every frame
	void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	APlayerController* GetPlayerController() const { return TankPlayerController; }	

	bool CheckPlayerAlive() const { return bIsAlive; }

	UFUNCTION(BlueprintImplementableEvent, Category = "Attack Properties")
	void OnAttack();

	UFUNCTION(BlueprintImplementableEvent, Category = "Attack Properties")
	void OnReadyingAttack();

	UFUNCTION(BlueprintImplementableEvent, Category = "Attack Properties")
	void OnReloadDone();

	UFUNCTION(BlueprintPure, Category = "Attack Properties")
	FTimerHandle GetPlayerAttackDelayTimer() { return PlayerAttackDelayTimer; }

	UFUNCTION(BlueprintPure, Category = "Attack Properties")
	FTimerHandle GetPlayerReloadAmmoTimer() { return ReloadAmmoTimer; }

	UFUNCTION(BlueprintPure, Category = "Attack Properties")
	float GetReadyingAttackTime() { return AttackSpeed; }

	UFUNCTION(BlueprintPure, Category = "Attack Properties")
	int GetRemainingAmmo() { return RemainingAmmo; }

	UFUNCTION(BlueprintPure, Category = "Attack Properties")
	float GetReloadingTime() { return ReloadTime; }

	UFUNCTION(BlueprintPure, Category = "Attack Properties")
	int GetMaxAmmo() { return MaxAmmo; }
	
private:

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	class USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Movement Properties")
	float MoveSpeed = 100;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Movement Properties")
	float TurnSpeed = 100;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Attack Properties")
	float ReloadTime = 3;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Attack Properties")
	int32 MaxAmmo = 5;

	int32 RemainingAmmo = 0;

	bool bAttackReady = true;

	APlayerController* TankPlayerController;

	FTimerHandle PlayerAttackDelayTimer;
	FTimerHandle ReloadAmmoTimer;

	bool bIsAlive = true;

	void MoveForward(float value);

	void Turn(float value);

	void Attack();

	void AmmoReloading();

	void ReadyingAttack();

	FVector GetMouseImpactPoint();
};
