// Fill out your copyright notice in the Description page of Project Settings.


#include "HDRoomCreateWidget.h"

#include <Components/Button.h>
#include <Components/EditableText.h>

#include <OnlineSubsystem.h>
#include <OnlineSessionSettings.h>
#include <Interfaces/OnlineSessionInterface.h>

void UHDRoomCreateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Create->OnClicked.AddDynamic(this, &UHDRoomCreateWidget::CreateSession);
}

void UHDRoomCreateWidget::CreateSession()
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (!Subsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("OnlineSubsystem을 찾을 수 없습니다."));
		return;
	}

	IOnlineSessionPtr Sessions = Subsystem->GetSessionInterface();
	if (!Sessions.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("SessionInterface를 사용할 수 없습니다."));
		return;
	}

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!LocalPlayer)
	{
		UE_LOG(LogTemp, Error, TEXT("LocalPlayer를 찾을 수 없습니다."));
		return;
	}

	const FUniqueNetIdRepl UserId = LocalPlayer->GetPreferredUniqueNetId();
	if (!UserId.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("유효한 온라인 사용자 ID가 없습니다. Steam 로그인을 확인하세요."));
		return;
	}

	FOnlineSessionSettings Settings;
	Settings.bIsLANMatch = false;
	Settings.bShouldAdvertise = true;
	Settings.bAllowJoinInProgress = true;
	Settings.bAllowJoinViaPresence = true;
	Settings.bUsesPresence = true;
	Settings.bUseLobbiesIfAvailable = true;
	Settings.NumPublicConnections = 4;

	const FString Title = RoomTitle->GetText().ToString().TrimStartAndEnd();
	Settings.Set(
		FName(TEXT("ROOM_TITLE")),
		Title,
		EOnlineDataAdvertisementType::ViaOnlineServiceAndPing
	);

	CreateSessionCompleteHandle =
		Sessions->AddOnCreateSessionCompleteDelegate_Handle(
			FOnCreateSessionCompleteDelegate::CreateUObject(
				this,
				&UHDRoomCreateWidget::OnCreateSessionComplete
			)
		);

	const bool bRequestAccepted =
		Sessions->CreateSession(*UserId, NAME_GameSession, Settings);

	if (!bRequestAccepted)
	{
		Sessions->ClearOnCreateSessionCompleteDelegate_Handle(
			CreateSessionCompleteHandle
		);
		UE_LOG(LogTemp, Error, TEXT("세션 생성 요청을 시작하지 못했습니다."));
	}
}

void UHDRoomCreateWidget::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	// 방으로 들어가게 됨

	// 방 위젯 띄워주기
	OnRoomCreated.Broadcast();

	// 현재 세션에 들어와있는 사람 리스트 띄워주기

}
