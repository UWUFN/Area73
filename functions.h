#pragma once

#include "patterns.h"
#include "util.h"

namespace Functions
{
    inline UFortEngine* GetEngine()
    {
        //MessageBoxA(0, "gettinenginee", 0, 0);
        static auto engine = UObject::FindObject<UFortEngine>("FortEngine_");
        //MessageBoxA(0, "AAAAAAA", std::to_string((uintptr_t)engine).c_str(), 0);
        return engine;
    }

    namespace Actor
    {
        inline __int64 (*GetNetMode)(__int64* a1);
    }

    namespace LocalPlayer
    {
        bool (*SpawnPlayActor)(ULocalPlayer* Player, const FString& URL, FString& OutError, UWorld* World);
    }

    namespace GC
    {
        __int64 (*CollectGarbage)(__int64 a1);
    }

    namespace AbilitySystemComponent
    {
        inline FGameplayAbilitySpecHandle* (*GiveAbility)(UAbilitySystemComponent* _this, FGameplayAbilitySpecHandle* outHandle, FGameplayAbilitySpec inSpec);
        inline bool (*InternalTryActivateAbility)(UAbilitySystemComponent* _this, FGameplayAbilitySpecHandle Handle, FPredictionKey InPredictionKey, UGameplayAbility** OutInstancedAbility, void* /* FOnGameplayAbilityEnded::FDelegate* */ OnGameplayAbilityEndedDelegate, FGameplayEventData* TriggerEventData);
        inline void (*MarkAbilitySpecDirty)(UAbilitySystemComponent* _this, FGameplayAbilitySpec& Spec);
    }

    namespace NetDriver
    {
        inline void* (*SetWorld)(UNetDriver* NetDriver, UWorld* World);
        inline bool (*InitListen)(UObject* Driver, void* InNotify, FURL& LocalURL, bool bReuseAddressAndPort, FString& Error);
        inline void (*TickFlush)(UNetDriver* NetDriver, float DeltaSeconds);
    }

    namespace ReplicationDriver
    {
        inline void (*ServerReplicateActors)(UReplicationDriver* ReplicationDriver);
    }

    namespace NetConnection
    {
        inline void (*ReceiveFString)(void* Bunch, FString& Str);
        inline void (*ReceiveUniqueIdRepl)(void* Bunch, FUniqueNetIdRepl& Str);
    }

    namespace OnlineSession
    {
        inline char (*KickPlayer)(AGameSession* a1, APlayerController*, FText a3);
    }

    namespace World
    {
        inline void (*WelcomePlayer)(UWorld* World, UNetConnection* Connection);
        inline void (*NotifyControlMessage)(UWorld* World, UNetConnection* Connection, uint8_t MessageType, void* Bunch);
        inline APlayerController* (*SpawnPlayActor)(UWorld* World, UPlayer* NewPlayer, ENetRole RemoteRole, FURL& URL, void* UniqueId, SDK::FString& Error, uint8_t NetPlayerIndex);
    }

    namespace Engine
    {
        inline void* (*NetDebug)(UObject* _this);
        inline UNetDriver* (*CreateNetDriver)(UEngine* Engine, UWorld* InWorld, FName NetDriverDefinition);
    }

    namespace FortWeapon
    {
        inline void* (*OnReload)(AFortWeapon* _this, int ammo_count);
    }

    void Initialize()
    {
        Offsets::Imagebase = (uintptr_t)GetModuleHandleA(0);

        UObject::GObjects = Utils::FindPattern<decltype(UObject::GObjects)>(Patterns::GObjects, 3);

        FMemory_Free = Utils::FindPattern<decltype(FMemory_Free)>(Patterns::Free);

        FMemory_Malloc = Utils::FindPattern<decltype(FMemory_Malloc)>(Patterns::Malloc);

        FMemory_Realloc = Utils::FindPattern<decltype(FMemory_Realloc)>(Patterns::Realloc);

        FNameToString = Utils::FindPattern<decltype(FNameToString)>(Patterns::FNameToString);

        NetDriver::TickFlush = Utils::FindPattern<decltype(NetDriver::TickFlush)>(Patterns::TickFlush);

        Engine::CreateNetDriver = Utils::FindPattern<decltype(Engine::CreateNetDriver)>(Patterns::CreateNetDriver);
        MessageBoxA(0, "CreateNetDriver", std::to_string((uintptr_t)Engine::CreateNetDriver).c_str(), 0);

        NetDriver::SetWorld = Utils::FindPattern<decltype(NetDriver::SetWorld)>(Patterns::NetDriver_SetWorld);
        MessageBoxA(0, "NetDriver_SetWorld", std::to_string((uintptr_t)NetDriver::SetWorld).c_str(), 0);

        NetDriver::InitListen = Utils::FindPattern<decltype(NetDriver::InitListen)>(Patterns::InitListen);
        MessageBoxA(0, "InitListen", std::to_string((uintptr_t)NetDriver::InitListen).c_str(), 0);

        World::WelcomePlayer = Utils::FindPattern<decltype(World::WelcomePlayer)>(Patterns::WelcomePlayer);
        MessageBoxA(0, "WelcomePlayer", std::to_string((uintptr_t)World::WelcomePlayer).c_str(), 0);

        World::NotifyControlMessage = Utils::FindPattern<decltype(World::NotifyControlMessage)>(Patterns::World_NotifyControlMessage);
        MessageBoxA(0, "NotifyControlMessage", std::to_string((uintptr_t)World::NotifyControlMessage).c_str(), 0);

        World::SpawnPlayActor = Utils::FindPattern<decltype(World::SpawnPlayActor)>(Patterns::SpawnPlayActor);
        MessageBoxA(0, "SpawnPlayActor", std::to_string((uintptr_t)World::SpawnPlayActor).c_str(), 0);

        NetConnection::ReceiveUniqueIdRepl = Utils::FindPattern<decltype(NetConnection::ReceiveUniqueIdRepl)>(Patterns::ReceiveUniqueIdRepl);

        NetConnection::ReceiveFString = Utils::FindPattern<decltype(NetConnection::ReceiveFString)>(Patterns::ReceiveFString);

        OnlineSession::KickPlayer = Utils::FindPattern<decltype(OnlineSession::KickPlayer)>(Patterns::KickPlayer);

        Actor::GetNetMode = Utils::FindPattern<decltype(Actor::GetNetMode)>(Patterns::GetNetMode);
     

        AbilitySystemComponent::GiveAbility = Utils::FindPattern<decltype(AbilitySystemComponent::GiveAbility)>(Patterns::GiveAbility);
        

        AbilitySystemComponent::InternalTryActivateAbility = Utils::FindPattern<decltype(AbilitySystemComponent::InternalTryActivateAbility)>(Patterns::InternalTryActivateAbility);
       

        AbilitySystemComponent::MarkAbilitySpecDirty = Utils::FindPattern<decltype(AbilitySystemComponent::MarkAbilitySpecDirty)>(Patterns::MarkAbilitySpecDirty);
      

        LocalPlayer::SpawnPlayActor = Utils::FindPattern<decltype(LocalPlayer::SpawnPlayActor)>(Patterns::LocalPlayerSpawnPlayActor);
      

        GC::CollectGarbage = Utils::FindPattern<decltype(GC::CollectGarbage)>(Patterns::CollectGarbage, 0);
        MessageBoxA(0, "CollectGarbage", std::to_string((uintptr_t)GC::CollectGarbage).c_str(), 0);

        Engine::NetDebug = Utils::FindPattern<decltype(Engine::NetDebug)>(Patterns::NetDebug);
        MessageBoxA(0, "NetDebug", std::to_string((uintptr_t)Engine::NetDebug).c_str(), 0);

        FortWeapon::OnReload = Utils::FindPattern<decltype(FortWeapon::OnReload)>(Patterns::OnReload);
        MessageBoxA(0, "OnReload", std::to_string((uintptr_t)FortWeapon::OnReload).c_str(), 0);

        oProcessEvent = reinterpret_cast<decltype(oProcessEvent)>(GetEngine()->Vtable[0x40]);
        MessageBoxA(0, "oProcessEvent", std::to_string((uintptr_t)oProcessEvent).c_str(), 0);
    }
}
