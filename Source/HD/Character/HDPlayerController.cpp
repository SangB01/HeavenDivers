// Fill out your copyright notice in the Description page of Project Settings.


#include "HDPlayerController.h"
#include "Engine/NetConnection.h"
#include "Engine/NetDriver.h"
#include "Kismet/GameplayStatics.h"

void AHDPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AHDPlayerController::PostNetInit()
{
	Super::PostNetInit();

	UNetDriver* NetDriver = GetNetDriver();
	if (!NetDriver)
	{
		return;
	}
}

void AHDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}

void AHDPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}
