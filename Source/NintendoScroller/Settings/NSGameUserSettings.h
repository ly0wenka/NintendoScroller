// My game copyright

#pragma once

#include "CoreMinimal.h"
#include "NSGameSettings.h"
#include "GameFramework/GameUserSettings.h"
#include "NSGameUserSettings.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSettingsUpdatedDelegate);

/**
 *
 */
UCLASS()
class UNSGameUserSettings : public UGameUserSettings
{
    GENERATED_BODY()

public:
    UNSGameUserSettings();
    static UNSGameUserSettings* Get();

    const TArray<UNSGameSettings*>& GetVideoSettings() const;

    void RunBenchmark();

    FOnSettingsUpdatedDelegate OnVideoSettingsUpdated;

private:
    UPROPERTY()
    TArray<UNSGameSettings*> VideoSettings;
};
 
