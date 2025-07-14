#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FTT_Ball.generated.h"

class USphereComponent;

UCLASS()
class FAROMTESTTASK_API AFTT_Ball : public AActor
{
	GENERATED_BODY()
	
public:	
	AFTT_Ball();
	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			   FVector NormalImpulse, const FHitResult& Hit);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Velocity;
	
protected:
	virtual void BeginPlay() override;

protected:	
	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BallMesh;
};