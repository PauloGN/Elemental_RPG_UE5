// Copyright Paulo R Santos. GNS


#include "Character/ElementalEnemy.h"
#include "Elemental/Elemental.h"
#include "GAS/ElementalAbilitySystemComponent.h"
#include "GAS/ElementalAttributeSet.h"

AElementalEnemy::AElementalEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UElementalAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	//How Game play effects will be replicated to clients
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UElementalAttributeSet>("AttributeSet");
}

void AElementalEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), 50, 20, FColor::Red, false, 2);
	if(Weapon)
	{
		Weapon->SetRenderCustomDepth(true);
		Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
}

void AElementalEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);

	if(Weapon)
	{
		Weapon->SetRenderCustomDepth(false);
	}
}
