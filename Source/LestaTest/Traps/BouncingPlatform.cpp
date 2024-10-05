#include "BouncingPlatform.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ABouncingPlatform::ABouncingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	BrickBoxColl = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	BrickBoxColl->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BrickBoxColl->SetBoxExtent(FVector(64.0, 48.0, 32.0));

	BrickBoxColl->OnComponentBeginOverlap.AddDynamic(this, &ABouncingPlatform::BeginOverlap);
}

void ABouncingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABouncingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABouncingPlatform::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ACharacter* Character = Cast<ACharacter>(OtherActor);
		if (Character)
		{
			UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
			if (MovementComponent)
			{
				FVector CurrentVelocity = MovementComponent->Velocity;

				FVector BounceDirection = FVector(0, 0, 1);

				Character->LaunchCharacter((BounceDirection * BounceForce) + CurrentVelocity, true, true);
			}
		}
	}
}

