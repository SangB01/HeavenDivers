// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HDCharacterBase.h"
#include "InputActionValue.h"
#include "HDCharacterPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class HD_API AHDCharacterPlayer : public AHDCharacterBase
{
	GENERATED_BODY()

public:
	AHDCharacterPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* newController) override;
	virtual void OnRep_Owner() override;
	virtual void PostNetInit() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	/** 카메라 암 */
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** 3인칭 카메라 */
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> IMC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	float MoveSpeed = 5.f;

};

