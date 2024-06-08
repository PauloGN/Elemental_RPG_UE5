// Copyright Paulo R Santos. GNS

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/ElementalWidgetController.h"
#include "OverlayWidgetController.generated.h"
/**
 *	Dynamic allows to assign event to them in blueprints
 *	Multicast means that multiple widget blueprints may want to bind to these delegates
 */
//DELEGATES

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ELEMENTAL_API UOverlayWidgetController : public UElementalWidgetController
{
	GENERATED_BODY()

public:

	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
	
};
