#include "NSPlayerController.h"
#include "NSCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void ANSPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    check(InputComponent);
    InputComponent->BindAction("ToggleGamePause", IE_Pressed, this, &ThisClass::ToggleGamePause).bExecuteWhenPaused = true;
}

void ANSPlayerController::ToggleGamePause()
{
    bInPause = !bInPause;
    SetPause(bInPause);
    bShowMouseCursor = bInPause;
    bInPause                                                                     //
        ? SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false))  //
        : SetInputMode(FInputModeGameOnly());
    OnGamePause.Broadcast(bInPause);
}
