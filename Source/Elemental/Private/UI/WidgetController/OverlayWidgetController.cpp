// Copyright Paulo R Santos. GNS


#include "UI/WidgetController/OverlayWidgetController.h"
#include "GAS/ElementalAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UElementalAttributeSet* ElementalAS = CastChecked<UElementalAttributeSet>(AttributeSet);

	//Broad cast initial values
	OnHealthChanged.Broadcast(ElementalAS->GetHealth());
	OnMaxHealthChanged.Broadcast(ElementalAS->GetMaxHealth());

	OnManaChanged.Broadcast(ElementalAS->GetMana());
	OnMaxManaChanged.Broadcast(ElementalAS->GetMaxMana());
}

void UOverlayWidgetController::BindCallBacksToDependencies()
{
	const UElementalAttributeSet* ElementalAS = CastChecked<UElementalAttributeSet>(AttributeSet);

	//Response to the act of changing attributes
	//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ElementalAS->GetHealthAttribute()).AddUObject(this, );
	//These Functions will be called when the attributes change

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ElementalAS->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ElementalAS->GetMaxHealthAttribute()).AddUObject(this,&UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ElementalAS->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ElementalAS->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);

}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	//NOTE: Data.NewValue is the changed value from the attribute.
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
