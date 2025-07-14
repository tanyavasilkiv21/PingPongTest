// Fill out your copyright notice in the Description page of Project Settings.


#include "FTT_Player.h"
#include "Net/UnrealNetwork.h"

void AFTT_Player::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFTT_Player, Offset);
}

AFTT_Player::AFTT_Player()
{
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
}

void AFTT_Player::Move(float AxisValue)
{
	FVector Right = GetActorRightVector();
	Offset  = Right * AxisValue * MoveSpeed * GetWorld()->DeltaTimeSeconds;
	AddActorWorldOffset(Offset, true);
}

void AFTT_Player::BeginPlay()
{
	Super::BeginPlay();
	SetReplicateMovement(true);
}

void AFTT_Player::OnRep_IsMoving()
{
	AddActorWorldOffset(Offset, true);
}
