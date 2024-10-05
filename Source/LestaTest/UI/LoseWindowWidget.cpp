#include "LoseWindowWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void ULoseWindowWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (RestartButton)
    {
        RestartButton->OnClicked.AddDynamic(this, &ULoseWindowWidget::RestartLevel);
    }
}

void ULoseWindowWidget::RestartLevel()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        PlayerController->SetInputMode(FInputModeGameOnly());
        PlayerController->bShowMouseCursor = false;
    }
    UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()));
}