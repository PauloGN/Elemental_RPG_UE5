// Copyright Paulo R Santos. GNS


#include "UI/WidgetController/ElementalWidgetController.h"

void UElementalWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UElementalWidgetController::BroadcastInitialValues()
{
}
