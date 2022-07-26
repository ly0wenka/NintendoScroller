#pragma once

namespace NS::Test
{
class WorldHelper
{
public:
    static bool IsWorldPlayInEditorOrGame(const FWorldContext& Context);
    static UWorld* GetWorld();
};
}
