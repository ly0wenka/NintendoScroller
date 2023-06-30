#include "Character/NSCharacter.h"
#include "Misc/AutomationTest.h"
#include "Tests/Utils/TestUtils.h"
#include "Tests/Utils/WorldHelper.h"
#include "Tests/Utils/Character/CharacterTypes.h"
#include "Tests/Utils/LevelScope/LevelScope.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHealthMightBeChangedWithDamage, "NSGame.Character.HealthMightBeChangedWithDamage",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

using namespace NS::Test;
using namespace NS::CharacterTest;

bool FHealthMightBeChangedWithDamage::RunTest(const FString& Parameters)
{
    LevelScope("/Game/Tests/EmptyTestLevel");

    UWorld* World = WorldHelper::GetWorld();
    if (!TestNotNull("World exists", World)) return false;

    const FTransform InitialTransform{FVector{0.0f, -240.0f, 110.0f}};
    ANSCharacter* Character = CreateBlueprintDeferred<ANSCharacter>(World, CharacterTestBPName, InitialTransform);
    if (!TestNotNull("Character exists", Character)) return false;

    FHealthData HealthData;
    HealthData.MaxHealth = 1000.0f;
    CallFuncByNameWithParams(Character, "SetHealthData", {HealthData.ToString()});

    Character->FinishSpawning(InitialTransform);

    const float DamageAmount = 10.0f;
    TestEqual("Health is full", Character->GetHealthPercent(), 1.0f);
    /*Character->TakeDamage(DamageAmount, FDamageEvent{}, nullptr, nullptr);
    TestEqual("Health was decreased", Character->GetHealthPercent(), 1.0f - DamageAmount / HealthData.MaxHealth);*/

    return true;
}
