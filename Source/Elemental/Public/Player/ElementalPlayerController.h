// Copyright Paulo R Santos. GNS

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ElementalPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class ITargetInterface;
/**
 * 
 */
UCLASS()
class ELEMENTAL_API AElementalPlayerController : public APlayerController
{
	GENERATED_BODY()


public:

	AElementalPlayerController();

	virtual void PlayerTick(float DeltaSeconds) override;

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:

#pragma region INPUTS

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> ElementalContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> InputCameraAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ZoomIn;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ZoomOut;

	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	void AllowCameraMove(const FInputActionValue& InputActionValue);

	void ZoomInFun(const FInputActionValue& InputActionValue);
	void ZoomOutFun(const FInputActionValue& InputActionValue);
#pragma endregion

	void CursorTrace();
	TObjectPtr <ITargetInterface> LastActor;
	TObjectPtr <ITargetInterface>  ThisActor;

	bool bAllowCameraAction = false;
	TObjectPtr<class USpringArmComponent> CameraBoom;
};
