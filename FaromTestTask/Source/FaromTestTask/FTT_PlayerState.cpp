// Fill out your copyright notice in the Description page of Project Settings.


#include "FTT_PlayerState.h"

#include "Net/UnrealNetwork.h"

AFTT_PlayerState::AFTT_PlayerState()
{
	bReplicates = true;
}

void AFTT_PlayerState::AddScore(int Amount)
{
	PlayerScore += Amount;
}

void AFTT_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFTT_PlayerState, PlayerScore);
	DOREPLIFETIME(AFTT_PlayerState, PlayerTag);
}