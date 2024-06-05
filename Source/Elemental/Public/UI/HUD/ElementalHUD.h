// Copyright Paulo R Santos. GNS

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ElementalHUD.generated.h"

class UElementalUserWidget;
/**
 * 
 */
UCLASS()
class ELEMENTAL_API AElementalHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<UElementalUserWidget> Overlaywidget;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UElementalUserWidget> OverlayWidgetSubClass;

};
