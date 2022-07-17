#include "WorldHelper.h"

bool WorldHelper::IsWorldPlayInEditorOrGame(const FWorldContext& Context)
{
    return (Context.WorldType == EWorldType::PIE || Context.WorldType == EWorldType::Game) && Context.World();
}

UWorld* WorldHelper::GetWorld()
{
    const TIndirectArray<FWorldContext>& WorldContexts = GEngine->GetWorldContexts();
    for (const FWorldContext& Context : WorldContexts)
    {
        if (IsWorldPlayInEditorOrGame(Context))
        {
            return Context.World();
        }
    }

    return nullptr;
}
