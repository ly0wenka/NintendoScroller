// My game copyright

#include "UI/PauseMenu/SettingOptionWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Settings/NSGameSettings.h"

void USettingOptionWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    check(SettingDisplayName);
    check(SettingCurrentValue);
    check(NextSettingButton);
    check(PrevSettingButton);

    NextSettingButton->OnClicked.AddDynamic(this, &ThisClass::OnNextSetting);
    PrevSettingButton->OnClicked.AddDynamic(this, &ThisClass::OnPrevSetting);
}

void USettingOptionWidget::Init(UNSGameSettings* InSetting)
{
    Setting = MakeWeakObjectPtr(InSetting);
    check(Setting.IsValid());

    UpdateTexts();
}

void USettingOptionWidget::UpdateTexts()
{
    if (Setting.IsValid())
    {
        SettingDisplayName->SetText(FText::FromString(Setting->GetName()));
        SettingCurrentValue->SetText(Setting->GetCurrentOption().Name);
    }
}

void USettingOptionWidget::OnNextSetting()
{
    if (Setting.IsValid())
    {
        Setting->ApplyNextOption();
        SettingCurrentValue->SetText(Setting->GetCurrentOption().Name);
    }
}

void USettingOptionWidget::OnPrevSetting()
{
    if (Setting.IsValid())
    {
        Setting->ApplyPrevOption();
        SettingCurrentValue->SetText(Setting->GetCurrentOption().Name);
    }
}
