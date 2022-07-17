// My game copyright

#include "UI/PauseMenu/PauseMenuWidget.h"
#include "Components/Button.h"

void UPauseMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    check(CloseMenuButton);
    CloseMenuButton->OnClicked.AddDynamic(this, &ThisClass::OnCloseMenu);
}

void UPauseMenuWidget::OnCloseMenu()
{
    if (!GetWorld()) return;

    if (auto* PC = Cast<ANSPlayerController>(GetWorld()->GetFirstPlayerController()))
    {
        PC->ToggleGamePause();
    }
}
