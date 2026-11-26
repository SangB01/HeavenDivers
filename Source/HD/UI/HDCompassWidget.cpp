// Fill out your copyright notice in the Description page of Project Settings.


#include "HDCompassWidget.h"

#include "Camera/PlayerCameraManager.h"
#include "GameFramework/PlayerController.h"

void UHDCompassWidget::NativeTick(
	const FGeometry& WidgetGeometry,
	float InDeltaTime)
{
	Super::NativeTick(WidgetGeometry, InDeltaTime);

	APlayerController* PC = GetOwningPlayer();

	if (!PC || !PC->IsLocalController() || !PC->PlayerCameraManager)
	{
		return;
	}

	const float CameraYaw = PC->PlayerCameraManager->GetCameraRotation().Yaw;

	HeadingDegrees = FRotator::ClampAxis(CameraYaw - NorthOffset);

	const int32 DisplayedHeading = FMath::RoundToInt(HeadingDegrees) % 360;

	if (DisplayedHeading != LastDisplayedHeading)
	{
		LastDisplayedHeading = DisplayedHeading;

		OnHeadingChanged(DisplayedHeading);
	}
	}

