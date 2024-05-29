// Copyright Paulo R Santos. GNS


#include "Player/ElementalPlayerState.h"

#include "GAS/ElementalAbilitySystemComponent.h"
#include "GAS/ElementalAttributeSet.h"

AElementalPlayerState::AElementalPlayerState()
{
	NetUpdateFrequency = 100;

	AbilitySystemComponent = CreateDefaultSubobject<UElementalAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UElementalAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AElementalPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AElementalPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
