// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "FTT_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class FAROMTESTTASK_API AFTT_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Client, Reliable)
	void Client_ShowMessage(const FString& Message);
	void Client_ShowMessage_Implementation(const FString& Message);
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void MoveActionTriggered(const FInputActionValue& Value);
	
	UFUNCTION(Server, Reliable)
	void Server_Move(float AxisValue);
	void Server_Move_Implementation(float AxisValue);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* MappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;
};


