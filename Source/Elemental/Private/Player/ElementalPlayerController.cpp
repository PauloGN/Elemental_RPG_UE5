// Copyright Paulo R Santos. GNS


#include "Player/ElementalPlayerController.h"
#include <Interaction/TargetInterface.h>
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/ElementalCharacter.h"
#include "GameFramework/SpringArmComponent.h"

namespace
{
	constexpr float MAX_ARM_LENGTH = 700.0f;
	constexpr float MIN_ARM_LENGTH = 150.0f;
	constexpr float ARM_LENGTH_RATE = 10.0f;
}

AElementalPlayerController::AElementalPlayerController()
{
	bReplicates = true;
}

void AElementalPlayerController::PlayerTick(float DeltaSeconds)
{
	Super::PlayerTick(DeltaSeconds);
	if (bShowMouseCursor)
	{
		CursorTrace();
	}
}

void AElementalPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//make sure to set in blueprint
	check(ElementalMappingContext);

	//Subsystems are singletons classes to handle specific services
	if (UEnhancedInputLocalPlayerSubsystem* subsystemInput = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		subsystemInput->AddMappingContext(ElementalMappingContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI inputModeData;
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(inputModeData);

	//Get USpringArm Comp
	// Get a reference to the character
	AElementalCharacter* elementalChar = Cast<AElementalCharacter>(GetPawn());

	if (elementalChar)
	{
		//Access the SpringArm component
		if (USpringArmComponent* springArm = elementalChar->FindComponentByClass<USpringArmComponent>())
		{
			CameraBoom = springArm;
		}
	}
}

void AElementalPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//Native input component cast to new Enhanced Input
	UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	enhancedInputComponent->BindAction(InputCameraAction, ETriggerEvent::Started, this, &ThisClass::AllowCameraMove);
	enhancedInputComponent->BindAction(InputCameraAction, ETriggerEvent::Completed, this, &ThisClass::AllowCameraMove);
	enhancedInputComponent->BindAction(ZoomIn, ETriggerEvent::Triggered, this, &ThisClass::ZoomInFun);
	enhancedInputComponent->BindAction(ZoomOut, ETriggerEvent::Triggered, this, &ThisClass::ZoomOutFun);
}

void AElementalPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D inputAxisVector = InputActionValue.Get<FVector2D>();

	const FRotator rotation = GetControlRotation();
	const FRotator yawRotation(0.0f, rotation.Yaw, 0.0f);

	const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightdDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* controlledPawn = GetPawn<APawn>())
	{
		controlledPawn->AddMovementInput(forwardDirection, inputAxisVector.Y);
		controlledPawn->AddMovementInput(rightdDirection, inputAxisVector.X);
	}
}

void AElementalPlayerController::Look(const FInputActionValue& InputActionValue)
{
	if (!bAllowCameraAction)
	{
		return;
	}

	// Get the input values
	const FVector2D lookAxisVector = InputActionValue.Get<FVector2D>();

	// Get the controlled pawn (assuming it's the character)
	APawn* controlledPawn = GetPawn();

	// Check if the controlled pawn exists and is of type AAuraCharacter
	if (controlledPawn && controlledPawn->IsA<AElementalCharacter>())
	{
		//Note: To control camera rotation SpringAmr should activate usePawnControlRotation as well inherit pitch, roll and yaw
		controlledPawn->AddControllerYawInput(lookAxisVector.X);
		controlledPawn->AddControllerPitchInput(-lookAxisVector.Y);
	}
}

void AElementalPlayerController::AllowCameraMove(const FInputActionValue& InputActionValue)
{
	bAllowCameraAction = InputActionValue.Get<bool>();

	if (bAllowCameraAction)
	{
		bShowMouseCursor = false;
		GEngine->AddOnScreenDebugMessage(1, 10, FColor::Blue, "Down");
		FInputModeGameOnly gameInput;
		gameInput.SetConsumeCaptureMouseDown(true);
		SetInputMode(gameInput);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 10, FColor::Blue, "Up");
		bShowMouseCursor = true;
		DefaultMouseCursor = EMouseCursor::Default;

		FInputModeGameAndUI inputModeData;

		inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		inputModeData.SetHideCursorDuringCapture(false);
		SetInputMode(inputModeData);
	}
}

void AElementalPlayerController::ZoomInFun()
{
	CameraBoom->TargetArmLength -= ARM_LENGTH_RATE;
	if (CameraBoom->TargetArmLength <= MIN_ARM_LENGTH)
	{
		CameraBoom->TargetArmLength = MIN_ARM_LENGTH;
	}
}

void AElementalPlayerController::ZoomOutFun()
{
	CameraBoom->TargetArmLength += ARM_LENGTH_RATE;
	if (CameraBoom->TargetArmLength >= MAX_ARM_LENGTH)
	{
		CameraBoom->TargetArmLength = MAX_ARM_LENGTH;
	}
}

void AElementalPlayerController::CursorTrace()
{
	FHitResult cursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, cursorHit);

	if (!cursorHit.bBlockingHit)
	{
		if(ThisActor)
		{
			ThisActor->UnHighlightActor();
			ThisActor = nullptr;
		}
		return;
	}

	LastActor = ThisActor;
	//The Wrapper "TScriptInterface" allows you to get the correct type without casting
	ThisActor = cursorHit.GetActor();

	/**
	 *	Line trace from cursor. There are several scenarios
	 *	A. Last actor is null and this actor is null
	 *		- Do nothing
	 *	B. LastActor is null && thisAcor  is valid
	 *		- Highlight thisActor
	 *	C. lastActor is valid && thisActor is null
	 *		- UnHighlight lastActor
	 *	D. Both actors are Valid, but lastActor != thisActor
	 * 		- UnHighlight lastActor, and Highlight thisActor
	 *	E. Both actors are Valid, and lastActor == thisActor
	 *		- Do nothing
	 */

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			//case b
			ThisActor->HighlightActor();
		}
		else
		{
			//case a -> Both are null
		}
	}
	else
	{
		if (ThisActor == nullptr)
		{
			//case c
			LastActor->UnHighlightActor();
		}
		else//both actors are not null (both are valid)
		{
			if (LastActor != ThisActor)
			{
				//case d
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				//case E do nothing
			}
		}
	}
}
