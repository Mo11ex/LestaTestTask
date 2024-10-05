#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WindTrap.generated.h"

class ACharacter;

UCLASS()
class LESTATEST_API AWindTrap : public AActor
{
	GENERATED_BODY()
	
public:
	AWindTrap();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Trap")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	class UBoxComponent* BrickBoxColl;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	float WindSpeed = 1000.0f;

public:
	virtual void Tick(float DeltaTime) override;

private:
	FVector CurrentWindDirection;
	FTimerHandle WindChangeTimer;

	bool bIsOverlapped = false;

	ACharacter* CharOver;

	void ChangeWindDirection();

	void TeleportCharacter(ACharacter* Character);

	void DebugWindDirection(); // Отладочная функция для вывода направления ветра

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(class UPrimitiveComponent* OverlappedComp, 
		class AActor* OtherActor, 
		class UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);

};
