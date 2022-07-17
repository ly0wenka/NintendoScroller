// Copyright Epic Games, Inc. All Rights Reserved.

#include "NSGameMode.h"
#include "Character/NSCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANSGameMode::ANSGameMode()
{
    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerBP/Blueprints/Character/BP_SideScrollerCharacter"));
    if (PlayerPawnBPClass.Class != nullptr)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}