#include "PlayerHUDWidget.h"
#include "../Character/Components/ActionComponent.h"
#include "../GameModes/LestaTestGM.h"

float UPlayerHUDWidget::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return 0.0f;

	const auto Component = Player->GetComponentByClass(UActionComponent::StaticClass());
	const auto HealthComponent = Cast<UActionComponent>(Component);

	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

FString UPlayerHUDWidget::GetElapsedTime() const
{
	ALestaTestGM* GameMode = Cast<ALestaTestGM>(GetWorld()->GetAuthGameMode());
	if (!GameMode)
		return TEXT("00:00");
	
	int32 Milliseconds = GameMode->GetElapsedTime();
	int32 Seconds = GameMode->GetSeconds();
	
	return FString::Printf(TEXT("%02d:%02d"), Seconds, Milliseconds);
}
