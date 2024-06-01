// Copyright Paulo R Santos. GNS

#pragma once

#include "CoreMinimal.h"
#include "Character/ElementalCharacterBase.h"
#include "ElementalCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTAL_API AElementalCharacter : public AElementalCharacterBase
{
	GENERATED_BODY()

public:

	AElementalCharacter();

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USpringArmComponent> CameraBoom;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:

	void InitAbilityActorInfo();
};
