#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"


UCLASS()
class LESTATEST_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

	void OpenWinWidget();
	void OpenLoseWidget();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UPlayerHUDWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UWinWindowWidget> WinWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class ULoseWindowWidget> LoseWidgetClass;

	virtual void BeginPlay() override;

private:
	class UWinWindowWidget* WinWidgetInstance;
	class ULoseWindowWidget* DeathWidgetInstance;
	class UPlayerHUDWidget* PlayerHUDWidgetInstance;
	
};
