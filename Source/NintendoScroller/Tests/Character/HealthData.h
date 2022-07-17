#pragma once

#include "CoreMinimal.h"
#include "HealthData.generated.h"

USTRUCT(BlueprintType)
struct FHealthData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1.0"))
    float MaxHealth{100.0f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.1"))
    float HealModifier{10.0f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.1", Units = "s"))
    float HealRate{0.5f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.1", Units = "s"))
    float LifeSpan{5.0f};

    [[nodiscard]] FString ToString() const
    {                                                                                           //
        return FString::Printf(TEXT("(MaxHealth=%f,HealModifier=%f,HealRate=%f,LifeSpan=%f)"),  //
            MaxHealth,                                                                          //
            HealModifier,                                                                       //
            HealRate,                                                                           //
            LifeSpan                                                                            //
        );
    }
};