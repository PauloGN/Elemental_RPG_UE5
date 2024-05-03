// Copyright Paulo R Santos. GNS


#include "Character/ElementalCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AElementalCharacter::AElementalCharacter()
{
	UCharacterMovementComponent* cm = GetCharacterMovement();
	cm->bOrientRotationToMovement = true;
	cm->RotationRate = FRotator(0.f, 400.0f, 0.f);
	cm->bConstrainToPlane = true;
	cm->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetCapsuleComponent());
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = true;
}
