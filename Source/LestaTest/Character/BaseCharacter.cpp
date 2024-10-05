#include "BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LestaTest/Input/Data/InputDataAsset.h"
#include "LestaTest/Character/Components/ActionComponent.h"
#include "Engine/DamageEvents.h"
#include "../Traps/TimerAct.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

ABaseCharacter::ABaseCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetMesh(), FName("Socket_Target"));
	SpringArmComponent->TargetArmLength = 0.0f;
	SpringArmComponent->bUsePawnControlRotation = false;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(SpringArmComponent);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	ActionComponent = CreateDefaultSubobject<UActionComponent>(TEXT("ActionComponent"));
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	check(ActionComponent);
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckFall();
}

/*---------------Movement---------------*/
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InputActions->JumpAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Jump);
		EnhancedInputComponent->BindAction(InputActions->JumpAction, ETriggerEvent::Completed, this, &ABaseCharacter::StopJumping);

		EnhancedInputComponent->BindAction(InputActions->MoveAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Move);

		EnhancedInputComponent->BindAction(InputActions->LookAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Look);

		EnhancedInputComponent->BindAction(InputActions->CrouchAction, ETriggerEvent::Triggered, this, &ABaseCharacter::StartCrouch);
		EnhancedInputComponent->BindAction(InputActions->CrouchAction, ETriggerEvent::Completed, this, &ABaseCharacter::StopCrouch);

		EnhancedInputComponent->BindAction(InputActions->SprintAction, ETriggerEvent::Triggered, this, &ABaseCharacter::StartSprint);
		EnhancedInputComponent->BindAction(InputActions->SprintAction, ETriggerEvent::Completed, this, &ABaseCharacter::StopSprint);
	}
}

void ABaseCharacter::CheckFall()
{
	if (GetActorLocation().Z < SomeThreshold)
	{
		TakeDamage(ActionComponent->GetHealth(), FDamageEvent{}, GetController(), this);
	}
}

void ABaseCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ABaseCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(-LookAxisVector.Y);
	}
}

void ABaseCharacter::StartCrouch()
{
	Crouch();
}

void ABaseCharacter::StopCrouch()
{
	UnCrouch();
}

void ABaseCharacter::Jump()
{
	Super::Jump();
}

void ABaseCharacter::StopJumping()
{
	Super::StopJumping();
}

void ABaseCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
}

void ABaseCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}
/*---------------------------------------*/