#include "WinWindowWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerHUDWidget.h"
#include "../GameModes/LestaTestGM.h"


void UWinWindowWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (RestartButton)
    {
        RestartButton->OnClicked.AddDynamic(this, &UWinWindowWidget::RestartLevel);
    }
}

void UWinWindowWidget::RestartLevel()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        PlayerController->SetInputMode(FInputModeGameOnly());
        PlayerController->bShowMouseCursor = false;
    }
    UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()));
}

FString UWinWindowWidget::GetElapsedTime() const
{
    ALestaTestGM* GameMode = Cast<ALestaTestGM>(GetWorld()->GetAuthGameMode());
    if (!GameMode)
        return TEXT("00:00");

    int32 Milliseconds = GameMode->GetElapsedTime();
    int32 Seconds = GameMode->GetSeconds();

    return FString::Printf(TEXT("%02d:%02d"), Seconds, Milliseconds);
}
