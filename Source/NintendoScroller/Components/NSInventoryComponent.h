#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPS/TPSTypes.h"
#include "NSInventoryComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TPS_API UNSInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UNSInventoryComponent();

    bool TryToAddItem(const FInventoryData& Data);

    UFUNCTION(BlueprintCallable)
    int32 GetInventoryAmountByType(EInventoryItemType Type) const;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TMap<EInventoryItemType, int32> InventoryLimits;

private:
    TMap<EInventoryItemType, int32> Inventory;
};