#pragma once

namespace Patterns
{

#if defined(VERSION_3_5) || defined(VERSION_4_1)
    constexpr const char* GObjects = "48 8B 05 ? ? ? ? 48 8D 1C C8 81 4B ? ? ? ? ? 49 63 76 30";
    constexpr const char* Free = "48 85 C9 74 1D 4C 8B 05 ? ? ? ? 4D 85 C0 0F 84 ? ? ? ? 49 8B 00 48 8B D1 49 8B C8 48 FF 60 20 C3";
    constexpr const char* Malloc = "4C 8B C9 48 8B 0D ? ? ? ? 48 85 C9 75 08 49 8B C9 E9 ? ? ? ?";
    constexpr const char* Realloc = "4C 8B D1 48 8B 0D ? ? ? ? 48 85 C9 75 08 49 8B CA E9 ? ? ? ? 48 8B 01 45 8B C8 4C 8B C2 49 8B D2 48 FF 60 18";
    constexpr const char* FNameToString = "48 89 5C 24 ? 57 48 83 EC 40 83 79 04 00 48 8B DA 48 8B F9";
    constexpr const char* TickFlush = "4C 8B DC 55 49 8D AB ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 89 5B 18 48 8D 05 ? ? ? ? 49 89 7B E8 48 8B F9 4D 89 63 E0 45 33 E4";
    constexpr const char* CreateNetDriver = "4C 89 44 24 18 53 48 83 EC ? 48 8B D9 E8 ? ? ? ? 4C 8B 44 24 40";
    constexpr const char* NetDriver_SetWorld = "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B B1 ? ? ? ? 48 8B FA 48 8B D9 48 85 F6 74 5C 48 8B 93 ? ? ? ? 48 8D 8E ? ? ?";
    constexpr const char* InitListen = "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 50 48 8B BC 24 ? ? ? ? 49 8B F0";
    constexpr const char* WelcomePlayer = "48 8B C4 55 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 89 70 20";
    constexpr const char* World_NotifyControlMessage = "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 33 F6 49 8B D9 44 89 74 24 ? 45 8B E6 48 8B 41 10 45 0F B6 F8 48 8B FA 4C 8B E9 4C 39 60 78";
    constexpr const char* SpawnPlayActor = "44 89 44 24 ? 48 89 54 24 ? 48 89 4C 24 ? 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 33 F6 48 8D 05 ? ? ? ? 89 75 67 4D 8B E9 4C 8B 65 77 49 39 04 24 74 2A 41 89 74 24 ? 41 39 74 24 ?";
    constexpr const char* ReceiveUniqueIdRepl = "48 89 5C 24 ? 55 56 57 48 8B EC 48 83 EC 40 F6 41 28 40 48 8B FA 48 8B D9 0F 84 ? ? ? ? F6 41 2B 02";
    constexpr const char* ReceiveFString = "40 55 53 56 57 41 56 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 27 0F B6 41 28";
    constexpr const char* KickPlayer = "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 49 8B F0 48 8B DA 48 85 D2 74 ? 48 8B BA ? ? ? ? 48";
    constexpr const char* GetNetMode = "48 89 5C 24 ? 57 48 83 EC 20 48 8B 01 48 8B D9 FF 90 ? ? ? ? 4C 8B 83 ? ? ? ? 48 8B F8 33 C0 48 C7 44 24";
    constexpr const char* GiveAbility = "48 89 5C 24 ? 56 57 41 56 48 83 EC 20 83 B9 ? ? ? ? ? 49 8B F0 4C 8B F2 48 8B D9 7E 61";
    constexpr const char* InternalTryActivateAbility = "4C 89 4C 24 ? 4C 89 44 24 ? 89 54 24 10 55 53 56 57 41 54 41 57 48 8D AC 24";
    constexpr const char* MarkAbilitySpecDirty = "48 89 5C 24 ? 57 48 83 EC 20 80 B9 ? ? ? ? ? 48 8B FA 48 8B D9 75 4A C6 81";
    constexpr const char* LocalPlayerSpawnPlayActor = "40 55 53 56 57 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 40 48 8B D9 4D 8B F1 49 8B C9 4D 8B F8 48 8B F2";
    constexpr const char* CollectGarbage = "40 53 48 83 EC ? 48 8B D9 FF 15 ? ? ? ? 84 C0 75 ?";
    constexpr const char* NetDebug = "40 55 56 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B 01 48 8B F1 FF 90 ? ? ? ? 4C 8B F0 48 85 C0 0F";
    constexpr const char* OnReload = "89 54 24 10 55 41 56 48 8D 6C 24 B1 48 81 EC ? ? ? ? 80 B9 18 01 00 00 ?";
#endif

#if defined(VERSION_4_2)
    constexpr const char* GObjects = "48 8B 05 ? ? ? ? 48 8D 14 C8 EB ? 48 8B D1 8B 42 08 C1 E8 ? A8 ? 0F 85 ? ? ? ? 48 8B 47 10";//
    constexpr const char* Free = "48 85 C9 74 1D 4C 8B 05 ? ? ? ? 4D 85 C0 0F 84 ? ? ? ? 49 8B 00 48 8B D1 49 8B C8 48 FF 60 20 C3";//
    constexpr const char* Malloc = "4C 8B C9 48 8B 0D ? ? ? ? 48 85 C9 75 08 49 8B C9 E9 ? ? ? ?";//
    constexpr const char* Realloc = "4C 8B D1 48 8B 0D ? ? ? ? 48 85 C9 75 08 49 8B CA E9 ? ? ? ? 48 8B 01 45 8B C8 4C 8B C2 49 8B D2 48 FF 60 18";//
    constexpr const char* FNameToString = "48 89 5C 24 ? 57 48 83 EC 40 83 79 04 00 48 8B DA 48 8B F9";//
    constexpr const char* TickFlush = "4C 8B DC 55 49 8D AB ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 89 5B 18 48 8D 05 ? ? ? ? 49 89 7B E8 48 8B F9 4D 89 63 E0 45 33 E4";//
    constexpr const char* CreateNetDriver = "idk";
    constexpr const char* NetDriver_SetWorld = "idk";
    constexpr const char* InitListen = "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 50 48 8B BC 24 ? ? ? ? 49 8B F0";//
    constexpr const char* WelcomePlayer = "48 8B C4 55 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 89 70 20";//
    constexpr const char* World_NotifyControlMessage = "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 48 FA FF FF";//
    constexpr const char* SpawnPlayActor = "48 8B C4 44 89 40 18 48 89 50 10 48 89 48 08 55 56";//
    constexpr const char* ReceiveUniqueIdRepl = "48 89 5C 24 ? 55 56 57 48 8B EC 48 83 EC 40 F6 41 28 40 48 8B FA 48 8B D9 0F 84 ? ? ? ? F6 41 2B 02";//
    constexpr const char* ReceiveFString = "40 55 53 56 57 41 56 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 27 0F B6 41 28";//
    constexpr const char* KickPlayer = "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 49 8B F0 48 8B DA 48 85 D2 74 ? 48 8B BA ? ? ? ? 48";//
    constexpr const char* GetNetMode = "48 89 5C 24 ? 57 48 83 EC 20 48 8B 01 48 8B D9 FF 90 ? ? ? ? 4C 8B 83 ? ? ? ? 48 8B F8 33 C0 48 C7 44 24";//
    constexpr const char* GiveAbility = "48 89 5C 24 ? 56 57 41 56 48 83 EC 20 83 B9 ? ? ? ? ? 49 8B F0 4C 8B F2 48 8B D9 7E 61";//
    constexpr const char* InternalTryActivateAbility = "4C 89 4C 24 ? 4C 89 44 24 ? 89 54 24 10 55 53 56 57 41 54 41 57 48 8D AC 24";//
    constexpr const char* MarkAbilitySpecDirty = "48 89 5C 24 ? 57 48 83 EC 20 80 B9 ? ? ? ? ? 48 8B FA 48 8B D9 75 4A C6 81";//
    constexpr const char* LocalPlayerSpawnPlayActor = "40 55 53 56 57 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 40 48 8B D9 4D 8B F1 49 8B C9 4D 8B F8 48 8B F2";//
    constexpr const char* CollectGarbage = "40 53 48 83 EC ? 48 8B D9 FF 15 ? ? ? ? 84 C0 75 ?";//
    constexpr const char* NetDebug = "40 55 56 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B 01 48 8B F1 FF 90 ? ? ? ? 4C 8B F0 48 85 C0 0F";//
    constexpr const char* OnReload = "89 54 24 10 55 41 56 48 8D 6C 24 B1 48 81 EC ? ? ? ? 80 B9 18 01 00 00 ?";//
#endif

#if defined(VERSION_4_5)
    constexpr const char* GObjects = "48 8B 05 ? ? ? ? 48 8D 14 C8 EB ? 48 8B D1 8B 42 08 C1 E8 ? A8 ? 0F 85 ? ? ? ? 48 8B 47 10";//
    constexpr const char* Free = "48 85 C9 74 1D 4C 8B 05 ? ? ? ? 4D 85 C0 0F 84 ? ? ? ? 49 8B 00 48 8B D1 49 8B C8 48 FF 60 20 C3";//
    constexpr const char* Malloc = "4C 8B C9 48 8B 0D ? ? ? ? 48 85 C9 75 08 49 8B C9 E9 ? ? ? ?";//
    constexpr const char* Realloc = "4C 8B D1 48 8B 0D ? ? ? ? 48 85 C9 75 08 49 8B CA E9 ? ? ? ? 48 8B 01 45 8B C8 4C 8B C2 49 8B D2 48 FF 60 18";//
    constexpr const char* FNameToString = "48 89 5C 24 ? 57 48 83 EC 40 83 79 04 00 48 8B DA 48 8B F9";//
    constexpr const char* TickFlush = "4C 8B DC 55 49 8D AB C8 FE FF FF 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 D0 00 00 00 49 89 5B 18";//
    constexpr const char* CreateNetDriver = "idk";
    constexpr const char* NetDriver_SetWorld = "idk";
    constexpr const char* InitListen = "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 50 48 8B BC 24 ? ? ? ? 49 8B F0";//
    constexpr const char* WelcomePlayer = "48 8B C4 55 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 89 70 20";//
    constexpr const char* World_NotifyControlMessage = "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 48 FA FF FF";//
    constexpr const char* SpawnPlayActor = "48 8B C4 44 89 40 18 48 89 50 10 48 89 48 08 55 56";//
    constexpr const char* ReceiveUniqueIdRepl = "48 89 5C 24 ? 55 56 57 48 8B EC 48 83 EC 40 F6 41 28 40 48 8B FA 48 8B D9 0F 84 ? ? ? ? F6 41 2B 02";//
    constexpr const char* ReceiveFString = "40 55 53 56 57 41 56 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 27 0F B6 41 28";//
    constexpr const char* KickPlayer = "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 49 8B F0 48 8B DA 48 85 D2 74 ? 48 8B BA ? ? ? ? 48";//
    constexpr const char* GetNetMode = "48 89 5C 24 ? 57 48 83 EC 20 48 8B 01 48 8B D9 FF 90 ? ? ? ? 4C 8B 83 ? ? ? ? 48 8B F8 33 C0 48 C7 44 24";//
    constexpr const char* GiveAbility = "48 89 5C 24 ? 56 57 41 56 48 83 EC 20 83 B9 ? ? ? ? ? 49 8B F0 4C 8B F2 48 8B D9 7E 61";//
    constexpr const char* InternalTryActivateAbility = "4C 89 4C 24 ? 4C 89 44 24 ? 89 54 24 10 55 53 56 57 41 54 41 57 48 8D AC 24";//
    constexpr const char* MarkAbilitySpecDirty = "48 89 5C 24 ? 57 48 83 EC 20 80 B9 ? ? ? ? ? 48 8B FA 48 8B D9 75 4A C6 81";//
    constexpr const char* LocalPlayerSpawnPlayActor = "40 55 53 56 57 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 40 48 8B D9 4D 8B F1 49 8B C9 4D 8B F8 48 8B F2";//
    constexpr const char* CollectGarbage = "40 53 48 83 EC ? 48 8B D9 FF 15 ? ? ? ? 84 C0 75 ?";//
    constexpr const char* NetDebug = "40 55 56 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B 01 48 8B F1 FF 90 ? ? ? ? 4C 8B F0 48 85 C0 0F";//
    constexpr const char* OnReload = "89 54 24 10 55 41 56 48 8D 6C 24 B1 48 81 EC ? ? ? ? 80 B9 18 01 00 00 ?";//
#endif




#if defined(VERSION_5_21)

    constexpr const char* GObjects = "48 8B 05 ? ? ? ? 48 8B 14 C8 49 63 C0 48 8D 0C 40 48 8D 04 CA EB ? 48 8B C6 8B 40 08 C1 E8 ? A8 ? 0F 85 ? ? ? ? 48 8B 55 88"; // updated
    constexpr const char* Free = "48 85 C9 74 ? 53 48 83 EC ? 48 8B D9 48 8B 0D ? ? ? ?"; // updated
    constexpr const char* Malloc = "48 83 EC ? 48 8B 0D ? ? ? ? 48 85 C9 75 ? 33 D2 B9 ? ? ? ? E8 ? ? ? ? 48 8B 4C 24 58"; // updated
    constexpr const char* Realloc = "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC ? 48 8B F1 41 8B D8 48 8B 0D ? ? ? ?";// updated
    constexpr const char* FNameToString = "48 89 5C 24 08 57 48 83 EC ? 83 79 04 ?";// updated
    constexpr const char* TickFlush = "4C 8B DC 55 49 8D AB 98 FE FF FF 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 00 01 00 00 49 89 5B 18 48 8D 05 ? ? ? ?";// updated
    constexpr const char* CreateNetDriver = "48 89 5C 24 10 57 48 83 EC ? 48 8B 81 50 0B 00 00";
    constexpr const char* NetDriver_SetWorld = "48 89 5C 24 ? 57 48 83 EC 20 48 8B FA 48 8B D9 48 8B 91 ? ? ? ? 48 85 D2 74 28 E8 ? ? ? ? 48 8B 8B ? ? ? ? 33 C0";
    constexpr const char* InitListen = "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 50 48 8B BC 24 ? ? ? ? 49 8B F0";// updated
    constexpr const char* WelcomePlayer = "48 8B C4 55 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 89 70 20";// updated
    constexpr const char* World_NotifyControlMessage = "48 89 5C 24 10 48 89 74 24 18 48 89 7C 24 20 48 89 4C 24 08 55 41 54 41 55 41 56 41 57 48 8D AC 24 C0 F9 FF FF";// updatedHM
    constexpr const char* SpawnPlayActor = "48 8B C4 4C 89 48 20 44 89 40 18 48 89 50 10 48 89 48 08 55 56";// updated -> ps: è un pò cambiata come parametri ma è questa
    constexpr const char* ReceiveUniqueIdRepl = "48 89 5C 24 ? 55 56 57 48 8B EC 48 83 EC 40 F6 41 28 40 48 8B FA 48 8B D9 0F 84 ? ? ? ? F6 41 2B 02";// updated
    constexpr const char* ReceiveFString = "48 89 5C 24 18 55 56 57 41 56 41 57 48 8D 6C 24 C9 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 27 0F B6 41 28";// updated
    constexpr const char* KickPlayer = "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC ? 49 8B F0 48 8B DA 48 85 D2";// updated
    constexpr const char* GetNetMode = "48 89 5C 24 ? 57 48 83 EC 20 48 8B 01 48 8B D9 FF 90 ? ? ? ? 4C 8B 83 ? ? ? ? 48 8B F8 33 C0 48 C7 44 24";// updated
    constexpr const char* GiveAbility = "48 89 5C 24 10 48 89 6C 24 18 48 89 7C 24 20 41 56 48 83 EC ? 83 B9 88 05 00 00 ?"; // updated
    constexpr const char* InternalTryActivateAbility = "4C 89 4C 24 ? 4C 89 44 24 ? 89 54 24 10 55 53 56 57 41 54 41 55 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 45 33 FF"; // updated
    constexpr const char* MarkAbilitySpecDirty = "48 89 5C 24 18 48 89 7C 24 20 41 56 48 83 EC ? 48 8B 01 41 0F B6 D8"; // updated
    constexpr const char* LocalPlayerSpawnPlayActor = "40 55 53 56 57 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 40 48 8B D9 4D 8B F1 49 8B C9 4D 8B F8 48 8B F2"; // updated
    constexpr const char* CollectGarbage = "48 89 5C 24 08 48 89 6C 24 10 56 57 41 56 48 81 EC ? ? ? ? 4C 8B 05"; // NON ESISTE PIU'
    constexpr const char* NetDebug = "40 55 56 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B 01 48 8B F1 FF 90 ? ? ? ? 4C 8B F0 48 85 C0 0F"; // updated
    constexpr const char* OnReload = "89 54 24 10 55 41 56 48 8D 6C 24 B1 48 81 EC ? ? ? ? 80 B9 18 01 00 00 ?";
#endif

#if defined(VERSION_6_1)

    constexpr const char* GObjects = "48 8B 0D ? ? ? ? 48 98 4C 8B 04 D1 48 8D 0C 40 49 8D 04 C8 EB ? 48 8B C6 8B 40 08 C1 E8 ? A8 ? 0F 85 ? ? ? ? 48 8B 55 88";//
    constexpr const char* Free = "48 85 C9 74 ? 53 48 83 EC ? 48 8B D9 48 8B 0D";//
    constexpr const char* Malloc = "48 89 5C 24 08 57 48 83 EC ? 48 8B F9 8B DA 48 8B 0D";//
    constexpr const char* Realloc = "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC ? 48 8B F1 41 8B D8 48 8B 0D";//
    constexpr const char* FNameToString = "48 89 5C 24 08 57 48 83 EC ? 83 79 04";//
    constexpr const char* TickFlush = "4C 8B DC 55 49 8D AB 98 FE FF FF 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 00 01 00 00 49 89 5B 18 48 8D 05";//
    constexpr const char* CreateNetDriver = "idk";
    constexpr const char* NetDriver_SetWorld = "48 89 5C 24 ? 57 48 83 EC 20 48 8B FA 48 8B D9 48 8B 91 ? ? ? ? 48 85 D2 74 28 E8 ? ? ? ? 48";
    constexpr const char* InitListen = "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 50 48 8B BC 24 ? ? ? ? 49 8B F0";//
    constexpr const char* WelcomePlayer = "48 8B C4 55 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 89 70 20";//
    constexpr const char* World_NotifyControlMessage = "48 89 5C 24 10 48 89 74 24 18 48 89 7C 24 20 48 89 4C 24 08 55 41 54 41 55 41 56 41 57 48 8D AC 24 C0 F9 FF FF";//
    constexpr const char* SpawnPlayActor = "48 8B C4 4C 89 48 20 44 89 40 18 48 89 50 10 48 89 48 08 55 56";//
    constexpr const char* ReceiveUniqueIdRepl = "48 89 5C 24 ? 55 56 57 48 8B EC 48 83 EC 40 F6 41 28 40 48 8B FA 48 8B D9 0F 84 ? ? ? ? F6 41 2B 02";//
    constexpr const char* ReceiveFString = "48 89 5C 24 18 55 56 57 41 56 41 57 48 8D 6C 24 C9 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 27 0F B6 41 28";//
    constexpr const char* KickPlayer = "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC ? 49 8B F0 48 8B DA 48 85 D2";//
    constexpr const char* GetNetMode = "48 89 5C 24 ? 57 48 83 EC 20 48 8B 01 48 8B D9 FF 90 ? ? ? ? 4C 8B 83 ? ? ? ? 48 8B F8 33 C0 48 C7 44 24";//
    constexpr const char* GiveAbility = "48 89 5C 24 10 48 89 6C 24 18 48 89 7C 24 20 41 56 48 83 EC ? 83 B9 88 05";//
    constexpr const char* InternalTryActivateAbility = "4C 89 4C 24 20 4C 89 44 24 18 89 54 24 10 55 53 56";//
    constexpr const char* MarkAbilitySpecDirty = "48 89 5C 24 18 48 89 7C 24 20 41 56 48 83 EC ? 48 8B 01 41 0F B6 D8";//
    constexpr const char* LocalPlayerSpawnPlayActor = "40 55 53 56 57 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 40 48 8B D9 4D 8B F1 49 8B C9 4D 8B F8 48 8B F2";//
    constexpr const char* CollectGarbage = "48 89 5C 24 08 48 89 6C 24 10 56 57 41 56 48 81 EC ? ? ? ? 4C 8B 05";
    constexpr const char* NetDebug = "40 55 56 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B 01 48 8B F1 FF 90 ? ? ? ? 4C 8B F0 48 85 C0 0F";//
    constexpr const char* OnReload = "89 54 24 10 55 41 56 48 8D 6C 24 B1 48 81 EC ? ? ? ? 80 B9 18 01 00 00 ?";//
#endif

#if defined(VERSION_7_3)
    constexpr const char* GObjects = "48 8B 0D ? ? ? ? 48 98 4C 8B 04 D1 48 8D 0C 40 49 8D 04 C8 EB ? 48 8B C6 8B 40 08 C1 E8 ? A8 ? 0F 85 ? ? ? ? 48 8B 55 F8";//
    constexpr const char* Free = "48 85 C9 74 ? 53 48 83 EC ? 48 8B D9 48 8B 0D";//
    constexpr const char* Malloc = "48 89 5C 24 08 57 48 83 EC ? 48 8B F9 8B DA 48 8B 0D ? ? ? ? 48 85 C9";//
    constexpr const char* Realloc = "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC ? 48 8B F1 41 8B D8 48 8B 0D";//
    constexpr const char* FNameToString = "48 89 5C 24 08 57 48 83 EC ? 83 79 04 ? 48 8B DA";//
    constexpr const char* TickFlush = "4C 8B DC 55 49 8D AB 78 FE FF FF 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 00 01 00 00 49 89 5B 18";//
    constexpr const char* CreateNetDriver = "48 89 5C 24 10 57 48 83 EC ? 48 8B 81 D0 0B 00 00";
    constexpr const char* NetDriver_SetWorld = "48 89 5C 24 08 57 48 83 EC ? 48 8B FA 48 8B D9 48 8B 91 40 01 00 00";
    constexpr const char* InitListen = "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 50 48 8B BC 24 ? ? ? ? 49 8B F0";//
    constexpr const char* WelcomePlayer = "48 8B C4 55 48 8D A8 48 FF FF FF";//
    constexpr const char* World_NotifyControlMessage = "48 89 5C 24 10 48 89 74 24 18 48 89 7C 24 20 48 89 4C 24 08 55 41 54 41 55 41 56 41 57 48 8D AC 24 D0 F9 FF FF";//
    constexpr const char* SpawnPlayActor = "48 8B C4 4C 89 48 20 44 89 40 18 48 89 50 10 48 89 48 08 55 56";//
    constexpr const char* ReceiveUniqueIdRepl = "48 89 5C 24 ? 55 56 57 48 8B EC 48 83 EC 40 F6 41 28 40 48 8B FA 48 8B D9 0F 84 ? ? ? ? F6 41 2B 02";//
    constexpr const char* ReceiveFString = "48 89 5C 24 18 55 56 57 41 56 41 57 48 8D 6C 24 C9 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 27 0F B6 41 28";//
    constexpr const char* KickPlayer = "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC ? 49 8B F0 48 8B DA 48 85 D2";//
    constexpr const char* GetNetMode = "48 89 5C 24 08 57 48 83 EC ? 48 8B 01 48 8B D9 FF 90 40 01 00 00 4C 8B 83 10 01 00 00";//
    constexpr const char* GiveAbility = "48 89 5C 24 10 48 89 6C 24 18 48 89 7C 24 20 41 56 48 83 EC ? 83 B9 60 05";//
    constexpr const char* InternalTryActivateAbility = "4C 89 4C 24 20 4C 89 44 24 18 89 54 24 10 55 53 56 57 41 54";//
    constexpr const char* MarkAbilitySpecDirty = "48 89 5C 24 18 48 89 7C 24 20 41 56 48 83 EC ? 48 8B 01 41 0F B6 D8";//
    constexpr const char* LocalPlayerSpawnPlayActor = "48 89 5C 24 08 48 89 74 24 10 48 89 7C 24 18 55 41 56 41 57 48 8D 6C 24 F0 48 81 EC ? ? ? ? 48 8B D9";//
    constexpr const char* CollectGarbage = "E9 ? ? ? ? 4C 8B 34 24 48 8D 64 24 ? 48 8B 2C 24 48 8D 64 24 ? E9 ? ? ? ?";
    constexpr const char* NetDebug = "40 55 56 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B 01 48 8B F1 FF 90 ? ? ? ? 4C 8B F0 48 85 C0 0F";//
    constexpr const char* OnReload = "89 54 24 10 55 41 56 48 8D 6C 24 B1 48 81 EC ? ? ? ? 80 B9 18 01 00 00 ?";//
#endif

}