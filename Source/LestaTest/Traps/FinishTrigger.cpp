#include "FinishTrigger.h"
#include "Components/BoxComponent.h"
#include "TimerAct.h"
#include <LestaTest/Character/BaseCharacter.h>
#include"../GameModes/LestaTestGM.h"
#include <Kismet/GameplayStatics.h>
#include "../UI/WinWindowWidget.h"
#include "../UI/GameHUD.h"

AFinishTrigger::AFinishTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	BrickBoxColl = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	BrickBoxColl->OnComponentBeginOverlap.AddDynamic(this, &AFinishTrigger::BeginOverlap);
	Timer = CreateDefaultSubobject<ATimerAct>(TEXT("Timer"));
}

void AFinishTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFinishTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFinishTrigger::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Finish overlapped!"));

	if (OtherActor)
	{
		ALestaTestGM* GameMode = Cast<ALestaTestGM>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->StopTimer();
			UE_LOG(LogTemp, Warning, TEXT("Stop!"));
		}
	}

	if (AGameHUD* MyHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
	{
		MyHUD->OpenWinWidget();
	}
}

