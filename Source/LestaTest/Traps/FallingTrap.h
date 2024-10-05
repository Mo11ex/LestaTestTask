#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallingTrap.generated.h"

UCLASS()
class LESTATEST_API AFallingTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	AFallingTrap();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Trap")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	class UBoxComponent* BrickBoxColl;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Trap")
	float FallDelay = 2.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Trap")
	float ShakeFrequency = 50.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Trap")
	float ShakeAmplitude = 3.0f;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle FallingTimeHandle;

	bool bIsShake = false;
	float TimeElapsed = 0.0f;

	void ShakePlatform();

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
