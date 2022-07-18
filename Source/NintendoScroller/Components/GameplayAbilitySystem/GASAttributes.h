#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"

#include "GASAttributes.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/*
 */
UCLASS()
class UGASAttributes : public UAttributeSet
{
	GENERATED_BODY()

public:
	UGASAttributes();

    /**
     *	Called just before modifying the value of an attribute. AttributeSet can make additional modifications here. Return true to continue, or false to throw out the modification.
     *	Note this is only called during an 'execute'. E.g., a modification to the 'base value' of an attribute. It is not called during an application of a GameplayEffect, such as a 5 ssecond +10 movement speed buff.
     */	
    virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData &Data) override ;
	
    /**
     *	Called just before a GameplayEffect is executed to modify the base value of an attribute. No more changes can be made.
     *	Note this is only called during an 'execute'. E.g., a modification to the 'base value' of an attribute. It is not called during an application of a GameplayEffect, such as a 5 ssecond +10 movement speed buff.
     */
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData &Data) override ;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameplayAbilitySystem|Attributes")
    float MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameplayAbilitySystem|Attributes")
    float MaxStrength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameplayAbilitySystem|Attributes")
    float MaxStamina;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameplayAbilitySystem|Attributes")
    float MaxMP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameplayAbilitySystem|Attributes")
    float MaxSpeed;

    UPROPERTY() FGameplayAttributeData Health;   ATTRIBUTE_ACCESSORS(UGASAttributes, Health) //
    UPROPERTY() FGameplayAttributeData Strength; ATTRIBUTE_ACCESSORS(UGASAttributes, Strength) //
    UPROPERTY() FGameplayAttributeData Stamina;  ATTRIBUTE_ACCESSORS(UGASAttributes, Stamina) //
    UPROPERTY() FGameplayAttributeData MP;  ATTRIBUTE_ACCESSORS(UGASAttributes, MP) //
    UPROPERTY() FGameplayAttributeData Speed;  ATTRIBUTE_ACCESSORS(UGASAttributes, Speed) //
    UPROPERTY() bool ISShouldResetStamina;
};
