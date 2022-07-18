
#include "GASAttributes.h"
#include "Character/NSCharacter.h"

UGASAttributes::UGASAttributes()
{
    MaxHealth = 100.f;
    Health = MaxHealth;
    MaxSpeed = 600.f;
    Speed = MaxSpeed;
    MaxStamina = 100.f; 
    Stamina = MaxStamina;
    ISShouldResetStamina = false; MaxStrength = 10.f;
    Strength = MaxStrength;
    MaxMP = 100.f; 
    MP = MaxMP; 
}

bool UGASAttributes::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
    Super::PreGameplayEffectExecute(Data);
    return true;
}

FGameplayAttribute (*funcGetGAttrPtr)();
float (*funcGetAttrPtr)();


#include "GameplayEffectExtension.h"
void UGASAttributes::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data); // Clamp the current Attribute values so that the minimum amount of Health it is © ond maximum should be max version of them
    if(Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), .0f, MaxHealth)); // KILL Player if Health reaches 6
        ANSCharacter* Player = Cast<ANSCharacter>(Data.Target.GetOwnerActor());
        if(Player && GetHealth() <= 0.f)
        {
            Player->SetPlayerIsALive(false);
        }
    }

    if(Data.EvaluatedData.Attribute == GetStrengthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), .0f, MaxHealth));
    }
}