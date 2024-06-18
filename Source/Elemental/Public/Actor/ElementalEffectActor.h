// Copyright Paulo R Santos. GNS

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElementalEffectActor.generated.h"

class USphereComponent;

UCLASS()
class ELEMENTAL_API AElementalEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AElementalEffectActor();

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
	
};

#pragma region  DELETED CODE
#pragma endregion