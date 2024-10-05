#pragma once

#include "PlayerHUDWidget.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WinWindowWidget.generated.h"


UCLASS()
class LESTATEST_API UWinWindowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable)
    void RestartLevel();

    UFUNCTION(BlueprintCallable, Category = "UI")
    FString GetElapsedTime() const;

protected:
    virtual void NativeConstruct() override;

private:
    UPROPERTY(meta = (BindWidget))
    class UButton* RestartButton;
};
