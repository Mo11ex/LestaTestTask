#include "ActionComponent.h"
#include "../../GameModes/LestaTestGM.h"
#include <Kismet/GameplayStatics.h>
#include "../../UI/GameHUD.h"


UActionComponent::UActionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);

	if (AActor* Owner = GetOwner())
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UActionComponent::OnTakeAnyDamageHandle);
	}
}

void UActionComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || !GetWorld()) return;

	float NewHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);
	SetHealth(NewHealth);

	if (FMath::IsNearlyZero(CurrentHealth))
	{
		Lose();
		UE_LOG(LogActor, Error, TEXT("You died!!!"));
	}
}

void UActionComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	CurrentHealth = NextHealth;
}

void UActionComponent::Lose()
{
	if (AGameHUD* MyHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
	{
		MyHUD->OpenLoseWidget();
	}
}


