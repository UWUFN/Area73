#pragma once

inline std::vector<UFunction*> toHook;
inline std::vector<std::function<bool(UObject*, void*)>> toCall;
#define HandlePEFunction(ufunctionName, func)                           \
            toHook.push_back(UObject::FindObject<UFunction>(ufunctionName)); \
            toCall.push_back([](UObject * Object, void* Parameters) -> bool func);


#include "game.h"
#include "ue4.h"

#include "FortniteGame/Abilities/Inventory.h"
#include "FortniteGame/Abilities/Build.h"
#include "FortniteGame/Abilities/Edit.h"
#include "FortniteGame/Abilities/DecoTool.h"
#include "FortniteGame/Abilities/Interactions.h"
#include "FortniteGame/Abilities/PlayerManager.h"
#include "FortniteGame/Abilities/Emote.h"
#include "FortniteGame/Abilities/Aircraft.h"
#include "FortniteGame/Abilities/Abilities.h"
#include "FortniteGame/SDKS/7_3/SDK/FN_Engine_classes.hpp"

namespace Hooks
{
    static int teamIdx = 2;
    std::vector<const wchar_t*> PlayersJoined;

    bool LocalPlayerSpawnPlayActor(ULocalPlayer* Player, const FString& URL, FString& OutError, UWorld* World)
    {
        if (bTraveled)
            return true;
        else
            return Functions::LocalPlayer::SpawnPlayActor(Player, URL, OutError, World);
    }

    inline UKismetMathLibrary* GetMath()
    {
        return (UKismetMathLibrary*)UKismetMathLibrary::StaticClass();
    }
    uint64 GetNetMode(UWorld* World)
    {
        return ENetMode::NM_ListenServer;
    }

    void TickFlush(UNetDriver* _thisNetDriver, float DeltaSeconds)
    {
        auto NetDriver = GetWorld()->NetDriver;
        if (!NetDriver) return;

        if (NetDriver->ClientConnections.Num() && !NetDriver->ClientConnections[0]->InternalAck)
            if (NetDriver->ReplicationDriver)
                Functions::ReplicationDriver::ServerReplicateActors(NetDriver->ReplicationDriver);

        Functions::NetDriver::TickFlush(NetDriver, DeltaSeconds);
    }
    /*
    void WelcomePlayer(UWorld* World, UNetConnection* IncomingConnection)
    {
        Functions::World::WelcomePlayer(GetWorld(), IncomingConnection);
    }
    */
    char KickPlayer(__int64 a1, __int64 a2, __int64 a3)
    {
        return 1;
    }
    void World_NotifyControlMessage(UWorld* World, UNetConnection* Connection, uint8_t MessageType, int64* Bunch)
    {
        //MessageBoxA(0, "World_NotifyControlMessage", std::to_string(MessageType).c_str(), 0);
        if (MessageType == 4) //NMT_Netspeed
        {
            //MessageBoxA(0, "NMT_Netspeed", std::to_string(MessageType).c_str(), 0);
            Connection->CurrentNetSpeed = 30000;
        }
        else if (MessageType == 5) //NMT_Login
        {
            //MessageBoxA(0, "NMT_Login", std::to_string(MessageType).c_str(), 0);
            Bunch[7] += (16 * 1024 * 1024);

            auto OnlinePlatformName = FString(L"");

            Functions::NetConnection::ReceiveFString(Bunch, Connection->ClientResponse);
            Functions::NetConnection::ReceiveFString(Bunch, Connection->RequestURL);
            Functions::NetConnection::ReceiveUniqueIdRepl(Bunch, Connection->PlayerID);
            Functions::NetConnection::ReceiveFString(Bunch, OnlinePlatformName);
            //MessageBoxW(0, L"OnlinePlatformName", OnlinePlatformName.c_str(), 0);

            Bunch[7] -= (16 * 1024 * 1024);

            Functions::World::WelcomePlayer(GetWorld(), Connection);
        }
        else
            Functions::World::NotifyControlMessage(GetWorld(), Connection, MessageType, (void*)Bunch);
    }

    APlayerController* SpawnPlayActor(UWorld* World, UPlayer* NewPlayer, ENetRole RemoteRole, FURL& URL, void* UniqueId, SDK::FString& Error, uint8_t NetPlayerIndex, FVector Loc = FVector(), FQuat Rot = FQuat())
    {
        auto PlayerController = (AFortPlayerControllerAthena*)Functions::World::SpawnPlayActor(GetWorld(), NewPlayer, RemoteRole, URL, UniqueId, Error, NetPlayerIndex);
        NewPlayer->PlayerController = PlayerController;

        if (((AFortGameStateAthena*)(GetWorld()->GameState))->GamePhase >= EAthenaGamePhase::Aircraft)
        {
            KickController(PlayerController, L"You can't join while the match is running, should've joined earlier.");
            return 0;
        }

        auto PlayerState = (AFortPlayerStateAthena*)PlayerController->PlayerState;

        auto NewPlayerIP = PlayerState->SavedNetworkAddress.c_str();
        std::wcout << L"Spawning Player with IP: " << NewPlayerIP << L"\n";

        for (int i = 0; i < PlayersJoined.size(); i++)
        {
            if (PlayersJoined[i] == NewPlayerIP)
            {
                KickController(PlayerController, L"You can't rejoin in the same match.");
                return 0;
            }

            if (i == PlayersJoined.size() - 1)
                PlayersJoined.push_back(NewPlayerIP);
        }

        InitializePawn(PlayerController);
        // Movement Fix

        Abilities::Inventory::InitInventory(PlayerController);

        auto entry = Abilities::Inventory::AddNewItem(PlayerController, ItemDefinitions::GetPickaxe(), 0);
        Abilities::Inventory::Update(PlayerController);
        EquipWeaponDefinition(PlayerController->Pawn, (UFortWeaponItemDefinition*)ItemDefinitions::GetPickaxe(), entry.ItemGuid, -1, true);



        

        PlayerState->TeamIndex = EFortTeam(teamIdx);

        PlayerState->PlayerTeam->TeamMembers.Add(PlayerController);
        PlayerState->PlayerTeam->Team = EFortTeam(teamIdx);

        PlayerState->SquadId = teamIdx - 1;
        PlayerState->OnRep_PlayerTeam();
        PlayerState->OnRep_SquadId();

        teamIdx++;

        PlayerController->OverriddenBackpackSize = 100;
        return PlayerController;
    }

    void* NetDebug(UObject* _this)
    {
        return nullptr;
    }

    __int64 CollectGarbage(__int64 a1)
    {
        return 0;
    }

    void OnReload(AFortWeapon* _this, unsigned int a2)
    {
        if (!_this->Owner) return;

        auto PC = ((APawn*)_this->Owner)->Controller;
        if (!PC) return;

        auto WeaponData = _this->WeaponData;
        if (!WeaponData) return;

        int AmmoToRemove = a2;

        Functions::FortWeapon::OnReload(_this, a2);

        if (ItemDefinitions::IsConsumable(WeaponData))
        {
            if (Abilities::Inventory::GetItemCount((AFortPlayerControllerAthena*)PC, WeaponData) <= 1)
            {
                auto Slots = ((AFortPlayerControllerAthena*)PC)->QuickBars->PrimaryQuickBar.Slots;
                for (int i = 0; i < Slots.Num(); i++)
                {
                    auto Slot = Slots[i];
                    if (!Slot.Items.Num()) continue;

                    auto ItemInstance = GetInstanceFromGuid(PC, Slot.Items[0]);
                    if (!ItemInstance) continue;

                    auto ItemDefinition = ItemInstance->ItemEntry.ItemDefinition;
                    if (ItemDefinition == WeaponData)
                    {
                        Abilities::Inventory::RemoveItemFromSlot((AFortPlayerControllerAthena*)PC, i, EFortQuickBars::Primary, 1);
                        return;
                    }
                }
            }
            else
            {
                Abilities::Inventory::DecreaseItemCount((AFortPlayerControllerAthena*)PC, WeaponData, 1);
                return;
            }
        }
        else
        {
            auto AmmoType = WeaponData->GetAmmoWorldItemDefinition_BP();
            if (!AmmoType) return;

            auto ItemInstances = ((AFortPlayerControllerAthena*)PC)->WorldInventory->Inventory.ItemInstances;
            for (int i = 0; i < ItemInstances.Num(); i++)
            {
                auto ItemInstance = ItemInstances[i];
                if (!ItemInstance) continue;

                auto Def = ItemInstance->ItemEntry.ItemDefinition;

                if (Def == AmmoType)
                {
                    Abilities::Inventory::AddItem((AFortPlayerControllerAthena*)PC, ItemInstance, 0, EFortQuickBars::Secondary, ItemInstance->ItemEntry.Count - AmmoToRemove);
                    return;
                }
            }
        }
    }
    void ProcessEventHook(UObject* Object, UFunction* Function, void* Parameters)
    {
        static auto Klixx3 = UObject::FindObject<UFunction>("Function Engine.PlayerController.ServerAcknowledgePossession");
        if (Function == Klixx3)
        {
            auto PlayerController = (APlayerController*)Object; PlayerController->AcknowledgedPawn = PlayerController->Pawn;
        }
        if (bTraveled)
        {
            if (!bListening)
            {

                static auto ReadyToStartMatchFn = UObject::FindObject<UFunction>("Function Engine.GameMode.ReadyToStartMatch");
                if (Function == ReadyToStartMatchFn)
                {
                    Game::OnReadyToStartMatch();



                    MessageBoxA(0, "Creating NetDriver", 0, 0);
                    auto NewNetDriver = Functions::Engine::CreateNetDriver(Functions::GetEngine(), GetWorld(), FName(282));
                    MessageBoxA(0, "NewNetDriver", std::to_string((uintptr_t)NewNetDriver).c_str(), 0);





                    NewNetDriver->NetDriverName = FName(282);
                    NewNetDriver->World = GetWorld();


                    FString Error;
                    auto InURL = FURL();
                    InURL.Port = 7777;

                    MessageBoxA(0, "InitListen", std::to_string((uintptr_t)NewNetDriver).c_str(), 0);
                    Functions::NetDriver::InitListen(NewNetDriver, GetWorld(), InURL, true, Error);
                    MessageBoxA(0, "LISTENING", std::to_string((uintptr_t)NewNetDriver).c_str(), 0);

                    MessageBoxA(0, "NetDriver_SetWorld", 0, 0);
                    Functions::NetDriver::SetWorld(NewNetDriver, GetWorld());
                    MessageBoxA(0, "SETTEDSHITSSS", std::to_string((uintptr_t)NewNetDriver).c_str(), 0);
                    MessageBoxA(0, "PROOF", std::to_string((uintptr_t)NewNetDriver->World).c_str(), 0);


                    Functions::ReplicationDriver::ServerReplicateActors = decltype(Functions::ReplicationDriver::ServerReplicateActors)(NewNetDriver->ReplicationDriver->Vtable[/*3.5/4.1: 0x54*/ /*0x54*/0x56]);
                    MessageBoxA(0, "Initialized ServerReplicateActors", std::to_string((uintptr_t)Functions::ReplicationDriver::ServerReplicateActors).c_str(), 0);


                    auto ClassRepNodePolicies = GetClassRepNodePolicies(NewNetDriver->ReplicationDriver);

                    for (auto&& Pair : ClassRepNodePolicies)
                    {
                        auto key = Pair.Key().ResolveObjectPtr();

                        if (key == AFortInventory::StaticClass())
                            Pair.Value() = EClassRepNodeMapping::RelevantAllConnections;
                        else if (key == AFortQuickBars::StaticClass())
                            Pair.Value() = EClassRepNodeMapping::RelevantAllConnections;
                    }

                    GetWorld()->NetDriver = NewNetDriver;
                    GetWorld()->LevelCollections[0].NetDriver = NewNetDriver;
                    GetWorld()->LevelCollections[1].NetDriver = NewNetDriver;
                    MessageBoxA(0, "stored shits in variables", std::to_string((uintptr_t)GetWorld()->NetDriver).c_str(), 0);

                    auto GameState = (AFortGameStateAthena*)GetWorld()->GameState;

                    ((AFortGameModeAthena*)GetWorld()->AuthorityGameMode)->GameSession->MaxPlayers = 100;



                    GameState->CurrentPlaylistInfo.BasePlaylist = UObject::FindObject<UFortPlaylistAthena>("FortPlaylistAthena Playlist_PlaygroundV2.Playlist_PlaygroundV2");
                    GameState->CurrentPlaylistInfo.PlaylistReplicationKey++;

                    GameState->PlayersLeft = 0;

                    GameState->OnRep_PlayersLeft();









                    /*
                    HostBeacon = SpawnActor<AFortOnlineBeaconHost>();
                    HostBeacon->ListenPort = 7776;
                    auto bInitBeacon = Functions::OnlineBeaconHost::InitHost(HostBeacon);

                    HostBeacon->NetDriverName = FName(282);
                    HostBeacon->NetDriver->NetDriverName = FName(282);
                    HostBeacon->NetDriver->World = GetWorld();


                    FString Error;
                    auto InURL = FURL();
                    InURL.Port = 7777;

                    Functions::NetDriver::InitListen(HostBeacon->NetDriver, GetWorld(), InURL, true, Error);
                    Functions::ReplicationDriver::ServerReplicateActors = decltype(Functions::ReplicationDriver::ServerReplicateActors)(HostBeacon->NetDriver->ReplicationDriver->Vtable[0x53]);

                    auto ClassRepNodePolicies = GetClassRepNodePolicies(HostBeacon->NetDriver->ReplicationDriver);

                    for (auto&& Pair : ClassRepNodePolicies)
                    {
                        auto key = Pair.Key().ResolveObjectPtr();

                        if (key == AFortInventory::StaticClass())
                            Pair.Value() = EClassRepNodeMapping::RelevantAllConnections;
                        else if (key == AFortQuickBars::StaticClass())
                            Pair.Value() = EClassRepNodeMapping::RelevantAllConnections;
                    }


                    GetWorld()->NetDriver = HostBeacon->NetDriver;
                    GetWorld()->LevelCollections[0].NetDriver = HostBeacon->NetDriver;
                    GetWorld()->LevelCollections[1].NetDriver = HostBeacon->NetDriver;

                    auto GameState = (AAthena_GameState_C*)GetWorld()->GameState;

                    ((AAthena_GameMode_C*)GetWorld()->AuthorityGameMode)->GameSession->MaxPlayers = 100;

                    Functions::OnlineBeacon::PauseBeaconRequests(HostBeacon, false);
                    */

                    bListening = true;
                    std::cout << "Server is listening, people can join\n";
                    return;
                }
            }
        }

        for (int i = 0; i < toHook.size(); i++)
        {
            if (Function == toHook[i])
            {
                if (toCall[i](Object, Parameters))
                {
                    return;
                }
                break;
            }
        }


        return oProcessEvent(Object, Function, Parameters);
    }
}