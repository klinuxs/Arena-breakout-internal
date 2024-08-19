#include <Windows.h>
#include <iostream>
#include <math.h>
#include <corecrt_math_defines.h>
#include "Cache.h"
DWORD MainThread(HMODULE Module)
{
    SDK::TArray<SDK::ULevel*>& levels = SDK::UWorld::GetWorld()->Levels;

    for (SDK::ULevel* Level : levels)
    {
        SDK::TArray<SDK::AActor*>& Actors = Level->Actors;
        for (SDK::AActor* Actor : Actors)
        {
            if (!Actor || !Actor->IsA(SDK::EClassCastFlags::Pawn) || !Actor->IsA(SDK::APawn::StaticClass()))
                continue;

            SDK::APawn* Pawn = static_cast<SDK::APawn*>(Actor);
            SDK::FVector Location = Pawn->GetTransform().Translation;
            std::string Name = Pawn->GetFullName();
            // location is Location.x, so on so forth, and the name you need to do a contains check if its a player or not, just make a print if you want to see every players name and location
        }
    }
    SDK::UInputSettings::GetDefaultObj()->ConsoleKeys[0].KeyName = SDK::UKismetStringLibrary::Conv_StringToName(L"F2");
    SDK::UObject* NewObject = SDK::UGameplayStatics::SpawnObject(SDK::UEngine::GetEngine()->ConsoleClass, SDK::UEngine::GetEngine()->GameViewport);
    SDK::UEngine::GetEngine()->GameViewport->ViewportConsole = static_cast<SDK::UConsole*>(NewObject);
    FreeLibraryAndExitThread(Module, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0);
        break;
    }

    return TRUE;
}