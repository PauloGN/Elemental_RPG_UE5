// Copyright Paulo R Santos. GNS


#include "Character/ElementalCharacter.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/ElementalPlayerController.h"
#include "Player/ElementalPlayerState.h"
#include "UI/HUD/ElementalHUD.h"

AElementalCharacter::AElementalCharacter()
{
	UCharacterMovementComponent* cm = GetCharacterMovement();
	cm->bOrientRotationToMovement = true;
	cm->RotationRate = FRotator(0.f, 300.0f, 0.f);
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

void AElementalCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Init Ability actor info for the server
	InitAbilityActorInfo();
}

void AElementalCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Init Ability actor info for the clients
	InitAbilityActorInfo();
}

void AElementalCharacter::InitAbilityActorInfo()
{
	AElementalPlayerState* ElementalPlayerState = GetPlayerState<AElementalPlayerState>();

	check(ElementalPlayerState);
	//Set pointers
	AbilitySystemComponent = ElementalPlayerState->GetAbilitySystemComponent();
	AttributeSet = ElementalPlayerState->GetAttributeSet();
	//Init Actor info for ability system component
	AbilitySystemComponent->InitAbilityActorInfo(ElementalPlayerState, this);

	//HUD - Overlay - Widget controller set
	if(AElementalPlayerController* ElementalPlayerController = Cast<AElementalPlayerController>(GetController()))
	{
		if(AElementalHUD* ElementalHUD = Cast<AElementalHUD>(ElementalPlayerController->GetHUD()))
		{
			ElementalHUD->InitOverlay(ElementalPlayerController, ElementalPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}