// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FTT_PlayerState.generated.h"

UCLASS()
class FAROMTESTTASK_API AFTT_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AFTT_PlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void AddScore(int Amount);
	
public:
	UPROPERTY(Replicated)
	int PlayerScore = 0;

	UPROPERTY(Replicated)
	FName PlayerTag;
	
};
