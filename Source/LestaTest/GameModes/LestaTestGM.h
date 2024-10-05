#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LestaTestGM.generated.h"


UCLASS()
class LESTATEST_API ALestaTestGM : public AGameMode
{
	GENERATED_BODY()
	
public:
    ALestaTestGM();

protected:
    virtual void BeginPlay() override;

private:
    FTimerHandle TimerHandle;
    float ElapsedTime;
    float Seconds;
    bool bTimerActive;

   
public:
    UFUNCTION(BlueprintCallable, Category = "Timer")
    float GetElapsedTime() const { return ElapsedTime; }
    float GetSeconds() const { return Seconds; }

    void StartTimer();
    void StopTimer();
    void UpdateTimer();
};
