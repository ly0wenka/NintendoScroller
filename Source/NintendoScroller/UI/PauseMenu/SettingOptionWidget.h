// My game copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingOptionWidget.generated.h"

class UTextBlock;
class UNSGameSettings;
class UButton;

/**
 *
 */
UCLASS()
class USettingOptionWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* SettingDisplayName;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* SettingCurrentValue;

    UPROPERTY(meta = (BindWidget))
    UButton* NextSettingButton;

    UPROPERTY(meta = (BindWidget))
    UButton* PrevSettingButton;

    virtual void NativeOnInitialized() override;

private:
    TWeakObjectPtr<UNSGameSettings> Setting;

    void Init(UNSGameSettings* Setting);
    void UpdateTexts();

    UFUNCTION()
    void OnNextSetting();

    UFUNCTION()
    void OnPrevSetting();

    friend class UVideoSettingsWidget;
};
