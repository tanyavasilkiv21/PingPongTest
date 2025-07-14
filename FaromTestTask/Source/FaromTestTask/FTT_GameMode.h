// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FTT_GameMode.generated.h"

class AFTT_Ball;

UCLASS()
class FAROMTESTTASK_API AFTT_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	
	void SpawnBall();
	
	void PlayerScored(FName Tag);

public:
	UPROPERTY(EditDefaultsOnly, Category = "Ball")
	TSubclassOf<AFTT_Ball> BallClass;
	
protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:	
	void TryStartGame();
	
private:
	int32 PlayersConnected = 0;
	
	FTimerHandle WaitForSecondPlayerTimer;
	
	UPROPERTY()
	TMap<APlayerController*, int> ConnectedPlayers;

};
