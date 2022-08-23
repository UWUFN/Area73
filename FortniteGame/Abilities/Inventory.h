#pragma once
#include "ue4.h"

namespace Abilities
{
    namespace Inventory
    {
        inline void Update(AFortPlayerController* Controller, int Dirty = 0, bool bRemovedItem = false)
        {
            if (!Controller)
                return;

            Controller->WorldInventory->bRequiresLocalUpdate = true;
            Controller->WorldInventory->HandleInventoryLocalUpdate();
            Controller->WorldInventory->ForceNetUpdate();
            Controller->HandleWorldInventoryLocalUpdate();

            Controller->QuickBars->OnRep_PrimaryQuickBar();
            Controller->QuickBars->OnRep_SecondaryQuickBar();
            Controller->QuickBars->ForceNetUpdate();
            Controller->ForceUpdateQuickbar(EFortQuickBars::Primary);
            Controller->ForceUpdateQuickbar(EFortQuickBars::Secondary);

            if (bRemovedItem)
                Controller->WorldInventory->Inventory.MarkArrayDirty();

            if (Dirty != 0 && Controller->WorldInventory->Inventory.ReplicatedEntries.Num() >= Dirty)
                Controller->WorldInventory->Inventory.MarkItemDirty(Controller->WorldInventory->Inventory.ReplicatedEntries[Dirty]);


        }

        inline auto AddItem(AFortPlayerController* PC, UFortWorldItem* SlotInstance, int Slot, EFortQuickBars Bars = EFortQuickBars::Primary, int Count = 1)
        {
            SlotInstance->SetOwningControllerForTemporaryItem(PC);

            SlotInstance->ItemEntry.Count = Count;
            SlotInstance->OwnerInventory = PC->WorldInventory;

            auto& ItemEntry = SlotInstance->ItemEntry;

            auto Idx = PC->WorldInventory->Inventory.ReplicatedEntries.Add(ItemEntry);

            PC->WorldInventory->Inventory.ItemInstances.Add((UFortWorldItem*)SlotInstance);
            PC->QuickBars->ServerAddItemInternal(ItemEntry.ItemGuid, Bars, Slot);

            if (Idx && PC->WorldInventory->Inventory.ReplicatedEntries.Num() >= Idx)
                PC->WorldInventory->Inventory.MarkItemDirty(PC->WorldInventory->Inventory.ReplicatedEntries[Idx]);

            Update(PC);

            return ItemEntry;
        }

        inline auto AddNewItem(AFortPlayerController* PC, UFortItemDefinition* Def, int Slot, EFortQuickBars Bars = EFortQuickBars::Primary, int Count = 1)
        {
            if (!PC || !Def)
                return FFortItemEntry();

            if (Slot < 0)
                return  FFortItemEntry();
            //Slot = 1;

            if (Bars == EFortQuickBars::Primary && Slot >= 6)
                return FFortItemEntry();
            //Slot = 5;

            auto& QuickBarSlots = PC->QuickBars->PrimaryQuickBar.Slots;

            auto TempItemInstance = (UFortWorldItem*)Def->CreateTemporaryItemInstanceBP(Count, 1);

            if (TempItemInstance)
            {
                TempItemInstance->SetOwningControllerForTemporaryItem(PC);

                TempItemInstance->ItemEntry.Count = Count;
                TempItemInstance->OwnerInventory = PC->WorldInventory;

                auto& ItemEntry = TempItemInstance->ItemEntry;

                auto Idx = PC->WorldInventory->Inventory.ReplicatedEntries.Add(ItemEntry);

                return AddItem(PC, TempItemInstance, Slot, Bars, Count);

                if (Idx && PC->WorldInventory->Inventory.ReplicatedEntries.Num() >= Idx)
                    PC->WorldInventory->Inventory.MarkItemDirty(PC->WorldInventory->Inventory.ReplicatedEntries[Idx]);

                return ItemEntry;
            }

            return FFortItemEntry();
        }

        inline static void InitInventory(AFortPlayerController* PlayerController)
        {
            PlayerController->QuickBars = SpawnActor<AFortQuickBars>({ -280, 400, 3000 }, PlayerController);
            auto QuickBars = PlayerController->QuickBars;
            PlayerController->OnRep_QuickBar();

            static auto Wall = UObject::FindObject<UFortBuildingItemDefinition>("FortBuildingItemDefinition BuildingItemData_Wall.BuildingItemData_Wall");
            static auto Floor = UObject::FindObject<UFortBuildingItemDefinition>("FortBuildingItemDefinition BuildingItemData_Floor.BuildingItemData_Floor");
            static auto Stair = UObject::FindObject<UFortBuildingItemDefinition>("FortBuildingItemDefinition BuildingItemData_Stair_W.BuildingItemData_Stair_W");
            static auto Cone = UObject::FindObject<UFortBuildingItemDefinition>("FortBuildingItemDefinition BuildingItemData_RoofS.BuildingItemData_RoofS");

            static auto Wood = ItemDefinitions::GetMaterial(false, ItemDefinitions::MaterialItemDefinitionNames::Wood);
            static auto Stone = ItemDefinitions::GetMaterial(false, ItemDefinitions::MaterialItemDefinitionNames::Stone);
            static auto Metal = ItemDefinitions::GetMaterial(false, ItemDefinitions::MaterialItemDefinitionNames::Metal);

            int Ammo_Count;
            static auto Rockets = ItemDefinitions::GetAmmo(false, &Ammo_Count, ItemDefinitions::AmmoItemDefinitionNames::Rockets);
            static auto Shells = ItemDefinitions::GetAmmo(false, &Ammo_Count, ItemDefinitions::AmmoItemDefinitionNames::Shells);
            static auto Medium = ItemDefinitions::GetAmmo(false, &Ammo_Count, ItemDefinitions::AmmoItemDefinitionNames::Medium);
            static auto Light = ItemDefinitions::GetAmmo(false, &Ammo_Count, ItemDefinitions::AmmoItemDefinitionNames::Light);
            static auto Heavy = ItemDefinitions::GetAmmo(false, &Ammo_Count, ItemDefinitions::AmmoItemDefinitionNames::Heavy);

            static auto EditTool = UObject::FindObject<UFortAmmoItemDefinition>("FortEditToolItemDefinition EditTool.EditTool");

            AddNewItem(PlayerController, Wall, 0, EFortQuickBars::Secondary, 1);
            AddNewItem(PlayerController, Floor, 1, EFortQuickBars::Secondary, 1);
            AddNewItem(PlayerController, Stair, 2, EFortQuickBars::Secondary, 1);
            AddNewItem(PlayerController, Cone, 3, EFortQuickBars::Secondary, 1);


            AddNewItem(PlayerController, Wood, 0, EFortQuickBars::Secondary, 500);
            AddNewItem(PlayerController, Stone, 0, EFortQuickBars::Secondary, 500);
            AddNewItem(PlayerController, Metal, 0, EFortQuickBars::Secondary, 500);

            AddNewItem(PlayerController, Rockets, 0, EFortQuickBars::Secondary, 999);
            AddNewItem(PlayerController, Shells, 0, EFortQuickBars::Secondary, 999);
            AddNewItem(PlayerController, Medium, 0, EFortQuickBars::Secondary, 999);
            AddNewItem(PlayerController, Light, 0, EFortQuickBars::Secondary, 999);
            AddNewItem(PlayerController, Heavy, 0, EFortQuickBars::Secondary, 999);


            AddNewItem(PlayerController, EditTool, 0, EFortQuickBars::Primary, 1);

            QuickBars->ServerActivateSlotInternal(EFortQuickBars::Primary, 0, 0, true, true);
        }


        inline void RemoveBuildingMaterials(AFortPlayerControllerAthena* PC, UClass* BuildingClass, int Amount = 10)
        {
            auto BuildingClassName = BuildingClass->GetName();

            auto Inventory = PC->WorldInventory;

            for (int i = 0; i < Inventory->Inventory.ReplicatedEntries.Num(); i++)
            {
                auto ItemDefinitionName = Inventory->Inventory.ReplicatedEntries[i].ItemDefinition->GetName();

                if (strstr(BuildingClassName.c_str(), "W1") && strstr(ItemDefinitionName.c_str(), "WoodItemData"))
                {
                    Inventory->Inventory.ReplicatedEntries[i].Count -= Amount;
                    Inventory->Inventory.ReplicatedEntries[i].ReplicationKey++;

                    Update(PC, 0, true);
                    return;
                }

                if (strstr(BuildingClassName.c_str(), "S1") && strstr(ItemDefinitionName.c_str(), "StoneItemData"))
                {
                    Inventory->Inventory.ReplicatedEntries[i].Count -= Amount;
                    Inventory->Inventory.ReplicatedEntries[i].ReplicationKey++;

                    Update(PC, 0, true);
                    return;
                }

                if (strstr(BuildingClassName.c_str(), "M1") && strstr(ItemDefinitionName.c_str(), "MetalItemData"))
                {
                    Inventory->Inventory.ReplicatedEntries[i].Count -= Amount;
                    Inventory->Inventory.ReplicatedEntries[i].ReplicationKey++;

                    Update(PC, 0, true);
                    return;
                }
            }
        }

        inline void DecreaseItemCount(AFortPlayerControllerAthena* PC, UFortItemDefinition* Item, int Amount)
        {
            auto Inventory = PC->WorldInventory;

            for (int i = 0; i < Inventory->Inventory.ReplicatedEntries.Num(); i++)
            {
                auto ItemDefinition = Inventory->Inventory.ReplicatedEntries[i].ItemDefinition;

                if (Item == ItemDefinition)
                {
                    Inventory->Inventory.ReplicatedEntries[i].Count -= Amount;
                    Inventory->Inventory.ReplicatedEntries[i].ReplicationKey++;

                    Update(PC, 0, true);
                    return;
                }
            }
        }

        inline void IncreaseItemCount(AFortPlayerControllerAthena* PC, UFortItemDefinition* Item, int Amount)
        {
            auto Inventory = PC->WorldInventory;

            for (int i = 0; i < Inventory->Inventory.ReplicatedEntries.Num(); i++)
            {
                auto ItemDefinition = Inventory->Inventory.ReplicatedEntries[i].ItemDefinition;

                if (Item == ItemDefinition)
                {
                    Inventory->Inventory.ReplicatedEntries[i].Count += Amount;
                    Inventory->Inventory.ReplicatedEntries[i].ReplicationKey++;

                    Update(PC, 0, true);
                    return;
                }
            }
        }

        inline int GetItemCount(AFortPlayerControllerAthena* PC, UFortItemDefinition* Item)
        {
            auto Inventory = PC->WorldInventory;

            for (int i = 0; i < Inventory->Inventory.ReplicatedEntries.Num(); i++)
            {
                auto ItemDefinition = Inventory->Inventory.ReplicatedEntries[i].ItemDefinition;

                if (Item == ItemDefinition)
                    return Inventory->Inventory.ReplicatedEntries[i].Count;
            }

            return 0;
        }


        inline bool IsValidGuid(AFortPlayerControllerAthena* Controller, const FGuid& Guid)
        {
            if (!Controller)
                return false;

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

        inline auto GetDefinitionInSlot(AFortPlayerControllerAthena* Controller, int Slot, int Item = 0, EFortQuickBars QuickBars = EFortQuickBars::Primary)
        {

            if (!Controller)
                return FFortItemEntry().ItemDefinition;

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
                    return ItemInstance->ItemEntry.ItemDefinition;
            }

            return FFortItemEntry().ItemDefinition;
        }

        inline FFortItemEntry AddItemToSlot(AFortPlayerControllerAthena* Controller, UFortWorldItemDefinition* Definition, int Slot, EFortQuickBars Bars = EFortQuickBars::Primary, int Count = 1, int* Idx = nullptr)
        {
            if (!Controller || !Definition)
                return FFortItemEntry();

            if (Slot < 0)
                return FFortItemEntry();
            //Slot = 1;

            if (Bars == EFortQuickBars::Primary && Slot >= 6)
                return FFortItemEntry();
            //Slot = 5;

            auto& QuickBarSlots = Controller->QuickBars->PrimaryQuickBar.Slots;

            auto TempItemInstance = (UFortWorldItem*)Definition->CreateTemporaryItemInstanceBP(Count, 1);

            if (TempItemInstance)
            {
                TempItemInstance->SetOwningControllerForTemporaryItem(Controller);

                TempItemInstance->ItemEntry.Count = Count;
                TempItemInstance->OwnerInventory = Controller->WorldInventory;

                auto& ItemEntry = TempItemInstance->ItemEntry;

                auto _Idx = Controller->WorldInventory->Inventory.ReplicatedEntries.Add(ItemEntry);

                if (Idx)
                    *Idx = _Idx;

                Controller->WorldInventory->Inventory.ItemInstances.Add((UFortWorldItem*)TempItemInstance);
                Controller->QuickBars->ServerAddItemInternal(ItemEntry.ItemGuid, Bars, Slot);

                Update(Controller, _Idx);

                return ItemEntry;
            }

            return FFortItemEntry();
        }

        inline bool RemoveItemFromSlot(AFortPlayerControllerAthena* Controller, int Slot, EFortQuickBars Quickbars = EFortQuickBars::Primary, int Amount = -1, bool bUseCustomGuid = false, FGuid CustomGuid = {})
        {
            if (!Controller)
                return false;

            auto& PrimarySlots = Controller->QuickBars->PrimaryQuickBar.Slots;
            auto& SecondarySlots = Controller->QuickBars->SecondaryQuickBar.Slots;

            bool bPrimaryQuickBar = (Quickbars == EFortQuickBars::Primary);

            if (Amount == -1)
            {
                if (bPrimaryQuickBar)
                    Amount = PrimarySlots[Slot].Items.Num();
                else
                    Amount = SecondarySlots[Slot].Items.Num();
            }

            bool bWasSuccessful = false;

            for (int i = 0; i < Amount; i++)
            {
                auto& ToRemoveGuid = bPrimaryQuickBar ? PrimarySlots[Slot].Items[i] : SecondarySlots[Slot].Items[i];
                if (bUseCustomGuid)
                    ToRemoveGuid = CustomGuid;

                for (int j = 0; j < Controller->WorldInventory->Inventory.ItemInstances.Num(); j++)
                {
                    auto ItemInstance = Controller->WorldInventory->Inventory.ItemInstances[j];

                    if (!ItemInstance)
                        continue;

                    auto Guid = ItemInstance->ItemEntry.ItemGuid;

                    if (ToRemoveGuid == Guid)
                    {
                        Controller->WorldInventory->Inventory.ItemInstances.RemoveAt(j);
                        bWasSuccessful = true;
                    }
                }

                for (int x = 0; x < Controller->WorldInventory->Inventory.ReplicatedEntries.Num(); x++)
                {
                    auto& ItemEntry = Controller->WorldInventory->Inventory.ReplicatedEntries[x];

                    if (ItemEntry.ItemGuid == ToRemoveGuid)
                    {
                        Controller->WorldInventory->Inventory.ReplicatedEntries.RemoveAt(x);
                        bWasSuccessful = true;
                    }
                }

                Controller->QuickBars->ServerRemoveItemInternal(ToRemoveGuid, false, true);
                ToRemoveGuid.Reset();
            }

            if (bWasSuccessful)
            {
                Controller->QuickBars->EmptySlot(Quickbars, Slot);

                if (bPrimaryQuickBar)
                    PrimarySlots[Slot].Items.FreeArray();
                else
                    SecondarySlots[Slot].Items.FreeArray();
            }

            Inventory::Update(Controller, 0, true);

            return bWasSuccessful;
        }
        inline void OnDrop(AFortPlayerControllerAthena* Controller, void* params)
        {
            auto Params = (AFortPlayerController_ServerAttemptInventoryDrop_Params*)params;

            if (!Params || !Controller)
                return;

            auto Instance = GetInstanceFromGuid(Controller, Params->ItemGuid);

            if (!Instance)
                return;

            auto Definition = Instance->ItemEntry.ItemDefinition;
            if (!Definition || Definition->IsA(UFortDecoItemDefinition::StaticClass())) return;

            auto QuickBars = Controller->QuickBars;

            auto& PrimaryQuickBarSlots = QuickBars->PrimaryQuickBar.Slots;
            auto& SecondaryQuickBarSlots = QuickBars->SecondaryQuickBar.Slots;

            if (Definition->IsA(UFortWeaponItemDefinition::StaticClass()))
            {
                for (int i = 1; i < PrimaryQuickBarSlots.Num(); i++)
                {
                    if (PrimaryQuickBarSlots[i].Items.Data)
                    {
                        for (int j = 0; j < PrimaryQuickBarSlots[i].Items.Num(); j++)
                        {
                            if (PrimaryQuickBarSlots[i].Items[j] == Params->ItemGuid)
                            {
                                auto SuccessfullyRemoved = RemoveItemFromSlot(Controller, i, EFortQuickBars::Primary, j + 1);

                                if (Definition && SuccessfullyRemoved)
                                {
                                    auto Pickup = SummonPickup((AFortPlayerPawn*)Controller->Pawn, Definition, Instance->ItemEntry.Count, Controller->Pawn->K2_GetActorLocation());
                                    Pickup->Owner = Controller;

                                    auto TestWeapon = ((AFortPlayerPawn*)Controller->Pawn)->EquipWeaponDefinition((UFortWeaponItemDefinition*)Definition, Params->ItemGuid);
                                    Instance->ItemEntry.LoadedAmmo = TestWeapon->AmmoCount;
                                    Pickup->PrimaryPickupItemEntry.LoadedAmmo = Instance->ItemEntry.LoadedAmmo;

                                    if (PrimaryQuickBarSlots[0].Items.Data)
                                        EquipInventoryItem(Controller, PrimaryQuickBarSlots[0].Items[0]);

                                    return;
                                }
                            }
                        }
                    }
                }
            }
            else if (Definition->IsA(UFortAmmoItemDefinition::StaticClass()))
            {
                if (Instance->ItemEntry.Count > 0)
                {
                    Abilities::Inventory::AddItem(Controller, Instance, 0, EFortQuickBars::Secondary, Instance->ItemEntry.Count - Instance->ItemEntry.Count);
                    auto Pickup = SummonPickup((AFortPlayerPawn*)Controller->Pawn, Definition, Instance->ItemEntry.Count, Controller->Pawn->K2_GetActorLocation());
                    Pickup->PrimaryPickupItemEntry.Count = Instance->ItemEntry.Count;
                    Instance->ItemEntry.Count = 0;

                    if (PrimaryQuickBarSlots[0].Items.Data)
                        EquipInventoryItem(Controller, PrimaryQuickBarSlots[0].Items[0]);
                }

                return;
            }
            else if (Definition->IsA(UFortResourceItemDefinition::StaticClass()))
            {
                Instance->ItemEntry.Count = GetItemCount(Controller, Definition);
                if (Instance->ItemEntry.Count > 0)
                {
                    DecreaseItemCount(Controller, Definition, Instance->ItemEntry.Count);
                    auto Pickup = SummonPickup((AFortPlayerPawn*)Controller->Pawn, Definition, Instance->ItemEntry.Count, Controller->Pawn->K2_GetActorLocation());
                    Pickup->PrimaryPickupItemEntry.Count = Instance->ItemEntry.Count;
                    Instance->ItemEntry.Count = 0;

                    if (PrimaryQuickBarSlots[0].Items.Data)
                        EquipInventoryItem(Controller, PrimaryQuickBarSlots[0].Items[0]);
                }

                return;
            }


            return;
        }


        inline void OnPickup(AFortPlayerControllerAthena* Controller, void* params)
        {
            auto Params = (AFortPlayerPawn_ServerHandlePickup_Params*)params;

            if (!Controller || !Params)
                return;

            auto& ItemInstances = Controller->WorldInventory->Inventory.ItemInstances;

            if (Params->Pickup)
            {
                auto WorldItemDefinition = (UFortWorldItemDefinition*)Params->Pickup->PrimaryPickupItemEntry.ItemDefinition;

                if (Params->Pickup->PrimaryPickupItemEntry.ItemDefinition->IsA(UFortWeaponItemDefinition::StaticClass()))
                {
                    auto& PrimaryQuickBarSlots = Controller->QuickBars->PrimaryQuickBar.Slots;

                    for (int i = 1; i < PrimaryQuickBarSlots.Num(); i++)
                    {
                        if (!PrimaryQuickBarSlots[i].Items.Data) //Empty Slot
                        {
                            if (Params->Pickup->IsActorBeingDestroyed() || Params->Pickup->bPickedUp)
                                return;

                            //All slots are full so we gonna remove the focused slot to place our weapon
                            if (i >= 6)
                            {
                                auto QuickBars = Controller->QuickBars;

                                auto FocusedSlot = QuickBars->PrimaryQuickBar.CurrentFocusedSlot;

                                if (FocusedSlot == 0)
                                    continue;

                                i = FocusedSlot;

                                FGuid& FocusedGuid = PrimaryQuickBarSlots[FocusedSlot].Items[0];

                                for (int j = 0; j < ItemInstances.Num(); j++)
                                {
                                    auto ItemInstance = ItemInstances[j];

                                    if (!ItemInstance)
                                        continue;

                                    auto Def = ItemInstance->ItemEntry.ItemDefinition;
                                    auto Guid = ItemInstance->ItemEntry.ItemGuid;

                                    if (FocusedGuid == Guid)
                                    {
                                        auto Pickup = SummonPickup((AFortPlayerPawn*)Controller->Pawn, Def, ItemInstance->ItemEntry.Count, Controller->Pawn->K2_GetActorLocation()); //Drop the weapon to replace
                                        Pickup->Owner = Controller;

                                        auto TestWeapon = ((AFortPlayerPawn*)Controller->Pawn)->EquipWeaponDefinition((UFortWeaponItemDefinition*)Def, Guid);
                                        ItemInstance->ItemEntry.LoadedAmmo = TestWeapon->AmmoCount;
                                        Pickup->PrimaryPickupItemEntry.LoadedAmmo = ItemInstance->ItemEntry.LoadedAmmo;

                                        RemoveItemFromSlot(Controller, FocusedSlot, EFortQuickBars::Primary);
                                        break;
                                    }
                                }

                            }

                            int Idx = 0;
                            auto entry = AddItemToSlot(Controller, WorldItemDefinition, i, EFortQuickBars::Primary, Params->Pickup->PrimaryPickupItemEntry.Count, &Idx);
                            auto Instance = GetInstanceFromGuid(Controller, entry.ItemGuid);

                            Params->Pickup->bPickedUp = true;
                            Params->Pickup->OnRep_bPickedUp();

                            if (!Params->Pickup->Owner)
                            {
                                auto TestWeapon = EquipWeaponDefinition(Controller->Pawn, (UFortWeaponItemDefinition*)Params->Pickup->PrimaryPickupItemEntry.ItemDefinition, entry.ItemGuid, -1, true);
                                if (TestWeapon)
                                    Params->Pickup->PrimaryPickupItemEntry.LoadedAmmo = TestWeapon->AmmoCount;
                            }

                            Params->Pickup->Owner = Controller;
                            Instance->ItemEntry.LoadedAmmo = Params->Pickup->PrimaryPickupItemEntry.LoadedAmmo;

                            Params->Pickup->K2_DestroyActor();

                            Update(Controller);

                            return;
                        }
                    }
                }
                else if (Params->Pickup->PrimaryPickupItemEntry.ItemDefinition->IsA(UFortAmmoItemDefinition::StaticClass()))
                {
                    for (int j = 0; j < ItemInstances.Num(); j++)
                    {
                        auto ItemInstance = ItemInstances[j];
                        if (!ItemInstance) continue;

                        if (ItemInstance->ItemEntry.ItemDefinition == WorldItemDefinition)
                        {
                            // Add the item without making a new instance
                            AddItem(Controller, ItemInstance, 0, EFortQuickBars::Secondary, ItemInstance->ItemEntry.Count + Params->Pickup->PrimaryPickupItemEntry.Count);
                            Params->Pickup->bPickedUp = true;
                            Params->Pickup->OnRep_bPickedUp();
                            Params->Pickup->K2_DestroyActor();
                            Update(Controller);
                            return;
                        }
                    }
                }
                else if (Params->Pickup->PrimaryPickupItemEntry.ItemDefinition->IsA(UFortResourceItemDefinition::StaticClass()))
                {
                    for (int j = 0; j < ItemInstances.Num(); j++)
                    {
                        auto ItemInstance = ItemInstances[j];
                        if (!ItemInstance) continue;

                        if (ItemInstance->ItemEntry.ItemDefinition == WorldItemDefinition)
                        {
                            IncreaseItemCount(Controller, WorldItemDefinition, ItemInstance->ItemEntry.Count + Params->Pickup->PrimaryPickupItemEntry.Count);
                            Params->Pickup->bPickedUp = true;
                            Params->Pickup->OnRep_bPickedUp();
                            Params->Pickup->K2_DestroyActor();
                            Update(Controller);
                            return;
                        }
                    }
                }
            }
        }
        void Initialize()
        {
            HandlePEFunction("Function FortniteGame.FortPlayerPawn.ServerHandlePickup", {
                OnPickup((AFortPlayerControllerAthena*)((APawn*)Object)->Controller, Parameters);
                return false;
                });
            HandlePEFunction("Function FortniteGame.FortPlayerController.ServerAttemptInventoryDrop", {
                auto PC = (AFortPlayerControllerAthena*)Object;

                if (PC && !PC->IsInAircraft())
                    OnDrop(PC, Parameters);

                return false;
                });

            HandlePEFunction("Function FortniteGame.FortPlayerController.ServerExecuteInventoryItem", {
                EquipInventoryItem((AFortPlayerControllerAthena*)Object, *(FGuid*)Parameters);

                return false;
                });

        }
    }
}
