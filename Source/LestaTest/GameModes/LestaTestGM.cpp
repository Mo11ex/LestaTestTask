#include "LestaTestGM.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

ALestaTestGM::ALestaTestGM()
{
	ElapsedTime = 0.f;
	Seconds = 0.f;
	bTimerActive = false;
}

void ALestaTestGM::BeginPlay()
{
	Super::BeginPlay();
}

void ALestaTestGM::StartTimer()
{
	if (!bTimerActive)
	{
		bTimerActive = true;
		ElapsedTime = 0.f;
		Seconds = 0.f;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ALestaTestGM::UpdateTimer, 0.01f, true);
		UE_LOG(LogTemp, Warning, TEXT("Timer start!"));
	}
}

void ALestaTestGM::StopTimer()
{
	UE_LOG(LogTemp, Warning, TEXT("Timer StopTimer!"));
	if (bTimerActive)
	{
		bTimerActive = false;
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		UE_LOG(LogTemp, Warning, TEXT("Timer stopped: %f sec"), Seconds);
		UE_LOG(LogTemp, Warning, TEXT("Timer StopTimer in fuction!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Timer StopTimer not is running!"));
	}
}

void ALestaTestGM::UpdateTimer()
{
	ElapsedTime += 1.f;
	if (ElapsedTime == 100.f)
	{
		Seconds += 1.f;
		ElapsedTime = 0.f;
	}
	UE_LOG(LogTemp, Warning, TEXT("Elapsed: %f"), ElapsedTime);
}
