#pragma once

#include "CoreMinimal.h"
#include "NSSettingOption.h"
#include "UObject/Object.h"

#include "NSGameSettings.generated.h"

UCLASS()
class UNSGameSettings : public UObject
{
	GENERATED_BODY()

public:
    void SetName(const FText& Name);
    void SetOptions(const TArray<FNSSettingOption>& Options);

    FNSSettingOption GetCurrentOption() const;
    FText GetSettingName() const;
    void AddGetter(TFunction<int32()> Func);
    void AddSetter(TFunction<void(int32)> Func);

    void ApplyNextOption();
    void ApplyPrevOption();

private:
    FText Name;
    TArray<FNSSettingOption> Options;
    TFunction<int32()> Getter;
    TFunction<void(int32)> Setter;

    int32 GetCurrentValue() const;
    void SetCurrentValue(int32 Value) const;
    int32 GetCurrentIndex() const;
};