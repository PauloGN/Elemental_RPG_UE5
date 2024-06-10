// Copyright Paulo R Santos. GNS

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ElementalHUD.generated.h"

class UElementalUserWidget;
class UOverlayWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class ELEMENTAL_API AElementalHUD : public AHUD
{
	GENERATED_BODY()

public:

	//behave as a singleton
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	//~ Pointer and subclass WIDGET to set from blueprint
	UPROPERTY()
	TObjectPtr<UElementalUserWidget> OverlayWidget;

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UElementalUserWidget> OverlayWidgetSubClass;
	// ~End

	//~ Pointer and subclass CONTROLLER to set from blueprint
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerSubClass;
	//~ End
};
