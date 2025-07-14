// Fill out your copyright notice in the Description page of Project Settings.


#include "FTT_GameMode.h"

#include "EngineUtils.h"
#include "FTT_Ball.h"
#include "FTT_PlayerController.h"
#include "FTT_PlayerState.h"
#include "GameFramework/PlayerStart.h"

AActor* AFTT_GameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	FName DesiredTag = (PlayersConnected == 1) ? FName("Player1") : FName("Player2");

	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		if (It->PlayerStartTag == DesiredTag)
		{
			return *It;
		}
	}

	return Super::ChoosePlayerStart_Implementation(Player);
}

void AFTT_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ConnectedPlayers.Add(TPair<APlayerController*, int>(NewPlayer, 0));
	PlayersConnected++;

	if (PlayersConnected == 1)
	{
		NewPlayer->Tags.Add(FName("Player1"));
		if (AFTT_PlayerState* PS = Cast<AFTT_PlayerState>(NewPlayer->PlayerState))
		{
			PS->PlayerTag = FName("Player1");
		}
		if (AFTT_PlayerController* PC = Cast<AFTT_PlayerController>(NewPlayer))
		{
			PC->Client_ShowMessage("Waiting for another player...");
		}
	}

	if (PlayersConnected == 2)
	{
		NewPlayer->Tags.Add(FName("Player2"));
		if (AFTT_PlayerState* PS = Cast<AFTT_PlayerState>(NewPlayer->PlayerState))
		{
			PS->PlayerTag = FName("Player2");
		}
		TryStartGame();
	}
}

void AFTT_GameMode::SpawnBall()
{
	if (!BallClass)
	{
		return;
	}

	FVector SpawnLocation = FVector(300.0,-240.0,80.0); 
	FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AFTT_Ball* SpawnedBall = GetWorld()->SpawnActor<AFTT_Ball>(BallClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (SpawnedBall)
	{
		float XDir = FMath::RandBool() ? 1.f : -1.f;
		SpawnedBall->Velocity = FVector(600.f * XDir, 0, 0.f);
	}
}

void AFTT_GameMode::PlayerScored(FName Tag)
{
	for (auto& PC : ConnectedPlayers)
	{
		if (PC.Key->Tags.Contains(Tag) && PC.Key->Tags.Num() > 0)
		{
			PC.Value += 1;
			if (AFTT_PlayerState* PS = Cast<AFTT_PlayerState>(PC.Key->PlayerState))
			{
				PS->AddScore(1);
			}
			UE_LOG(LogTemp, Warning, TEXT("%s : %d"), *PC.Key->Tags[0].ToString(), PC.Value);
		}
	}
}

void AFTT_GameMode::TryStartGame()
{
	for (auto PC : ConnectedPlayers)
	{
		if (AFTT_PlayerController* MyPC = Cast<AFTT_PlayerController>(PC.Key))
		{
			MyPC->Client_ShowMessage("Game Started!");
			
		}
	}
	SpawnBall();
}
