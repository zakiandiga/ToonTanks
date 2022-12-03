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
	
private:

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	class USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Movement Properties")
	float MoveSpeed = 100;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Movement Properties")
	float TurnSpeed = 100;

	APlayerController* TankPlayerController;

	bool bIsAlive = true;

	void MoveForward(float value);

	void Turn(float value);

	void Attack();

	FVector GetMouseImpactPoint();
};
