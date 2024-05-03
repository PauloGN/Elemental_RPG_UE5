// Copyright Paulo R Santos. GNS


#include "Player/ElementalPlayerController.h"
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
	check(ElementalContext);

	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (subsystem)
	{
		subsystem->AddMappingContext(ElementalContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI inputModeData;
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(inputModeData);

	//Get USpringArm Comp
	// Get a reference to the character
	AElementalCharacter* ElementalChar = Cast<AElementalCharacter>(GetPawn());

	if (ElementalChar)
	{
		// Access the SpringArm component
		USpringArmComponent* SpringArm = ElementalChar->FindComponentByClass<USpringArmComponent>();
		if (SpringArm)
		{
			CameraBoom = SpringArm;
		}
	}
}

void AElementalPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

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
	const FVector2D InputAAxisVector = InputActionValue.Get<FVector2D>();

	const FRotator rotation = GetControlRotation();
	const FRotator yawRotation(0.0f, rotation.Yaw, 0.0f);

	const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightdDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* controlledPawn = GetPawn<APawn>())
	{
		controlledPawn->AddMovementInput(forwardDirection, InputAAxisVector.Y);
		controlledPawn->AddMovementInput(rightdDirection, InputAAxisVector.X);
	}
}

void AElementalPlayerController::Look(const FInputActionValue& InputActionValue)
{
	if (!bAllowCameraAction)
	{
		return;
	}

	// Get the input values
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	// Get the controlled pawn (assuming it's the character)
	APawn* ControlledPawn = GetPawn();

	// Check if the controlled pawn exists and is of type AAuraCharacter
	if (ControlledPawn && ControlledPawn->IsA<AElementalCharacter>())
	{
		//Note: To control camera rotation SpringAmr should activate usePawnControlRotation as well inherit pitch, roll and yaw
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
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

void AElementalPlayerController::ZoomInFun(const FInputActionValue& InputActionValue)
{
	CameraBoom->TargetArmLength -= ARM_LENGTH_RATE;
	if (CameraBoom->TargetArmLength <= MIN_ARM_LENGTH)
	{
		CameraBoom->TargetArmLength = MIN_ARM_LENGTH;
	}
}

void AElementalPlayerController::ZoomOutFun(const FInputActionValue& InputActionValue)
{
	CameraBoom->TargetArmLength += ARM_LENGTH_RATE;
	if (CameraBoom->TargetArmLength >= MAX_ARM_LENGTH)
	{
		CameraBoom->TargetArmLength = MAX_ARM_LENGTH;
	}
}

void AElementalPlayerController::CursorTrace()
{
	//FHitResult cursorHit;
	//GetHitResultUnderCursor(ECC_Visibility, false, cursorHit);

	//if (!cursorHit.bBlockingHit)
	//{
	//	return;
	//}

	//LastActor = ThisActor;
	//ThisActor = Cast<ITargetInterface>(cursorHit.GetActor());

	///**
	// *	Line trace from cursor. There are several scenarios
	// *	A. Last actor is null and this actor is null
	// *		- Do nothing
	// *	B. LastActor is null && thisAcor  is valid
	// *		- Highlight thisActor
	// *	C. lastActor is valid && thisActor is null
	// *		- UnHighlight lastActor
	// *	D. Both actors are Valid, but lastActor != thisActor
	// * 		- UnHighlight lastActor, and Highlight thisActor
	// *	E. Both actors are Valid, and lastActor == thisActor
	// *		- Do nothing
	// */

	//if (LastActor == nullptr)
	//{
	//	if (ThisActor != nullptr)
	//	{
	//		//case b
	//		ThisActor->HighlightActor();
	//	}
	//	else
	//	{
	//		//case a -> Both are null
	//	}
	//}
	//else
	//{
	//	if (ThisActor == nullptr)
	//	{
	//		//case c
	//		LastActor->UnHighlightActor();
	//	}
	//	else//both actors are not null (both are valid)
	//	{
	//		if (LastActor != ThisActor)
	//		{
	//			//case d
	//			LastActor->UnHighlightActor();
	//			ThisActor->HighlightActor();
	//		}
	//		else
	//		{
	//			//case E do nothing
	//		}
	//	}
	//}
}
