#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BouncingPlatform.generated.h"

UCLASS()
class LESTATEST_API ABouncingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	ABouncingPlatform();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Trap")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	class UBoxComponent* BrickBoxColl;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Trap")
	float BounceForce = 1000.0f;

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
