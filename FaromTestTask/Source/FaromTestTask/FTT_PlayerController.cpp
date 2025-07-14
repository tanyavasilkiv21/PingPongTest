// Fill out your copyright notice in the Description page of Project Settings.


#include "FTT_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "FTT_Player.h"


void AFTT_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MappingContext, 0);
	}
}

void AFTT_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFTT_PlayerController::MoveActionTriggered);
	}
}

void AFTT_PlayerController::MoveActionTriggered(const FInputActionValue& Value)
{
	float Axis = Value.Get<float>();
	Server_Move(Axis);
	
}

void AFTT_PlayerController::Server_Move_Implementation(float AxisValue)
{
	if (AFTT_Player* MyPawn = Cast<AFTT_Player>(GetPawn()))
	{
		MyPawn->Move(AxisValue);
	}
}
void AFTT_PlayerController::Client_ShowMessage_Implementation(const FString& Message)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Message);
	}
}