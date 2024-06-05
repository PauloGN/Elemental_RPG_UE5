// Copyright Paulo R Santos. GNS


#include "UI/HUD/ElementalHUD.h"
#include "UI/Widget/ElementalUserWidget.h"
#include "Blueprint/UserWidget.h"

void AElementalHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetSubClass);
	widget->AddToViewport();
}
