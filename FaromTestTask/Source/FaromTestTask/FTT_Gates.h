// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FTT_Gates.generated.h"

class UBoxComponent;

UCLASS()
class FAROMTESTTASK_API AFTT_Gates : public AActor
{
	GENERATED_BODY()
	
public:	
	AFTT_Gates();
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* GoalTrigger;
};
