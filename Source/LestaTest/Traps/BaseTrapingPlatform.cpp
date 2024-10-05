#include "BaseTrapingPlatform.h"
#include "Components/BoxComponent.h"


ABaseTrapingPlatform::ABaseTrapingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	BrickBoxColl = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	BrickBoxColl->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BrickBoxColl->SetBoxExtent(FVector(64.0, 48.0, 32.0));

	BrickBoxColl->OnComponentBeginOverlap.AddDynamic(this, &ABaseTrapingPlatform::BeginOverlap);
}

void ABaseTrapingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseTrapingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseTrapingPlatform::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

