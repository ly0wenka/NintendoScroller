#include "GenericPlatform/GenericPlatformCrashContext.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(AlgorithmReadHeximalFilesTest, "Algorithm.Read Heximal Files Test",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

DEFINE_LOG_CATEGORY_STATIC(LogReadFile, All, All);

bool AlgorithmReadHeximalFilesTest::RunTest(const FString& Parameters)
{
    TestTrueExpr(true);
    const FString& FileName = "C:\\Users\\L\\Downloads\\SMB\\bin\\ANNSMB (J)_PRG_ROM.bin";
    FString FileContentString;
    if (!FFileHelper::LoadFileToString(FileContentString, *FileName))
    {
        UE_LOG(LogReadFile, Error, TEXT("File opening error"))
        return false;
    }

    TestEqual("", FileContentString[0], TEXT("xØ©^P<8d>^@ ¢ÿ<9a>­^B ^Pû­^B ^Pû þ¢^E½×^GÉ")[0]);
    return true;
}
