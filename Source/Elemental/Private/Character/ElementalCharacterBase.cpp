// Copyright Paulo R Santos. GNS

#include "Character/ElementalCharacterBase.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AElementalCharacterBase::AElementalCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AElementalCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

