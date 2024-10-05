#include "FallingTrap.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"


AFallingTrap::AFallingTrap()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	BrickBoxColl = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	BrickBoxColl->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BrickBoxColl->SetBoxExtent(FVector(64.0, 48.0, 32.0));

	BrickBoxColl->OnComponentBeginOverlap.AddDynamic(this, &AFallingTrap::BeginOverlap);
}

void AFallingTrap::BeginPlay()
{
	Super::BeginPlay();
}

void AFallingTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeElapsed += DeltaTime;

	if (bIsShake)
		ShakePlatform();
}

void AFallingTrap::ShakePlatform()
{
	float OffsetX = FMath::Sin(TimeElapsed * ShakeFrequency) * ShakeAmplitude;
	float OffsetY = FMath::Sin(TimeElapsed * ShakeFrequency + PI / 2) * ShakeAmplitude;

	FVector OriginalLocation = GetActorLocation();

	FVector NewLocation = OriginalLocation + FVector(OffsetX, OffsetY, 0.0f);
	SetActorLocation(NewLocation);
}

void AFallingTrap::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		bIsShake = true;
		GetWorld()->GetTimerManager().SetTimer(FallingTimeHandle, [this](){ this->Destroy(); }, FallDelay, false);
	}
}

