#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTrapingPlatform.generated.h"

UCLASS()
class LESTATEST_API ABaseTrapingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseTrapingPlatform();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Trap")
	class UStaticMeshComponent* MeshComponent;

protected:
	virtual void BeginPlay() override;

	class UBoxComponent* BrickBoxColl;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

public:
	virtual void Tick(float DeltaTime) override;

private:
	
};
