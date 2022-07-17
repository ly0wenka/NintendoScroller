#include "NSGameSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogTPSGameSetting, All, All);

void UNSGameSettings::SetName(const FText& InName)
{
    Name = InName;
}

void UNSGameSettings::SetOptions(const TArray<FNSSettingOption>& InOptions)
{
    Options = InOptions;
}

FNSSettingOption UNSGameSettings::GetCurrentOption() const
{
    const int32 CurrentValue = GetCurrentValue();
    const auto Option = Options.FindByPredicate([&](const auto& Opt) { return CurrentValue == Opt.Value; });
    if (!Option)
    {
        UE_LOG(LogTPSGameSetting, Error, TEXT("Option doesn't exist"));
        return FNSSettingOption{};
    }
    return *Option;
}

FText UNSGameSettings::GetSettingName() const
{
    return Name;
}

void UNSGameSettings::AddGetter(TFunction<int32()> Func)
{
    Getter = Func;
}

void UNSGameSettings::AddSetter(TFunction<void(int32)> Func)
{
    Setter = Func;
}

void UNSGameSettings::ApplyNextOption()
{
    const int32 CurrentIndex = GetCurrentIndex();
    if (CurrentIndex == INDEX_NONE) return;

    const int32 NextIndex = (CurrentIndex + 1) % Options.Num();
    SetCurrentValue(Options[NextIndex].Value);
}

void UNSGameSettings::ApplyPrevOption()
{
    const int32 CurrentIndex = GetCurrentIndex();
    if (CurrentIndex == INDEX_NONE) return;

    const int32 PrevIndex = CurrentIndex == 0 ? Options.Num() - 1 : CurrentIndex - 1;
    SetCurrentValue(Options[PrevIndex].Value);
}

int32 UNSGameSettings::GetCurrentValue() const
{
    if (!Getter)
    {
        UE_LOG(LogTPSGameSetting, Error, TEXT("Getter func is not set for %s"), *Name.ToString());
        return INDEX_NONE;
    }
    return Getter();
}

void UNSGameSettings::SetCurrentValue(int32 Value) const
{
    if (!Setter)
    {
        UE_LOG(LogTPSGameSetting, Error, TEXT("Setter func is not set for %s"), *Name.ToString());
        return;
    }
    Setter(Value);
}

int32 UNSGameSettings::GetCurrentIndex() const
{
    const int32 CurrentValue = GetCurrentValue();
    return Options.IndexOfByPredicate([&](const auto& Opt) { return CurrentValue == Opt.Value; });
}