// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

APlayerTank::APlayerTank()
{
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(CameraSpringArm);

}


void APlayerTank::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<APlayerController>(GetController());
}

void APlayerTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		RotateTurret(GetMouseImpactPoint());
	}
}

void APlayerTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerTank::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerTank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &APlayerTank::Attack);
}

void APlayerTank::MoveForward(float value)
{	
	FVector MoveDirection = FVector::ZeroVector;
	MoveDirection = (value * FVector::ForwardVector) * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(MoveDirection, true);
}

void APlayerTank::Turn(float value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = value * TurnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

	AddActorLocalRotation(DeltaRotation, true);
}

void APlayerTank::Attack()
{
	Super::Attack();
	
}

void APlayerTank::Die()
{
	Super::Die();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bIsAlive = false;
}

FVector APlayerTank::GetMouseImpactPoint()
{
	FHitResult HitResult;
	TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

	return HitResult.ImpactPoint;
}



