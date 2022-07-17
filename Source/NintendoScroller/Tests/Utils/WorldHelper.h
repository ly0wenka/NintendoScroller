#pragma once

class WorldHelper
{
public:
    static bool IsWorldPlayInEditorOrGame(const FWorldContext& Context);
    static UWorld* GetWorld();
};
