#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoseWindowWidget.generated.h"

UCLASS()
class LESTATEST_API ULoseWindowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void RestartLevel();

protected:
    virtual void NativeConstruct() override;

private:
    UPROPERTY(meta = (BindWidget))
    class UButton* RestartButton;
};
