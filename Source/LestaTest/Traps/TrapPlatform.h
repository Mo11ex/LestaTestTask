#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTrapingPlatform.h"
#include "TrapPlatform.generated.h"

class UMaterialInterface;

UCLASS()
class LESTATEST_API ATrapPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrapPlatform();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Trap")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	class UBoxComponent* BrickBoxColl;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap", meta = (ClampMin = "10.0", ClampMax = "100.0"))
	float DamageAmount = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	float RechargeTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	float DamageDelay = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	UMaterialInterface* DefaultMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	UMaterialInterface* ActiveMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	UMaterialInterface* DamageMaterial;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	bool bIsActive = false;

	FTimerHandle DamageTimerHandle;
	FTimerHandle RechargeTimerHandle;

	void ActivateTrap();

	void ApplyDamage();

	void SwitchMaterial(UMaterialInterface* Material, UStaticMeshComponent* Mesh);
    
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
