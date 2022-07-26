#pragma once
#include "Tests/AutomationCommon.h"

namespace NS::Test
{
class LevelScope
{
public:
    LevelScope(const FString& MapName) { AutomationOpenMap(MapName); }
    ~LevelScope() { ADD_LATENT_AUTOMATION_COMMAND(FExitGameCommand); }
};
}
