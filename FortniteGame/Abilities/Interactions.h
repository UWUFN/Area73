#pragma once

namespace Abilities
{
	namespace Interactions
	{
		void Initialize()
		{
            HandlePEFunction("Function FortniteGame.FortPlayerController.ServerAttemptInteract", {
                auto Params = (AFortPlayerController_ServerAttemptInteract_Params*)Parameters;
                auto PC = (AFortPlayerControllerAthena*)Object;
                
                if (Params->ReceivingActor)
                {
                    if (Params->ReceivingActor->IsA(APlayerPawn_Athena_C::StaticClass()))
                    {
                        auto DBNOPawn = (APlayerPawn_Athena_C*)Params->ReceivingActor;
                        auto DBNOPC = (AFortPlayerControllerAthena*)DBNOPawn->Controller;

                        if (DBNOPawn && DBNOPC)
                        {
                            DBNOPawn->ReviveFromDBNO(PC);
                        }
                    }
                    else if (Params->ReceivingActor->IsA(ABuildingContainer::StaticClass()))
                    {
                        auto Container = (ABuildingContainer*)Params->ReceivingActor;
                        auto ContainerName = Container->GetFullName();
                        
                        Container->bAlreadySearched = true;
                        Container->OnRep_bAlreadySearched();
                        
                        auto Location = Container->K2_GetActorLocation();

                        if (strstr(ContainerName.c_str(), "Chest"))
                        {
                            std::cout << "Player opened a chest" << "\n";

                            auto Weapon = ItemDefinitions::GetWeapon(true);
                            SummonPickupFromChest(Weapon, 1, FVector(Location.X, Location.Y, Location.Z + 50));

                            int Ammo_Count = 0;
                            auto Ammo = ItemDefinitions::GetAmmoOfWeapon(Weapon, &Ammo_Count);
                            SummonPickupFromChest(Ammo, Ammo_Count, FVector(Location.X, Location.Y, Location.Z + 50));

                            int Consumable_Count = 0;
                            auto Consumable = ItemDefinitions::GetConsumable(true, &Consumable_Count);
                            SummonPickupFromChest(Consumable, Consumable_Count, FVector(Location.X, Location.Y, Location.Z + 50));

                            SummonPickupFromChest(ItemDefinitions::GetMaterial(true), 30, FVector(Location.X, Location.Y, Location.Z + 50));

                            auto rand_trap_spawn = rand() % 3 + 1;
                            if(rand_trap_spawn == 2)
                                SummonPickupFromChest(ItemDefinitions::GetTrap(true), 1, FVector(Location.X, Location.Y, Location.Z + 50));
                        }

                        if (strstr(ContainerName.c_str(), "Ammo"))
                        {
                            std::cout << "Player opened an ammobox" << "\n";

                            int Ammo_Count1 = 0;
                            auto Ammo1 = ItemDefinitions::GetAmmo(true, &Ammo_Count1);
                            SummonPickupFromChest(Ammo1, Ammo_Count1, FVector(Location.X, Location.Y, Location.Z + 50));

                            int Ammo_Count2 = 0;
                            auto Ammo2 = ItemDefinitions::GetAmmo(true, &Ammo_Count2);
                            SummonPickupFromChest(Ammo2, Ammo_Count2, FVector(Location.X, Location.Y, Location.Z + 50));

                            /*
                            auto LaunchPad = UObject::FindObject<UFortTrapItemDefinition>("FortTrapItemDefinition TID_Floor_Player_Launch_Pad_Athena.TID_Floor_Player_Launch_Pad_Athena");
                            SummonPickupFromChest(LaunchPad, 1, FVector(Location.X, Location.Y, Location.Z + 50));


                            auto Campfire = UObject::FindObject<UFortTrapItemDefinition>("FortTrapItemDefinition TID_Floor_Campfire_R_T04.TID_Floor_Campfire_R_T04");
                            if(Campfire)
                                SummonPickupFromChest(Campfire, 1, FVector(Location.X, Location.Y, Location.Z + 50));

                            auto Trap = UObject::FindObject<UFortTrapItemDefinition>("FortTrapItemDefinition TID_Floor_Spikes_Athena_R_T03.TID_Floor_Spikes_Athena_R_T03");
                            if (Trap)
                                SummonPickupFromChest(Trap, 1, FVector(Location.X, Location.Y, Location.Z + 50));

                            Trap = UObject::FindObject<UFortTrapItemDefinition>("FortTrapItemDefinition TID_Wall_Spikes_Athena_R_T03.TID_Wall_Spikes_Athena_R_T03");
                            if (Trap)
                                SummonPickupFromChest(Trap, 1, FVector(Location.X, Location.Y, Location.Z + 50));

                            Trap = UObject::FindObject<UFortTrapItemDefinition>("FortTrapItemDefinition TID_Ceiling_Spikes_Athena_R_T03.TID_Ceiling_Spikes_Athena_R_T03");
                            if (Trap)
                                SummonPickupFromChest(Trap, 1, FVector(Location.X, Location.Y, Location.Z + 50));
                                */
                        }


                        //TODO: spawn pickup
                        //SummonPickupFromChest(FindWID("WID_Assault_AutoHigh_Athena_SR_Ore_T03"), 1, FVector(Location.X, Location.Y, Location.Z + 50));


                    }
                }

                return false;
            });
		}
	}
}