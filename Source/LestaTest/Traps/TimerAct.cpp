#include "TimerAct.h"

ATimerAct::ATimerAct()
{
	PrimaryActorTick.bCanEverTick = true;

	ElapsedTime = 0.0f;
	bIsRunning = false;
}

void ATimerAct::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATimerAct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATimerAct::StartTimer()
{
	if (!bIsRunning)
	{
		bIsRunning = true;
		ElapsedTime = 0.0f;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATimerAct::UpdateTimer, 1.0f, true);
		UE_LOG(LogTemp, Warning, TEXT("Timer start!"));
	}
}

void ATimerAct::StopTimer()
{
	UE_LOG(LogTemp, Warning, TEXT("Timer StopTimer!"));
	if (bIsRunning)
	{
		bIsRunning = false;
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		UE_LOG(LogTemp, Warning, TEXT("Timer stopped: %f sec"), ElapsedTime);
		UE_LOG(LogTemp, Warning, TEXT("Timer StopTimer in fuction!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Timer StopTimer not is running!"));
	}
}

void ATimerAct::UpdateTimer()
{
	ElapsedTime += 1.0f;
	UE_LOG(LogTemp, Warning, TEXT("Elapsed: %f"), ElapsedTime);
}

void ATimerAct::ResetTimer()
{
	ElapsedTime = 0.0f;
}

