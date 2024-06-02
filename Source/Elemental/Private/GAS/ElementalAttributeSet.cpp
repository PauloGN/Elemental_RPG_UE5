// Copyright Paulo R Santos. GNS


#include "GAS/ElementalAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

UElementalAttributeSet::UElementalAttributeSet()
{
}

void UElementalAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Vital Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UElementalAttributeSet, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UElementalAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UElementalAttributeSet, Mana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UElementalAttributeSet, MaxMana, COND_None, REPNOTIFY_Always)
}

void UElementalAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UElementalAttributeSet, Health, OldHealth)
}

void UElementalAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UElementalAttributeSet, MaxHealth, OldMaxHealth)

}

void UElementalAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UElementalAttributeSet, Mana, OldMana)
}

void UElementalAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UElementalAttributeSet, MaxMana, OldMaxMana)
}
