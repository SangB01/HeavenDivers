// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "HDActivatableWidget.generated.h"

UENUM(BlueprintType)
enum class EHDUIInputMode : uint8
{
	Inherit,
	Menu,
	GameMenu,
	Gameplay
};


UCLASS(Abstract, Blueprintable)
class HD_API UHDActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HD|Input")
		EHDUIInputMode InputMode = EHDUIInputMode::Menu;
};
