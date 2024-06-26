// Copyright Paulo R Santos. GNS

#pragma once

#include "CoreMinimal.h"
#include "Character/ElementalCharacterBase.h"
#include "Interaction/TargetInterface.h"
#include "ElementalEnemy.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTAL_API AElementalEnemy : public AElementalCharacterBase, public ITargetInterface
{
	GENERATED_BODY()

public:
	
	AElementalEnemy();
#pragma region INTERFACES
	//Target Interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
#pragma endregion

protected:

	virtual void BeginPlay() override;
};
