// Copyright Paulo R Santos. GNS

#include "Character/ElementalCharacterBase.h"

// Sets default values
AElementalCharacterBase::AElementalCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AElementalCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

