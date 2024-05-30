// Copyright Paulo R Santos. GNS


#include "Player/ElementalPlayerState.h"

#include "GAS/ElementalAbilitySystemComponent.h"
#include "GAS/ElementalAttributeSet.h"

AElementalPlayerState::AElementalPlayerState()
{
	NetUpdateFrequency = 100;

	AbilitySystemComponent = CreateDefaultSubobject<UElementalAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	//How Game play effects will be replicated to clients
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

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
