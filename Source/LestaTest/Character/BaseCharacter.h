#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BaseCharacter.generated.h"

UCLASS()
class LESTATEST_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputDataAsset* InputActions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float SomeThreshold = 300.0f;

	/*-------------------Components-------------------*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UActionComponent* ActionComponent;
	/*------------------------------------------------*/

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void CheckFall();

	/*---------------Movement---------------*/
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartCrouch();
	void StopCrouch();
	virtual void Jump() override;
	virtual void StopJumping() override;
	void StartSprint();
	void StopSprint();
	/*---------------------------------------*/
};
