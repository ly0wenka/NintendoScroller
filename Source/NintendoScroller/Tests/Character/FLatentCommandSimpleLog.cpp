#include "Misc/AutomationTest.h"
#include "Tests/Utils/Character/CharacterTypes.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLatentCommandSimpleLog, "NSGame.LatentCommand.SimpleLog",
EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);
using namespace NS::CharacterTest;

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FNSLogLatentCommand, FString, LogMessage);
bool FNSLogLatentCommand::Update()
{
    UE_LOG(LogNSCharacterTests, Display, TEXT("%s"), *LogMessage);
    return true;
}

bool FLatentCommandSimpleLog::RunTest(const FString& Parameters)
{
    UE_LOG(LogNSCharacterTests, Display, TEXT("Log 1"));
    ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand(
        []()
        {
            UE_LOG(LogNSCharacterTests, Display, TEXT("Latent log 1"));
            return true;
        }));
    UE_LOG(LogNSCharacterTests, Display, TEXT("Log 2"));
    ADD_LATENT_AUTOMATION_COMMAND(FNSLogLatentCommand("Latent log 2"));
    UE_LOG(LogNSCharacterTests, Display, TEXT("Log 3"));
    return true;
}
