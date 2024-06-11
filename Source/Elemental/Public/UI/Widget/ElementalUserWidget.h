// Copyright Paulo R Santos. GNS

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ElementalUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTAL_API UElementalUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();

};
