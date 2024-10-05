#include "GameHUD.h"
#include "Blueprint/UserWidget.h"
#include "WinWindowWidget.h"
#include "LoseWindowWidget.h"
#include "PlayerHUDWidget.h"
#include <Kismet/GameplayStatics.h>


void AGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerHUDWidgetClass)
	{
		PlayerHUDWidgetInstance = CreateWidget<UPlayerHUDWidget>(GetWorld(), PlayerHUDWidgetClass);
		if (PlayerHUDWidgetInstance)
		{
			PlayerHUDWidgetInstance->AddToViewport();		
		}
	}
	/*auto PlayerHUDWidget = CreateWidget<UPlayerHUDWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}*/
}

void AGameHUD::OpenWinWidget()
{
	if (WinWidgetClass)
	{
		WinWidgetInstance = CreateWidget<UWinWindowWidget>(GetWorld(), WinWidgetClass);
		if (WinWidgetInstance)
		{
			WinWidgetInstance->AddToViewport();
			if (PlayerHUDWidgetInstance)
			{
				PlayerHUDWidgetInstance->RemoveFromParent();
			}
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PlayerController)
			{
				PlayerController->SetInputMode(FInputModeUIOnly());
				PlayerController->bShowMouseCursor = true;
				PlayerController->GetPawn()->DisableInput(PlayerController);
			}
		}
	}
}

void AGameHUD::OpenLoseWidget()
{
	if (LoseWidgetClass)
	{
		DeathWidgetInstance = CreateWidget<ULoseWindowWidget>(GetWorld(), LoseWidgetClass);
		if (DeathWidgetInstance)
		{
			DeathWidgetInstance->AddToViewport();
			if (PlayerHUDWidgetInstance)
			{
				PlayerHUDWidgetInstance->RemoveFromParent();
			}
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PlayerController)
			{
				PlayerController->SetInputMode(FInputModeUIOnly());
				PlayerController->bShowMouseCursor = true;
			}
		}
	}
}
