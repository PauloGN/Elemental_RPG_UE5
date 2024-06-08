// Copyright Paulo R Santos. GNS


#include "UI/WidgetController/OverlayWidgetController.h"

#include "GAS/ElementalAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UElementalAttributeSet* ElementalAS = CastChecked<UElementalAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(ElementalAS->GetHealth());
	OnMaxHealthChanged.Broadcast(ElementalAS->GetMaxHealth());
}
