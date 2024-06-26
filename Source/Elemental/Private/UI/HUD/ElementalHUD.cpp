// Copyright Paulo R Santos. GNS


#include "UI/HUD/ElementalHUD.h"
#include "UI/Widget/ElementalUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "Blueprint/UserWidget.h"

UOverlayWidgetController* AElementalHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{

	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerSubClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallBacksToDependencies();
	}

	return OverlayWidgetController;
}

void AElementalHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC,
	UAttributeSet* AS)
{

	checkf(OverlayWidgetSubClass, TEXT("Overlay widget tsubclass of Uninitialized, please check BP_ElementalHUD"));
	checkf(OverlayWidgetControllerSubClass, TEXT("Overlay widget controller tsubclass of Uninitialized, please check BP_ElementalHUD"));

	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetSubClass);
	OverlayWidget = Cast<UElementalUserWidget>(widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);

	//All set
	WidgetController->BroadcastInitialValues();

	widget->AddToViewport();
}
