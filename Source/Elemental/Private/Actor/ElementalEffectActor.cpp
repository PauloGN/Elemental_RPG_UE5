// Copyright Paulo R Santos. GNS


#include "Actor/ElementalEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Components/SphereComponent.h"
#include "GAS/ElementalAttributeSet.h"

AElementalEffectActor::AElementalEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(Mesh);
}

void AElementalEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UElementalAttributeSet* ElementalAttributeSet = Cast<UElementalAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UElementalAttributeSet::StaticClass()));

		//BIG NO NO cast away constancy
		UElementalAttributeSet* MutableElementalAttributeSet = const_cast<UElementalAttributeSet*>(ElementalAttributeSet);
		MutableElementalAttributeSet->SetHealth(ElementalAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AElementalEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{


	}
}

void AElementalEffectActor::BeginPlay()
{
	Super::BeginPlay();

	//Bind function to overlap events
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AElementalEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AElementalEffectActor::EndOverlap);
}
