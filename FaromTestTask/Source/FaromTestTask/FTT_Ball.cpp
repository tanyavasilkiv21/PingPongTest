#include "FTT_Ball.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

AFTT_Ball::AFTT_Ball()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(30.f);
	CollisionComp->SetCollisionObjectType(ECC_Pawn);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	CollisionComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	CollisionComp->SetGenerateOverlapEvents(true);
	RootComponent = CollisionComp;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	BallMesh->SetupAttachment(CollisionComp);
	BallMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Velocity = FVector(600.f, 0.f, 0.f);
}

void AFTT_Ball::BeginPlay()
{
	Super::BeginPlay();

	SetReplicateMovement(true);
	if (HasAuthority())
	{
		CollisionComp->OnComponentHit.AddDynamic(this, &AFTT_Ball::OnHit);
	}
}

void AFTT_Ball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FHitResult Hit;
		AddActorWorldOffset(Velocity * DeltaTime, true, &Hit);
	}
}

void AFTT_Ball::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					  FVector NormalImpulse, const FHitResult& Hit)
{
	if (!HasAuthority())
		return;

	if (!OtherActor || OtherActor == this)
		return;

	FVector ReflectedVelocity = FMath::GetReflectionVector(Velocity, Hit.ImpactNormal);

	FVector RandomSide = FVector::CrossProduct(ReflectedVelocity, FVector::UpVector);
	RandomSide.Normalize();

	float MaxAngleDegrees = 20.f; 

	float AngleOffset = FMath::FRandRange(-MaxAngleDegrees, MaxAngleDegrees);

	FRotator RotationOffset(0.f, AngleOffset, 0.f);
	FVector NewVelocity = RotationOffset.RotateVector(ReflectedVelocity);

	Velocity = NewVelocity.GetSafeNormal() * Velocity.Size();
}