#include "Character/NSCharacter.h"
#include "Misc/AutomationTest.h"
#include "Tests/Utils/TestUtils.h"
#include "Tests/Utils/WorldHelper.h"
#include "Tests/Utils/BlueprintHelper/BlueprintHelper.h"
#include "Tests/Utils/LevelScope/LevelScope.h"
#include "Tests/Utils/Character/CharacterTypes.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAutoHealShouldRestoreHealth, "NSGame.Character.AutoHealShouldRestoreHealth",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

using namespace NS::Test;
using namespace NS::CharacterTest;

DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FAutoHealCheckLatentCommand, ANSCharacter*, Character, float, HealingDuration);
bool FAutoHealCheckLatentCommand::Update()
{
    const double NewTime = FPlatformTime::Seconds();
    if (NewTime - StartTime >= HealingDuration)
    {
        if (!FMath::IsNearlyEqual(Character->GetHealthPercent(), 1.0f))
        {
            UE_LOG(LogNSCharacterTests, Error, TEXT("Health is not full"));
        }
        return true;
    }
    return false;
}

bool FAutoHealShouldRestoreHealth::RunTest(const FString& Parameters)
{
    const auto Level = LevelScope("/Game/SideScrollerBP/Maps/Level_1-1");

    UWorld* World = WorldHelper::GetWorld();
    if (!TestNotNull("World exists", World)) return false;

    const FTransform InitialTransform{FVector{0.0f, -240.0f, 110.0f}};
    ANSCharacter* Character = BlueprintHelper::CreateBlueprintDeferred<ANSCharacter>(World, CharacterTestBPName, InitialTransform);
    if (!TestNotNull("Character exists", Character)) return false;

    FHealthData HealthData;
    HealthData.MaxHealth = 200.0f;
    HealthData.HealModifier = 5.0f;
    HealthData.HealRate = 0.5f;
    CallFuncByNameWithParams(Character, "SetHealthData", {HealthData.ToString()});

    Character->FinishSpawning(InitialTransform);

    const float DamageAmount = 20.0f;
    TestEqual("Health is full", Character->GetHealthPercent(), 1.0f);
    Character->TakeDamage(DamageAmount, FDamageEvent{}, nullptr, nullptr);
    TestEqual("Health was decreased", Character->GetHealthPercent(), 1.0f - DamageAmount / HealthData.MaxHealth);

    const float HealthDiff = HealthData.MaxHealth * (1.0f - Character->GetHealthPercent());
    const float HealingDuration = HealthData.HealRate * HealthDiff / HealthData.HealModifier;
    // ADD_LATENT_AUTOMATION_COMMAND(FAutoHealCheckLatentCommand(Character, HealingDuration));

    ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand(
        [Character]()
        {
            if (!FMath::IsNearlyEqual(Character->GetHealthPercent(), 1.0f))
            {
                UE_LOG(LogNSCharacterTests, Error, TEXT("Health is not full"));
            }
        },
        HealingDuration));

    return true;
}
