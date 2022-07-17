#pragma once

class BlueprintHelper
{
public:
    template <typename T> static
    T* CreateBlueprint(UWorld* World, const FString& Name, const FTransform& Transform = FTransform::Identity)
    {
        const UBlueprint* Blueprint = LoadObject<UBlueprint>(nullptr, *Name);
        return (World && Blueprint) ? World->SpawnActor<T>(Blueprint->GeneratedClass, Transform) : nullptr;
    }

    template <typename T> static
    T* CreateBlueprintDeferred(UWorld* World, const FString& Name, const FTransform& Transform = FTransform::Identity)
    {
        const UBlueprint* Blueprint = LoadObject<UBlueprint>(nullptr, *Name);
        return (World && Blueprint) ? World->SpawnActorDeferred<T>(Blueprint->GeneratedClass, Transform) : nullptr;
    }
};
