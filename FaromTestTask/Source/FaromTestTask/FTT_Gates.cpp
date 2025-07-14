#include "FTT_Gates.h"

#include "FTT_Ball.h"
#include "FTT_GameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


AFTT_Gates::AFTT_Gates()
{
	PrimaryActorTick.bCanEverTick = false;

	GoalTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("GoalTrigger"));
	GoalTrigger->SetGenerateOverlapEvents(true);
	GoalTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GoalTrigger->SetCollisionResponseToAllChannels(ECR_Overlap);
	RootComponent = GoalTrigger;

	GoalTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFTT_Gates::OnOverlapBegin);
}

void AFTT_Gates::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority())
	{
		return;
	}

	if (AFTT_Ball* Ball = Cast<AFTT_Ball>(OtherActor))
	{
		if (AFTT_GameMode* GM = Cast<AFTT_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			GM->SpawnBall();
			if (Tags.Num() > 0)
			{
				GM->PlayerScored(Tags[0]);
			}
		}

		Ball->Destroy();
	}
}