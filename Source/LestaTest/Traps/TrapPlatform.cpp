#include "TrapPlatform.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"

ATrapPlatform::ATrapPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	BrickBoxColl = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	BrickBoxColl->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BrickBoxColl->SetBoxExtent(FVector(64.0, 48.0, 32.0));

	BrickBoxColl->OnComponentBeginOverlap.AddDynamic(this, &ATrapPlatform::BeginOverlap);

	bIsActive = false;

	check(BrickBoxColl);
	check(MeshComponent);

	SwitchMaterial(DefaultMaterial, MeshComponent);
}

void ATrapPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATrapPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrapPlatform::ActivateTrap()
{
	bIsActive = true;

	SwitchMaterial(ActiveMaterial, MeshComponent);
	
	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &ATrapPlatform::ApplyDamage, DamageDelay, false);
}

void ATrapPlatform::ApplyDamage()
{
	SwitchMaterial(DamageMaterial, MeshComponent);

	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, [this]() { SwitchMaterial(DefaultMaterial, MeshComponent); }, 0.5f, false);

	TArray<AActor*> OverlappingActors;
	BrickBoxColl->GetOverlappingActors(OverlappingActors, ACharacter::StaticClass());
	for (AActor* Actor : OverlappingActors)
	{
		if (Actor)
		{
			Actor->TakeDamage(DamageAmount, FDamageEvent{}, Actor->GetInstigatorController(), this);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(RechargeTimerHandle, [this]() { bIsActive = false; }, RechargeTime, false);
}

void ATrapPlatform::SwitchMaterial(UMaterialInterface* Material, UStaticMeshComponent* Mesh)
{
	if (Material && Mesh)
		Mesh->SetMaterial(0, Material);
}

void ATrapPlatform::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	if(!bIsActive)
		ActivateTrap();
}


