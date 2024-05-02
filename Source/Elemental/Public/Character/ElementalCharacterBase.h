// Copyright Paulo R Santos. GNS

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ElementalCharacterBase.generated.h"

UCLASS(Abstract)
class ELEMENTAL_API AElementalCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:

	AElementalCharacterBase();

protected:

	virtual void BeginPlay() override;

};
