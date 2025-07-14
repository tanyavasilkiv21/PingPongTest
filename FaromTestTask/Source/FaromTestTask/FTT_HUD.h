// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FTT_HUD.generated.h"

/**
 * 
 */
UCLASS()
class FAROMTESTTASK_API AFTT_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

private:
	int32 GetPlayerScoreByTag(FName Tag);
};
