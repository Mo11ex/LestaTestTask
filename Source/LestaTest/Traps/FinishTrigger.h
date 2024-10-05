#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinishTrigger.generated.h"

UCLASS()
class LESTATEST_API AFinishTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	AFinishTrigger();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	class UBoxComponent* BrickBoxColl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	class ATimerAct* Timer;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);


};
