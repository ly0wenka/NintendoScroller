// My game copyright

#include "Components/NSInventoryComponent.h"

UNSInventoryComponent::UNSInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

bool UNSInventoryComponent::TryToAddItem(const FInventoryData& Data)
{
    if (Data.Score < 0) return false;

    if (!Inventory.Contains(Data.Type))
    {
        Inventory.Add(Data.Type, 0);
    }

    const auto NextScore = Inventory[Data.Type] + Data.Score;
    if (NextScore > InventoryLimits[Data.Type]) return false;

    Inventory[Data.Type] = NextScore;

    return true;
}

int32 UNSInventoryComponent::GetInventoryAmountByType(EInventoryItemType Type) const
{
    return Inventory.Contains(Type) ? Inventory[Type] : 0;
}

void UNSInventoryComponent::BeginPlay()
{
    Super::BeginPlay();

//#if !UE_BUILD_SHIPPING
//    const UEnum* InvEnum = StaticEnum<EInventoryItemType>();
//    check(InvEnum);
//    for (int32 i = 0; i < InvEnum->NumEnums() - 1; ++i)
//    {
//        const EInventoryItemType EnumElem = static_cast<EInventoryItemType>(i);
//        const FString EnumElemName = UEnum::GetValueAsString(EnumElem);
//        const bool LimitCheckCond = InventoryLimits.Contains(EnumElem) && InventoryLimits[EnumElem] >= 0;
//        checkf(LimitCheckCond, TEXT("Limit for %s doesn't exist or less then zero"), *EnumElemName);
//    }
//#endif
}