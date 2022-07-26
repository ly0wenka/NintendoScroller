#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include <GameplayEffectTypes.h>
#include "NintendoScroller.h"
#include "Components/GameplayAbilitySystem/GASAttributes.h"
#include "Types/HealthData.h"
#include "NSCharacter.generated.h"

//class UGASComponent;
//class UGASAttributes;
class UNSInventoryComponent;
class UDamageType;
class AController;
class USpringArmComponent;
class UCameraComponent;
class UInputComponent;

UCLASS(config = Game)
class ANSCharacter : public ACharacter//, public IAbilitySystemInterface
{
public:
    //virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;// override;
    void SetPlayerIsALive(bool bCond);
private:
    GENERATED_BODY()

    /** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* CameraBoom;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FollowCamera;
public:
    // UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
    //     Category="haracter")
    // UGASComponent* GASComponent;
    //
    // UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
    //     Category="haracter")
    // UGASAttributes* GASAttributes;
    //
    // UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="haracter")
    // TArray<AActor*> ArmorSetItems;
    //
    // UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="haracter")
    // EWeaponType WeaponBeingUsed;
public:

    ANSCharacter();

    /** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    float BaseTurnRate;

    /** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    float BaseLookUpRate;

protected:
    /** Resets HMD orientation in VR. */
    void OnResetVR();

    /** Called for forwards/backward input */
    virtual void MoveForward(float Value);

    /** Called for side to side input */
    void MoveRight(float Value);

    /**
     * Called via input to turn at a given rate.
     * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
     */
    void TurnAtRate(float Rate);

    /**
     * Called via input to turn look up/down at a given rate.
     * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
     */
    virtual void LookUpAtRate(float Rate);

    /** Handler for when a touch input begins. */
    void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

    /** Handler for when a touch input stops. */
    void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:

    // APawn interface
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    // End of APawn interface

public:
    /** Returns CameraBoom subobject **/
    FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    /** Returns FollowCamera subobject **/
    FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

    UFUNCTION(BlueprintCallable, Category = "Health" /*, meta = (BlueprintProtected = "true")*/)
    float GetHealthPercent() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UNSInventoryComponent* InventoryComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    FHealthData HealthData;

    virtual void BeginPlay() override;

private:
    float Health{0.0f};
    FTimerHandle HealTimerHandle;

    UFUNCTION() void OnAnyDamageReceived(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

    void OnHealing();
    void OnDeath();
};
