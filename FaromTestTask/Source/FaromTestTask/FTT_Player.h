// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FTT_Player.generated.h"

UCLASS()
class FAROMTESTTASK_API AFTT_Player : public APawn
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	AFTT_Player();

	void Move(float AxisValue);
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 1000.f;

	float InputDirectionMultiplier = 1.f;
	
	UPROPERTY(ReplicatedUsing = OnRep_IsMoving)
	FVector Offset;
	
	UFUNCTION()
	void OnRep_IsMoving();
};
