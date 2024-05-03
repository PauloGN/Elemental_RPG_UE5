// Copyright Paulo R Santos. GNS


#include "Character/ElementalEnemy.h"
#include "Elemental/Elemental.h"

void AElementalEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), 50, 20, FColor::Red, false, 2);

	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AElementalEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}
