#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerAct.generated.h"

UCLASS()
class LESTATEST_API ATimerAct : public AActor
{
	GENERATED_BODY()
	
public:	
	ATimerAct();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
    void StartTimer();

    UFUNCTION(BlueprintCallable)
    void StopTimer();

    UFUNCTION(BlueprintCallable)
    void UpdateTimer();

    UFUNCTION(BlueprintCallable)
    void ResetTimer();

    UFUNCTION(BlueprintCallable)
    float GetElapsedTime() const { return ElapsedTime; };

    UFUNCTION(BlueprintCallable)
    bool IsRunning() const { return bIsRunning; };

private:
    FTimerHandle TimerHandle;
    float ElapsedTime;
    bool bIsRunning;

};
