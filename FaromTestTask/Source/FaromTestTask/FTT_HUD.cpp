// Fill out your copyright notice in the Description page of Project Settings.

#include "FTT_HUD.h"
#include "FTT_PlayerState.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "CanvasTypes.h"
#include "GameFramework/GameStateBase.h"

int32 AFTT_HUD::GetPlayerScoreByTag(FName Tag)
{
	if (!GetWorld() || !GetWorld()->GetGameState())
	{
		return 0;
	}

	for (APlayerState* PS : GetWorld()->GetGameState()->PlayerArray)
	{
		AFTT_PlayerState* MyPS = Cast<AFTT_PlayerState>(PS);
		if (!MyPS)
		{
			continue;
		}

		if (MyPS->PlayerTag == Tag)
		{
			return MyPS->PlayerScore;
		}
	}

	return 0;
}

void AFTT_HUD::DrawHUD()
{
	Super::DrawHUD();

	int ScoreP1 = GetPlayerScoreByTag(FName("Player1"));
	int ScoreP2 = GetPlayerScoreByTag(FName("Player2"));

	FString ScoreText = FString::Printf(TEXT("%d : %d"), ScoreP1, ScoreP2);

	if (Canvas)
	{
		float X = Canvas->ClipX / 2.0f;
		float Y = 50.0f;

		float TextWidth = 0.f;
		float TextHeight = 0.f;
		UFont* Font = GEngine->GetLargeFont();

		GetTextSize(ScoreText, TextWidth, TextHeight, Font);

		Canvas->SetDrawColor(FColor::Green);

		Canvas->DrawText(Font, ScoreText, X - TextWidth / 2, Y);
	}
}
