// Copyright Paulo R Santos. GNS


#include "Character/ElementalEnemy.h"
#include "Elemental/Elemental.h"

AElementalEnemy::AElementalEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
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
