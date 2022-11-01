#pragma once

#include "CoreMinimal.h"
#include "InventoryItemType.generated.h"

UENUM(BlueprintType)
enum class EInventoryItemType : uint8
{
    SPHERE = 0 UMETA(DisplayName = "MY COOL SPHERE"),
    CUBE UMETA(DisplayName = "MY COOL CUBE"),
    CYLINDER,
    CONE,
    Coin,
    MagicMushroom,
    FireFlower,
    Mushroom1up,
    StarMan,
};