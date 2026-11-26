// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HDRoomCreateWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnRoomCreated);

/**
 * 
 */

UCLASS()
class HD_API UHDRoomCreateWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void CreateSession();

	UFUNCTION()
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	
public:
	FOnRoomCreated OnRoomCreated;

private:
	FDelegateHandle CreateSessionCompleteHandle;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UEditableText> RoomTitle;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Create;
};
