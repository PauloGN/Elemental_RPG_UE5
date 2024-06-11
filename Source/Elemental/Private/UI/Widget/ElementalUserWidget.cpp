// Copyright Paulo R Santos. GNS


#include "UI/Widget/ElementalUserWidget.h"

void UElementalUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
