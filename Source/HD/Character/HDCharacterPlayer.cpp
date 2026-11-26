// Fill out your copyright notice in the Description page of Project Settings.


#include "HDCharacterPlayer.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include <Net/UnrealNetwork.h>

AHDCharacterPlayer::AHDCharacterPlayer()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->TargetArmLength = 500.f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingRef(TEXT("/Game/Input/IMC_Move.IMC_Move"));
	if (nullptr != InputMappingRef.Object)
	{
		IMC = InputMappingRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Game/Input/IA_Move.IA_Move"));
	if (nullptr != InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Game/Input/IA_Look.IA_Look"));
	if (nullptr != InputActionLookRef.Object)
	{
		LookAction = InputActionLookRef.Object;
	}

	SetReplicates(true);
}

void AHDCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		EnableInput(PlayerController);
	}
}

void AHDCharacterPlayer::PossessedBy(AController* newController)
{
	Super::PossessedBy(newController);

	AActor* OwnerActor = GetOwner();
	if (!OwnerActor)
	{
		return;
	}
}

void AHDCharacterPlayer::OnRep_Owner()
{
	Super::OnRep_Owner();

	AActor* OwnerActor = GetOwner();
	if (!OwnerActor)
	{
		return;
	}
}

void AHDCharacterPlayer::PostNetInit()
{
	Super::PostNetInit();
}

void AHDCharacterPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AHDCharacterPlayer::Move(const FInputActionValue& Value)
{
	if (!Controller || Value.GetValueType() != EInputActionValueType::Axis2D)
	{
		return;
	}

	const FVector2D MovementInput = Value.Get<FVector2D>();
	const FRotator CameraRotation = FollowCamera ? FollowCamera->GetComponentRotation() : CameraBoom->GetComponentRotation();

	const FRotator YawRotation(0.f, CameraRotation.Yaw, 0.f);
	const FRotationMatrix MovementRotation(YawRotation);
	const FVector ForwardDirection = MovementRotation.GetUnitAxis(EAxis::X);
	const FVector RightDirection = MovementRotation.GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementInput.Y);
	AddMovementInput(RightDirection, MovementInput.X);
}

void AHDCharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AHDCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (Input && MoveAction)
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHDCharacterPlayer::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHDCharacterPlayer::Look);

		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		Subsystem->AddMappingContext(IMC, 0);
	}
}


