// Fill out your copyright notice in the Description page of Project Settings.


#include "HDActivatableWidget.h"

#include "HDActivatableWidget.h"
#include "CommonUISettings.h"
#include "Input/UIActionBindingHandle.h"

TOptional<FUIInputConfig> UHDActivatableWidget::GetDesiredInputConfig() const
{
    switch (InputMode)
    {
    case EHDUIInputMode::Menu:
        return FUIInputConfig(
            ECommonInputMode::Menu,
            EMouseCaptureMode::NoCapture,
            false
        );
        
    case EHDUIInputMode::GameMenu:
        return FUIInputConfig(
            ECommonInputMode::Game,
            EMouseCaptureMode::NoCapture,
            false
        );

    case EHDUIInputMode::Gameplay:
        return FUIInputConfig(
            ECommonInputMode::Game,
            EMouseCaptureMode::CapturePermanently
        );

    default:
        return Super::GetDesiredInputConfig();
    }
}

