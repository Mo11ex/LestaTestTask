#include "WindTrap.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Engine.h" 

AWindTrap::AWindTrap()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	BrickBoxColl = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	BrickBoxColl->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BrickBoxColl->SetBoxExtent(FVector(64.0, 48.0, 32.0));

	BrickBoxColl->OnComponentBeginOverlap.AddDynamic(this, &AWindTrap::BeginOverlap);
	BrickBoxColl->OnComponentEndOverlap.AddDynamic(this, &AWindTrap::EndOverlap);

	ChangeWindDirection();
}

void AWindTrap::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(WindChangeTimer, this, &AWindTrap::ChangeWindDirection, 2.0f, true);
}

void AWindTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsOverlapped)
		TeleportCharacter(CharOver);
}

void AWindTrap::ChangeWindDirection()
{
	float RandomAngle = FMath::FRandRange(0.f, 360.f);
	CurrentWindDirection = FVector(FMath::Cos(FMath::DegreesToRadians(RandomAngle)),
		FMath::Sin(FMath::DegreesToRadians(RandomAngle)), 0.f).GetSafeNormal();
}

void AWindTrap::TeleportCharacter(ACharacter* Character)
{
	if (Character)
	{
		FVector TargetLocation = Character->GetActorLocation() + (CurrentWindDirection * WindSpeed * GetWorld()->GetDeltaSeconds());

		FVector CurrentLocation = Character->GetActorLocation();
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, GetWorld()->GetDeltaSeconds(), 5.0f);

		Character->SetActorLocation(NewLocation);

		UE_LOG(LogActor, Warning, TEXT("New Location: %s"), *NewLocation.ToString());
	}
}

void AWindTrap::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		CharOver = Character;
		bIsOverlapped = true;
	}
}

void AWindTrap::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		bIsOverlapped = false;
	}
}

