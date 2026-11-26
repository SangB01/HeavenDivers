// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HDPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HD_API AHDPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void PostInitializeComponents() override;

	virtual void PostNetInit() override;

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* aPawn) override;

};
