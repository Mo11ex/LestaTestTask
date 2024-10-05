#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LESTATEST_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UActionComponent();

	float GetHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const { return CurrentHealth / MaxHealth; }

	UFUNCTION()
	void Lose();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "10.0"))
	float MaxHealth = 100.0f;

private:
	float CurrentHealth = 0.0f;

	void SetHealth(float NewHealth);
	

	UFUNCTION()
	void OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
