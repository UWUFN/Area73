#pragma once

#include <unordered_set>
#include <random>

#include "functions.h"
#include "FortniteGame/ItemDefinitions/ItemDefinitions.h"


constexpr auto PI = 3.1415926535897932f;

inline bool bTraveled = false;
inline bool bListening = false;
inline bool bTraveled2 = false;
static bool bSpawnedFloorLoot = false;

//static AFortOnlineBeaconHost* HostBeacon = nullptr;

inline UWorld* GetWorld()
{
    return Functions::GetEngine()->GameViewport->World;
}

inline AFortPlayerControllerAthena* GetPlayerController(int32 Index = 0)
{
    if (Index > GetWorld()->OwningGameInstance->LocalPlayers.Num())
        return (AFortPlayerControllerAthena*)GetWorld()->OwningGameInstance->LocalPlayers[0]->PlayerController;

    return (AFortPlayerControllerAthena*)GetWorld()->OwningGameInstance->LocalPlayers[Index]->PlayerController;
}

template <typename T>
static T* FindObjectFast(std::string ObjectName, UClass* ObjectClass = UObject::StaticClass())
{
    auto OrigInName = std::wstring(ObjectName.begin(), ObjectName.end()).c_str();

    static auto StaticFindObjectAddr = Utils::FindPattern<uintptr_t>("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8B EC 48 83 EC 60 80 3D ? ? ? ? ? 45 0F B6 F1");
    auto StaticFindObject = (T * (*)(UClass*, UObject * Package, const wchar_t* OrigInName, bool ExactClass))(StaticFindObjectAddr);
    return StaticFindObject(ObjectClass, nullptr, OrigInName, false);
}

struct FObjectKey
{
public:
    UObject* ResolveObjectPtr() const
    {
        FWeakObjectPtr WeakPtr;
        WeakPtr.ObjectIndex = ObjectIndex;
        WeakPtr.ObjectSerialNumber = ObjectSerialNumber;

        return WeakPtr.Get();
    }

    int32 ObjectIndex;
    int32 ObjectSerialNumber;
};

FORCEINLINE auto& GetClassRepNodePolicies(UObject* ReplicationDriver)
{
    return *reinterpret_cast<TMap<FObjectKey, EClassRepNodeMapping>*>(__int64(ReplicationDriver) + 0x3B8);
}

FORCEINLINE UGameplayStatics* GetGameplayStatics()
{
    return reinterpret_cast<UGameplayStatics*>(UGameplayStatics::StaticClass());
}

FORCEINLINE UKismetSystemLibrary* GetKismetSystem()
{
    return reinterpret_cast<UKismetSystemLibrary*>(UKismetSystemLibrary::StaticClass());
}

FORCEINLINE UFortKismetLibrary* GetFortKismet()
{
    return ((UFortKismetLibrary*)UFortKismetLibrary::StaticClass());
}

FORCEINLINE UKismetStringLibrary* GetKismetString()
{
    return (UKismetStringLibrary*)UKismetStringLibrary::StaticClass();
}

FORCEINLINE UKismetMathLibrary* GetKismetMath()
{
    return (UKismetMathLibrary*)UKismetMathLibrary::StaticClass();
}

static FORCEINLINE void sinCos(float* ScalarSin, float* ScalarCos, float Value)
{
    float quotient = (0.31830988618f * 0.5f) * Value;
    if (Value >= 0.0f)
    {
        quotient = (float)((int)(quotient + 0.5f));
    }
    else
    {
        quotient = (float)((int)(quotient - 0.5f));
    }
    float y = Value - (2.0f * PI) * quotient;

    float sign;
    if (y > 1.57079632679f)
    {
        y = PI - y;
        sign = -1.0f;
    }
    else if (y < -1.57079632679f)
    {
        y = -PI - y;
        sign = -1.0f;
    }
    else
    {
        sign = +1.0f;
    }

    float y2 = y * y;

    *ScalarSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

    float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
    *ScalarCos = sign * p;
}

static auto RotToQuat(FRotator Rotator)
{
    const float DEG_TO_RAD = PI / (180.f);
    const float DIVIDE_BY_2 = DEG_TO_RAD / 2.f;
    float SP, SY, SR;
    float CP, CY, CR;

    sinCos(&SP, &CP, Rotator.Pitch * DIVIDE_BY_2);
    sinCos(&SY, &CY, Rotator.Yaw * DIVIDE_BY_2);
    sinCos(&SR, &CR, Rotator.Roll * DIVIDE_BY_2);

    FQuat RotationQuat;
    RotationQuat.X = CR * SP * SY - SR * CP * CY;
    RotationQuat.Y = -CR * SP * CY - SR * CP * SY;
    RotationQuat.Z = CR * CP * SY - SR * SP * CY;
    RotationQuat.W = CR * CP * CY + SR * SP * SY;

    return RotationQuat;
}

static AActor* SpawnActorTrans(UClass* StaticClass, FTransform SpawnTransform, AActor* Owner = nullptr, ESpawnActorCollisionHandlingMethod Flags = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn)
{
    AActor* FirstActor = GetGameplayStatics()->STATIC_BeginDeferredActorSpawnFromClass(GetWorld(), StaticClass, SpawnTransform, Flags, Owner);

    if (FirstActor)
    {
        AActor* FinalActor = GetGameplayStatics()->STATIC_FinishSpawningActor(FirstActor, SpawnTransform);

        if (FinalActor)
        {
            return FinalActor;
        }
    }

    return nullptr;
}

inline AActor* SpawnActorByClass(UClass* ActorClass, FVector Location = { 0.0f, 0.0f, 0.0f }, FRotator Rotation = { 0, 0, 0 }, AActor* Owner = nullptr, ESpawnActorCollisionHandlingMethod Flags = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn)
{
    FTransform SpawnTransform;

    SpawnTransform.Translation = Location;
    SpawnTransform.Scale3D = FVector{ 1, 1, 1 };
    SpawnTransform.Rotation = RotToQuat(Rotation);

    return SpawnActorTrans(ActorClass, SpawnTransform, Owner, Flags);
}

template <typename RetActorType = AActor>
inline RetActorType* SpawnActor(FVector Location = { 0.0f, 0.0f, 0.0f }, AActor* Owner = nullptr, FQuat Rotation = { 0, 0, 0 }, ESpawnActorCollisionHandlingMethod Flags = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn)
{
    FTransform SpawnTransform;

    SpawnTransform.Translation = Location;
    SpawnTransform.Scale3D = FVector{ 1, 1, 1 };
    SpawnTransform.Rotation = Rotation;

    return (RetActorType*)SpawnActorTrans(RetActorType::StaticClass(), SpawnTransform, Owner, Flags);
}


inline auto CreateCheatManager(APlayerController* Controller)
{
    if (!Controller->CheatManager)
    {
        Controller->CheatManager = (UCheatManager*)GetGameplayStatics()->STATIC_SpawnObject(UFortCheatManager::StaticClass(), Controller);
    }

    return (UFortCheatManager*)Controller->CheatManager;
}


/*
inline FFortItemEntry GetEntryInSlot(AFortPlayerControllerAthena* Controller, int Slot, int Item = 0, EFortQuickBars QuickBars = EFortQuickBars::Primary)
{
    if (!Controller)
        return FFortItemEntry();

    auto& ItemInstances = Controller->WorldInventory->Inventory.ItemInstances;

    FGuid ToFindGuid;

    if (QuickBars == EFortQuickBars::Primary)
        ToFindGuid = Controller->QuickBars->PrimaryQuickBar.Slots[Slot].Items[Item];
    else if (QuickBars == EFortQuickBars::Secondary)
        ToFindGuid = Controller->QuickBars->SecondaryQuickBar.Slots[Slot].Items[Item];

    for (int j = 0; j < ItemInstances.Num(); j++)
    {
        auto ItemInstance = ItemInstances[j];

        if (!ItemInstance)
            continue;

        auto Guid = ItemInstance->ItemEntry.ItemGuid;

        if (ToFindGuid == Guid)
            return ItemInstance->ItemEntry;
    }

    return FFortItemEntry();
}
*/




inline UFortWorldItem* GetInstanceFromGuid(AController* PC, const FGuid& ToFindGuid)
{
    auto& ItemInstances = ((AFortPlayerController*)PC)->WorldInventory->Inventory.ItemInstances;
    for (int j = 0; j < ItemInstances.Num(); j++)
    {
        auto ItemInstance = ItemInstances[j];

        if (!ItemInstance)
            continue;

        auto Guid = ItemInstance->ItemEntry.ItemGuid;

        if (ToFindGuid == Guid)
        {
            return ItemInstance;
        }
    }

    return nullptr;
}

inline bool IsGuidInInventory(AFortPlayerControllerAthena* Controller, const FGuid& Guid)
{
    auto& QuickBarSlots = Controller->QuickBars->PrimaryQuickBar.Slots;

    for (int i = 0; i < QuickBarSlots.Num(); i++)
    {
        if (QuickBarSlots[i].Items.Data)
        {
            auto items = QuickBarSlots[i].Items;

            for (int i = 0; items.Num(); i++)
            {
                if (items[i] == Guid)
                    return true;
            }
        }
    }

    return false;
}

inline AFortWeapon* EquipWeaponDefinition(APawn* dPawn, UFortWeaponItemDefinition* Definition, const FGuid& Guid, int Ammo = -1, bool bEquipWithMaxAmmo = false)
{
    auto weaponClass = Definition->GetWeaponActorClass();
    auto Pawn = (APlayerPawn_Athena_C*)dPawn;
    if (Pawn && Definition && weaponClass)
    {
        auto Controller = (AFortPlayerControllerAthena*)Pawn->Controller;

        if (!IsGuidInInventory(Controller, Guid))
            return nullptr;

        auto Instance = GetInstanceFromGuid(Controller, Guid);

        AFortWeapon* Weapon = nullptr;

        if (weaponClass->GetFullName() == "BlueprintGeneratedClass TrapTool.TrapTool_C")
        {
            Weapon = (AFortWeapon*)SpawnActorTrans(weaponClass, {}, Pawn);

            if (Weapon)
            {
                Weapon->bReplicates = true;
                Weapon->bOnlyRelevantToOwner = false;

                ((AFortTrapTool*)Weapon)->ItemDefinition = Definition;
            }
        }
        else
            Weapon = Pawn->EquipWeaponDefinition(Definition, Guid);

        if (Weapon)
        {
            Weapon->WeaponData = Definition;
            Weapon->ItemEntryGuid = Guid;

            if (bEquipWithMaxAmmo)
                Weapon->AmmoCount = Weapon->GetBulletsPerClip();
            else if (Ammo != -1)
                Weapon->AmmoCount = Ammo;

            if (Instance->ItemEntry.ItemDefinition->ObjectFlags)

                Instance->ItemEntry.LoadedAmmo = Weapon->AmmoCount;

            Weapon->Owner = dPawn;
            Weapon->SetOwner(dPawn);
            Weapon->OnRep_ReplicatedWeaponData();
            Weapon->OnRep_AmmoCount(Instance->ItemEntry.LoadedAmmo);
            Weapon->ClientGivenTo(Pawn);
            Pawn->ClientInternalEquipWeapon(Weapon);
            Pawn->OnRep_CurrentWeapon(); //boh
        }

        return Weapon;
    }

    return nullptr;
}

inline AFortWeapon* EquipInventoryItem(AFortPlayerControllerAthena* PC, FGuid& Guid)
{
    if (!PC || PC->IsInAircraft())
        return 0;

    auto& ItemInstances = PC->WorldInventory->Inventory.ItemInstances;

    for (int i = 0; i < ItemInstances.Num(); i++)
    {
        auto CurrentItemInstance = ItemInstances[i];

        if (!CurrentItemInstance)
            continue;

        auto Def = (UFortWeaponItemDefinition*)CurrentItemInstance->GetItemDefinitionBP();

        if (CurrentItemInstance->GetItemGuid() == Guid && Def)
        {
            return EquipWeaponDefinition((APlayerPawn_Athena_C*)PC->Pawn, Def, Guid);
        }
    }
}










static AFortPickup* SummonPickup(AFortPlayerPawn* Pawn, auto ItemDef, int Count, FVector Location)
{
    auto FortPickup = SpawnActor<AFortPickup>(Location, Pawn);

    FortPickup->bReplicates = true;

    FortPickup->PrimaryPickupItemEntry.Count = Count;
    FortPickup->PrimaryPickupItemEntry.ItemDefinition = ItemDef;

    FortPickup->OnRep_PrimaryPickupItemEntry();
    FortPickup->TossPickup(Location, Pawn, 6, true);

    return FortPickup;
}

static AFortPickup* SummonPickupFromChest(UFortItemDefinition* ItemDef, int Count, FVector Location)
{
    auto FortPickup = SpawnActor<AFortPickup>(Location);
    if (!FortPickup) return 0;

    FortPickup->bReplicates = true;
    //FortPickup->bTossedFromContainer = true;

    FortPickup->PrimaryPickupItemEntry.Count = Count;
    FortPickup->PrimaryPickupItemEntry.ItemDefinition = ItemDef;

    FortPickup->OnRep_PrimaryPickupItemEntry();
    //FortPickup->OnRep_TossedFromContainer();
    FortPickup->TossPickup(Location, 0, 6, true);

    return FortPickup;
}

inline void SpawnPickupFromFloorLoot(auto ItemDef, int Count, FVector Location)
{
    auto FortPickup = SpawnActor<AFortPickup>(Location);

    FortPickup->bReplicates = true;

    FortPickup->PrimaryPickupItemEntry.Count = Count;
    FortPickup->PrimaryPickupItemEntry.ItemDefinition = ItemDef;

    FortPickup->OnRep_PrimaryPickupItemEntry();
}



template <typename Class>
static FFortItemEntry FindItemInInventory(AFortPlayerControllerAthena* PC, bool& bFound)
{

    auto ret = FFortItemEntry();
    
    auto& ItemInstances = PC->WorldInventory->Inventory.ItemInstances;

    bFound = false;

    for (int i = 0; i < ItemInstances.Num(); i++)
    {
        auto ItemInstance = ItemInstances[i];

        if (!ItemInstance)
            continue;

        auto Def = ItemInstance->ItemEntry.ItemDefinition;

        if (Def && Def->IsA(Class::StaticClass()))
        {
            bFound = true;
            ret = ItemInstance->ItemEntry;
        }
    }
    
    return ret;
}

FGameplayAbilitySpec* UAbilitySystemComponent_FindAbilitySpecFromHandle(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAbilitySpecHandle Handle)
{
    auto Specs = AbilitySystemComponent->ActivatableAbilities.Items;

    for (int i = 0; i < Specs.Num(); i++)
    {
        auto& Spec = Specs[i];

        if (Spec.Handle.Handle == Handle.Handle)
        {
            return &Spec;
        }
    }

    return nullptr;
}

auto TryActivateAbility(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAbilitySpecHandle AbilityToActivate, bool InputPressed, FPredictionKey* PredictionKey, FGameplayEventData* TriggerEventData)
{
    auto Spec = UAbilitySystemComponent_FindAbilitySpecFromHandle(AbilitySystemComponent, AbilityToActivate);

    if (!Spec)
    {
        printf("InternalServerTryActiveAbility. Rejecting ClientActivation of ability with invalid SpecHandle!\n");
        AbilitySystemComponent->ClientActivateAbilityFailed(AbilityToActivate, PredictionKey->Current);
        return;
    }


    UGameplayAbility* InstancedAbility = nullptr;
    Spec->InputPressed = true;

    if (!Functions::AbilitySystemComponent::InternalTryActivateAbility(AbilitySystemComponent, AbilityToActivate, *PredictionKey, &InstancedAbility, nullptr, TriggerEventData))
    {
        printf("InternalServerTryActiveAbility. Rejecting ClientActivation of %s. InternalTryActivateAbility failed\n", Spec->Ability->GetName().c_str());
        AbilitySystemComponent->ClientActivateAbilityFailed(AbilityToActivate, PredictionKey->Current);
        Spec->InputPressed = false;
        return;
    }

    Functions::AbilitySystemComponent::MarkAbilitySpecDirty(AbilitySystemComponent, *Spec);
}

static auto GrantGameplayAbility(APlayerPawn_Athena_C* TargetPawn, UClass* GameplayAbilityClass)
{
    auto AbilitySystemComponent = TargetPawn->AbilitySystemComponent;

    if (!AbilitySystemComponent)
        return;

    auto GenerateNewSpec = [&]() -> FGameplayAbilitySpec
    {
        FGameplayAbilitySpecHandle Handle{ rand() };

        FGameplayAbilitySpec Spec{ -1, -1, -1, Handle, (UGameplayAbility*)GameplayAbilityClass->CreateDefaultObject(), 1, -1, nullptr, 0, false, false, false };

        return Spec;
    };

    auto Spec = GenerateNewSpec();

    for (int i = 0; i < AbilitySystemComponent->ActivatableAbilities.Items.Num(); i++)
    {
        auto& CurrentSpec = AbilitySystemComponent->ActivatableAbilities.Items[i];

        if (CurrentSpec.Ability == Spec.Ability)
            return;
    }

    auto Handle = Functions::AbilitySystemComponent::GiveAbility(AbilitySystemComponent, &Spec.Handle, Spec);
}

static bool KickController(APlayerController* PC, FString Message)
{
    if (PC && Message.Data)
    {
        FText text = reinterpret_cast<UKismetTextLibrary*>(UKismetTextLibrary::StaticClass())->STATIC_Conv_StringToText(Message);
        return Functions::OnlineSession::KickPlayer(GetWorld()->AuthorityGameMode->GameSession, PC, text);
    }

    return false;
}

auto GetAllActorsOfClass(UClass* Class)
{
    TArray<AActor*> OutActors;

    static auto GameplayStatics = (UGameplayStatics*)UGameplayStatics::StaticClass()->CreateDefaultObject();
    GameplayStatics->STATIC_GetAllActorsOfClass(GetWorld(), Class, &OutActors);

    return OutActors;
}

FTransform GetPlayerStart(AFortPlayerControllerAthena* PC)
{
    auto OutActors = GetAllActorsOfClass(AFortPlayerStartWarmup::StaticClass());

    auto ActorsNum = OutActors.Num();

    auto SpawnTransform = FTransform();
    SpawnTransform.Scale3D = FVector(1, 1, 1);
    SpawnTransform.Rotation = FQuat();
    SpawnTransform.Translation = FVector{ 1250, 1818, 3284 };

    auto GamePhase = ((AFortGameStateAthena*)GetWorld()->GameState)->GamePhase;

    if (ActorsNum != 0 && (GamePhase == EAthenaGamePhase::Setup || GamePhase == EAthenaGamePhase::Warmup))
    {
        auto ActorToUseNum = rand() % ActorsNum;
        auto ActorToUse = OutActors[ActorToUseNum];

        while (!ActorToUse)
        {
            ActorToUseNum = rand() % ActorsNum;
            ActorToUse = OutActors[ActorToUseNum];
        }

        SpawnTransform.Translation = ActorToUse->K2_GetActorLocation();

        PC->WarmupPlayerStart = (AFortPlayerStartWarmup*)ActorToUse;
    }

    OutActors.FreeArray();

    return SpawnTransform;
}

inline auto ApplyAbilities(APawn* _Pawn)
{
    auto Pawn = (APlayerPawn_Athena_C*)_Pawn;

    static auto SprintAbility = UObject::FindClass("Class FortniteGame.FortGameplayAbility_Sprint");
    static auto ReloadAbility = UObject::FindClass("Class FortniteGame.FortGameplayAbility_Reload");
    static auto RangedWeaponAbility = UObject::FindClass("Class FortniteGame.FortGameplayAbility_RangedWeapon");
    static auto JumpAbility = UObject::FindClass("Class FortniteGame.FortGameplayAbility_Jump");
    static auto DeathAbility = UObject::FindClass("BlueprintGeneratedClass GA_DefaultPlayer_Death.GA_DefaultPlayer_Death_C");
    static auto InteractUseAbility = UObject::FindClass("BlueprintGeneratedClass GA_DefaultPlayer_InteractUse.GA_DefaultPlayer_InteractUse_C");
    static auto InteractSearchAbility = UObject::FindClass("BlueprintGeneratedClass GA_DefaultPlayer_InteractSearch.GA_DefaultPlayer_InteractSearch_C");
    static auto EmoteAbility = UObject::FindClass("BlueprintGeneratedClass GAB_Emote_Generic.GAB_Emote_Generic_C");
    static auto TrapAbility = UObject::FindClass("BlueprintGeneratedClass GA_TrapBuildGeneric.GA_TrapBuildGeneric_C");
    static auto DanceGrenadeAbility = UObject::FindClass("BlueprintGeneratedClass GA_DanceGrenade_Stun.GA_DanceGrenade_Stun_C");

#ifdef VERSION_7_3
    static auto VehicleEnter = UObject::FindClass("BlueprintGeneratedClass GA_AthenaEnterVehicle.GA_AthenaEnterVehicle_C");
    static auto VehicleExit = UObject::FindClass("BlueprintGeneratedClass GA_AthenaExitVehicle.GA_AthenaExitVehicle_C");
    static auto InVehicle = UObject::FindClass("BlueprintGeneratedClass GA_AthenaInVehicle.GA_AthenaInVehicle_C");
#endif

    /*
    static auto DBNOPlayerAbility = UObject::FindClass("BlueprintGeneratedClass GAB_PlayerDBNO.GAB_PlayerDBNO_C");
    static auto DBNOAthenaAbility = UObject::FindClass("BlueprintGeneratedClass GAB_AthenaDBNO.GAB_AthenaDBNO_C");
    static auto AthenaDBNORevive = UObject::FindClass("BlueprintGeneratedClass GAB_AthenaDBNORevive.GAB_AthenaDBNORevive_C");
    static auto PlayerDBNOResurrect = UObject::FindClass("BlueprintGeneratedClass GAB_PlayerDBNOResurrect.GAB_PlayerDBNOResurrect_C");
    */

    GrantGameplayAbility(Pawn, SprintAbility);
    GrantGameplayAbility(Pawn, ReloadAbility);
    GrantGameplayAbility(Pawn, RangedWeaponAbility);
    GrantGameplayAbility(Pawn, JumpAbility);
    GrantGameplayAbility(Pawn, DeathAbility);
    GrantGameplayAbility(Pawn, InteractUseAbility);
    GrantGameplayAbility(Pawn, InteractSearchAbility);
    GrantGameplayAbility(Pawn, EmoteAbility);
    GrantGameplayAbility(Pawn, TrapAbility);
    GrantGameplayAbility(Pawn, DanceGrenadeAbility);

#ifdef VERSION_7_3
    GrantGameplayAbility(Pawn, VehicleEnter);
    GrantGameplayAbility(Pawn, VehicleExit);
    GrantGameplayAbility(Pawn, InVehicle);
#endif
    //GrantGameplayAbility(Pawn, DBNOPlayerAbility);
    //GrantGameplayAbility(Pawn, DBNOAthenaAbility);
    //GrantGameplayAbility(Pawn, AthenaDBNORevive);
    //GrantGameplayAbility(Pawn, PlayerDBNOResurrect);

}



DWORD WINAPI SummonFloorLoot(LPVOID)
{
    //if (!bSpawnedFloorLoot)
    {
        static auto FloorLootClass = UObject::FindObject<UClass>("BlueprintGeneratedClass Tiered_Athena_FloorLoot_01.Tiered_Athena_FloorLoot_01_C");

        if (!FloorLootClass)
            return 0;

        auto FloorLootActors = GetAllActorsOfClass(FloorLootClass);
        std::cout << "FLOORLOOTACTORS: " << FloorLootActors.Num() << "\n";
        //auto AmountOfActorsToSpawn = 20;

        std::cout << "Spawning " << FloorLootActors.Num() << " pickups\n";

        for (int i = 0; i < FloorLootActors.Num(); i++)
        {
            auto FloorLootActor = FloorLootActors[i];
            if (IsBadWritePtr(FloorLootActor, 8)) continue;

            auto Location = FloorLootActor->K2_GetActorLocation();
            if (Location.Z < 20) continue;

            int brps = rand() >> 5;
            brps = brps % 4 + 1;

            std::cout << "Spawning Pickup At X: " << Location.X << " Y: " << Location.Y << " Z: " << Location.Z << "\n";

            UFortItemDefinition* ItemDef = 0;
            int ItemDefCount = 1;

            switch (brps)
            {
            case 1:
                ItemDef = ItemDefinitions::GetWeapon(true);
                //SummonPickupFromChest(ItemDefinitions::GetAmmoOfWeapon(ItemDef), 20, FVector(Location.X, Location.Y, Location.Z + 100));
                break;
            case 2:
                ItemDef = ItemDefinitions::GetAmmo(true, &ItemDefCount);
                break;
            case 3:
                ItemDef = ItemDefinitions::GetConsumable(true, &ItemDefCount);
                break;
            case 4:
                ItemDef = ItemDefinitions::GetMaterial(true);
                ItemDefCount = 50;
                break;
            }

            if (ItemDef)
                SummonPickupFromChest(ItemDef, ItemDefCount, FVector(Location.X, Location.Y, Location.Z + 100));

            Sleep(100);
        }

        std::cout << "Spawned " << FloorLootActors.Num() << " pickups\n";

        /*
        if (GetWorld() && GetWorld()->NetDriver && GetWorld()->NetDriver->ClientConnections.Data)
        {
            auto Connections = HostBeacon->NetDriver->ClientConnections;

            for (int i = 0; i < Connections.Num(); i++)
            {
                auto Controller = (AFortPlayerControllerAthena*)Connections[i]->PlayerController;

                if (!Controller || !Controller->IsA(AFortPlayerControllerAthena::StaticClass()) || Controller->PlayerState->bIsSpectator)
                    continue;

                auto Pawn = Controller->Pawn;
                if (!Pawn) continue;

                Pawn->K2_TeleportTo(storelocShit, {});
            }
        }
        */

    }

    bSpawnedFloorLoot = true;

    return 0;
}


void EquipTrapTool(AController* Controller)
{
    static auto TrapDef = UObject::FindObject<UFortTrapItemDefinition>("FortTrapItemDefinition TID_Floor_Player_Launch_Pad_Athena.TID_Floor_Player_Launch_Pad_Athena");

    auto TrapTool = (AFortTrapTool*)SpawnActorTrans(TrapDef->GetWeaponActorClass(), {}, Controller);

    if (TrapTool && TrapDef)
    {
        TrapTool->ItemDefinition = TrapDef;

        auto Pawn = (APlayerPawn_Athena_C*)Controller->Pawn;
        if (Pawn) // && weaponClass)
        {
            if (TrapTool)
            {
                TrapTool->WeaponData = TrapDef;
                TrapTool->SetOwner(Pawn);
                TrapTool->OnRep_ReplicatedWeaponData();
                TrapTool->ClientGivenTo(Pawn);
                Pawn->ClientInternalEquipWeapon(TrapTool);
                Pawn->OnRep_CurrentWeapon();
            }
        }
    }
}

APlayerPawn_Athena_C* InitializePawnNOCP(AFortPlayerControllerAthena* PlayerController, FVector Loc = FVector(), FQuat Rot = FQuat(), bool open_glider = false)
{
    if (PlayerController->Pawn)
        PlayerController->Pawn->K2_DestroyActor();

    if (Loc.X == 0 && Loc.Y == 0 && Loc.Z == 0)
        Loc = GetPlayerStart(PlayerController).Translation;

    auto Pawn = SpawnActor< APlayerPawn_Athena_C>(Loc, PlayerController, Rot);
    Pawn->Owner = PlayerController;
    Pawn->OnRep_Owner();

    Pawn->NetCullDistanceSquared = 0.f;

    PlayerController->Pawn = Pawn;
    PlayerController->AcknowledgedPawn = Pawn;
    PlayerController->AcknowledgedPawn = PlayerController->Pawn;
    PlayerController->OnRep_Pawn();
    PlayerController->Possess(Pawn);
   
    
    Pawn->bReplicateMovement = true; 
    Pawn->OnRep_ReplicateMovement(); 
    Pawn->OnRep_ReplicatedMovement(); 
    Pawn->OnRep_ReplicatedBasedMovement();

    if (open_glider)
        Pawn->CharacterMovement->SetMovementMode(EMovementMode::MOVE_Custom, 4U);


    Pawn->SetMaxHealth(100);
    Pawn->SetMaxShield(100);

    auto PlayerState = (AFortPlayerStateAthena*)PlayerController->PlayerState;

    auto& HealthSet = Pawn->HealthSet;
    Pawn->SetHealth(100);
    HealthSet->Health.CurrentValue = 100;
    PlayerState->CurrentHealth = 100;
    HealthSet->OnRep_Health();

    PlayerState->CurrentShield = 100;
    HealthSet->Shield.CurrentValue = 100;
    HealthSet->OnRep_Shield();
    HealthSet->CurrentShield.CurrentValue = 100;
    HealthSet->OnRep_CurrentShield();


    PlayerController->bHasClientFinishedLoading = true;
    PlayerController->bHasServerFinishedLoading = true;
    PlayerController->bHasInitiallySpawned = true;
    PlayerController->OnRep_bHasServerFinishedLoading();


    PlayerState->bHasFinishedLoading = true;
    PlayerState->bHasStartedPlaying = true;
    PlayerState->OnRep_bHasStartedPlaying();


    //auto FortRegisteredPlayerInfo = ((UFortGameInstance*)GetWorld()->OwningGameInstance)->RegisteredPlayers[0];
    //auto FortRegisteredPlayerInfo = PlayerController->GetRegisteredPlayerInfo();
    //auto FortRegisteredPlayerInfo = PlayerController->MyPlayerInfo;

    //if (FortRegisteredPlayerInfo)
    {
//        auto HeroType = UObject::FindObject<UFortHeroType>("FortHeroType HID_Outlander_015_F_V1_SR_T04.HID_Outlander_015_F_V1_SR_T04");//FortRegisteredPlayerInfo->AthenaMenuHeroDef;
//
//        PlayerState->HeroType = HeroType;
//        PlayerState->OnRep_HeroType();
//
//        static auto Head = UObject::FindObject<UCustomCharacterPart>("CustomCharacterPart F_Med_Head1.F_Med_Head1");
//        static auto Body = UObject::FindObject<UCustomCharacterPart>("CustomCharacterPart F_Med_Soldier_01.F_Med_Soldier_01");
//
//#ifdef VERSION_7_3
//        PlayerState->CharacterParts.Parts[(uint8_t)EFortCustomPartType::Head] = Head;
//         PlayerState->CharacterParts.Parts[(uint8_t)EFortCustomPartType::Body] = Body;
//#else
//        PlayerState->CharacterParts[(uint8_t)EFortCustomPartType::Head] = Head;
//        PlayerState->CharacterParts[(uint8_t)EFortCustomPartType::Body] = Body;
//#endif
//
//
//        PlayerState->OnRep_CharacterParts();

        /*
        auto Hero = FortRegisteredPlayerInfo->AthenaMenuHeroDef;

        PlayerState->HeroType = Hero->GetHeroTypeBP();
        PlayerState->OnRep_HeroType();

        for (int i = 0; i < Hero->CharacterParts.Num(); i++)
        {
            auto Part = Hero->CharacterParts[i];
            if (!Part) continue;

            PlayerState->CharacterParts[i] = Part;
        }

        //PlayerState->CharacterBodyType = Hero->CharacterParts[1]->BodyTypesPermitted;
        //Pawn->CharacterBodyType = Hero->CharacterParts[1]->BodyTypesPermitted;
        //Pawn->CharacterGender = Hero->CharacterParts[1]->GenderPermitted;
        PlayerState->OnRep_CharacterBodyType();
        PlayerState->OnRep_CharacterParts();
        */

        //Default Skin
        /*
        auto Hero = FortRegisteredPlayerInfo->AthenaMenuHeroDef;

        if (Hero)
        {
            UFortHeroType* HeroType = Hero->GetHeroTypeBP(); //UObject::FindObject<UFortHeroType>("FortHeroType HID_Outlander_015_F_V1_SR_T04.HID_Outlander_015_F_V1_SR_T04");
            PlayerState->HeroType = HeroType;
            PlayerState->OnRep_HeroType();

            static auto Head = UObject::FindObject<UCustomCharacterPart>("CustomCharacterPart F_Med_Head1.F_Med_Head1");
            static auto Body = UObject::FindObject<UCustomCharacterPart>("CustomCharacterPart F_Med_Soldier_01.F_Med_Soldier_01");

            PlayerState->CharacterParts[(uint8_t)EFortCustomPartType::Head] = Head;
            PlayerState->CharacterParts[(uint8_t)EFortCustomPartType::Body] = Body;
            PlayerState->OnRep_CharacterParts();
        }
        */
    }

    return Pawn;
}

APlayerPawn_Athena_C* InitializePawn(AFortPlayerControllerAthena* PlayerController, FVector Loc = FVector(), FQuat Rot = FQuat(), bool open_glider = false)
{
    if (PlayerController->Pawn)
        PlayerController->Pawn->K2_DestroyActor();

    if (Loc.X == 0 && Loc.Y == 0 && Loc.Z == 0)
        Loc = GetPlayerStart(PlayerController).Translation;

    auto Pawn = SpawnActor< APlayerPawn_Athena_C>(Loc, PlayerController, Rot);
    Pawn->Owner = PlayerController;
    Pawn->OnRep_Owner();

    Pawn->NetCullDistanceSquared = 0.f;

    PlayerController->Pawn = Pawn;
    PlayerController->AcknowledgedPawn = Pawn;
    PlayerController->AcknowledgedPawn = PlayerController->Pawn;
    PlayerController->OnRep_Pawn();
    PlayerController->Possess(Pawn);


    Pawn->bReplicateMovement = true;
    Pawn->OnRep_ReplicateMovement();
    Pawn->OnRep_ReplicatedMovement();
    Pawn->OnRep_ReplicatedBasedMovement();

    if (open_glider)
        Pawn->CharacterMovement->SetMovementMode(EMovementMode::MOVE_Custom, 3U);


    Pawn->SetMaxHealth(100);
    Pawn->SetMaxShield(100);

    auto PlayerState = (AFortPlayerStateAthena*)PlayerController->PlayerState;

    auto& HealthSet = Pawn->HealthSet;
    Pawn->SetHealth(100);
    HealthSet->Health.CurrentValue = 100;
    PlayerState->CurrentHealth = 100;
    HealthSet->OnRep_Health();

    PlayerState->CurrentShield = 100;
    HealthSet->Shield.CurrentValue = 100;
    HealthSet->OnRep_Shield();
    HealthSet->CurrentShield.CurrentValue = 100;
    HealthSet->OnRep_CurrentShield();


    PlayerController->bHasClientFinishedLoading = true;
    PlayerController->bHasServerFinishedLoading = true;
    PlayerController->bHasInitiallySpawned = true;
    PlayerController->OnRep_bHasServerFinishedLoading();


    PlayerState->bHasFinishedLoading = true;
    PlayerState->bHasStartedPlaying = true;
    PlayerState->OnRep_bHasStartedPlaying();


    //auto FortRegisteredPlayerInfo = ((UFortGameInstance*)GetWorld()->OwningGameInstance)->RegisteredPlayers[0];
    //auto FortRegisteredPlayerInfo = PlayerController->GetRegisteredPlayerInfo();
    //auto FortRegisteredPlayerInfo = PlayerController->MyPlayerInfo;

    //if (FortRegisteredPlayerInfo)
    {
        auto HeroType = UObject::FindObject<UFortHeroType>("FortHeroType HID_Outlander_015_F_V1_SR_T04.HID_Outlander_015_F_V1_SR_T04");//FortRegisteredPlayerInfo->AthenaMenuHeroDef;

        PlayerState->HeroType = HeroType;
        PlayerState->OnRep_HeroType();

        static auto Head = UObject::FindObject<UCustomCharacterPart>("CustomCharacterPart F_Med_Head1.F_Med_Head1");
        static auto Body = UObject::FindObject<UCustomCharacterPart>("CustomCharacterPart F_Med_Soldier_01.F_Med_Soldier_01");

#ifdef VERSION_7_3
        PlayerState->CharacterParts.Parts[(uint8_t)EFortCustomPartType::Head] = Head;
        PlayerState->CharacterParts.Parts[(uint8_t)EFortCustomPartType::Body] = Body;
#else
        PlayerState->CharacterParts[(uint8_t)EFortCustomPartType::Head] = Head;
        PlayerState->CharacterParts[(uint8_t)EFortCustomPartType::Body] = Body;
#endif


        PlayerState->OnRep_CharacterParts();

        /*
        auto Hero = FortRegisteredPlayerInfo->AthenaMenuHeroDef;

        PlayerState->HeroType = Hero->GetHeroTypeBP();
        PlayerState->OnRep_HeroType();

        for (int i = 0; i < Hero->CharacterParts.Num(); i++)
        {
            auto Part = Hero->CharacterParts[i];
            if (!Part) continue;

            PlayerState->CharacterParts[i] = Part;
        }

        //PlayerState->CharacterBodyType = Hero->CharacterParts[1]->BodyTypesPermitted;
        //Pawn->CharacterBodyType = Hero->CharacterParts[1]->BodyTypesPermitted;
        //Pawn->CharacterGender = Hero->CharacterParts[1]->GenderPermitted;
        PlayerState->OnRep_CharacterBodyType();
        PlayerState->OnRep_CharacterParts();
        */

        //Default Skin
        /*
        auto Hero = FortRegisteredPlayerInfo->AthenaMenuHeroDef;

        if (Hero)
        {
            UFortHeroType* HeroType = Hero->GetHeroTypeBP(); //UObject::FindObject<UFortHeroType>("FortHeroType HID_Outlander_015_F_V1_SR_T04.HID_Outlander_015_F_V1_SR_T04");
            PlayerState->HeroType = HeroType;
            PlayerState->OnRep_HeroType();

            static auto Head = UObject::FindObject<UCustomCharacterPart>("CustomCharacterPart F_Med_Head1.F_Med_Head1");
            static auto Body = UObject::FindObject<UCustomCharacterPart>("CustomCharacterPart F_Med_Soldier_01.F_Med_Soldier_01");

            PlayerState->CharacterParts[(uint8_t)EFortCustomPartType::Head] = Head;
            PlayerState->CharacterParts[(uint8_t)EFortCustomPartType::Body] = Body;
            PlayerState->OnRep_CharacterParts();
        }
        */
    }

    return Pawn;
}