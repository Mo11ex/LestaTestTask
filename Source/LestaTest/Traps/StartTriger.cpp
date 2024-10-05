#include "StartTriger.h"
#include "Components/BoxComponent.h"
#include "TimerAct.h"
#include <LestaTest/Character/BaseCharacter.h>
#include"../GameModes/LestaTestGM.h"

AStartTriger::AStartTriger()
{
	PrimaryActorTick.bCanEverTick = true;

	BrickBoxColl = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	Timer = CreateDefaultSubobject<ATimerAct>(TEXT("Timer"));
	BrickBoxColl->OnComponentBeginOverlap.AddDynamic(this, &AStartTriger::BeginOverlap);
}

void AStartTriger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStartTriger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStartTriger::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        ALestaTestGM* GameMode = Cast<ALestaTestGM>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
			GameMode->StartTimer();
        }
    }
	/*if (Timer)
	{
		Timer->StartTimer();
	}*/
}

