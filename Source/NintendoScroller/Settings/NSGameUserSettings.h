// My game copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "NSGameUserSettings.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSettingsUpdatedDelegate);

/**
 *
 */
UCLASS()
class TPS_API UNSGameUserSettings : public UGameUserSettings
{
    GENERATED_BODY()

public:
    UNSGameUserSettings();
    static UNSGameUserSettings* Get();

    const TArray<class UNSGameSetting*>& GetVideoSettings() const;

    void RunBenchmark();

    FOnSettingsUpdatedDelegate OnVideoSettingsUpdated;

private:
    UPROPERTY()
    TArray<class UNSGameSetting*> VideoSettings;
};
 
