// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "HDCompassWidget.generated.h"

UCLASS(Abstract, Blueprintable)
class HD_API UHDCompassWidget : public UCommonUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeTick(
		const FGeometry& WidgetGeometry,
		float InDeltaTime) override;

	// 북쪽 기준. 0이면 월드 +X가 북쪽.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Compass")
	float NorthOffset = 0.0f;

	// 북쪽 기준으로 계산한 카메라 방위각.
	UPROPERTY(BlueprintReadOnly, Category = "Compass")
	float HeadingDegrees = 0.0f;

	// 정수 각도가 달라졌을 때 호출하고, 화면 처리는 BP에서 구현.

	UFUNCTION(BlueprintImplementableEvent, Category = "Compass")
	void OnHeadingChanged(int32 Heading);

private:
	// 첫 갱신 때 반드시 알림이 발생하도록 -1로 시작.
	int32 LastDisplayedHeading = INDEX_NONE;


};
