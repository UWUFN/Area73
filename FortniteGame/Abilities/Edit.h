#pragma once

namespace Abilities
{
	namespace Edit
	{
		void Initialize()
		{
            HandlePEFunction("Function FortniteGame.FortPlayerController.ServerBeginEditingBuildingActor", {
                auto Params = (AFortPlayerController_ServerBeginEditingBuildingActor_Params*)Parameters;
                auto Controller = (AFortPlayerControllerAthena*)Object;
                auto Pawn = (APlayerPawn_Athena_C*)Controller->Pawn;
                bool bFound = false;
                auto EditToolEntry = FindItemInInventory<UFortEditToolItemDefinition>(Controller, bFound);

                if (Controller && Pawn && Params->BuildingActorToEdit && bFound)
                {
                    auto EditTool = (AFortWeap_EditingTool*)EquipWeaponDefinition(Pawn, (UFortWeaponItemDefinition*)EditToolEntry.ItemDefinition, EditToolEntry.ItemGuid);

                    if (EditTool)
                    {
                        EditTool->EditActor = Params->BuildingActorToEdit;
                        EditTool->OnRep_EditActor();
                        Params->BuildingActorToEdit->EditingPlayer = (AFortPlayerStateZone*)Pawn->PlayerState;
                        Params->BuildingActorToEdit->OnRep_EditingPlayer();
                    }
                }

                return false;
            });

            HandlePEFunction("Function FortniteGame.FortPlayerController.ServerEditBuildingActor", {
                auto Params = (AFortPlayerController_ServerEditBuildingActor_Params*)Parameters;
                auto PC = (AFortPlayerControllerAthena*)Object;

                if (PC && Params)
                {
                    auto BuildingActor = Params->BuildingActorToEdit;
                    auto NewBuildingClass = Params->NewBuildingClass;
                    auto RotIterations = Params->RotationIterations;

                    if (BuildingActor && NewBuildingClass)
                    {
                        auto location = BuildingActor->K2_GetActorLocation();
                        auto rotation = BuildingActor->K2_GetActorRotation();

                        if (BuildingActor->BuildingType != EFortBuildingType::Wall)
                        {
                            int Yaw = (int(rotation.Yaw) + 360) % 360;

                            if (Yaw > 80 && Yaw < 100) // 90
                            {
                                if (RotIterations == 1)
                                    location = location + FVector(-256, 256, 0);
                                else if (RotIterations == 2)
                                    location = location + FVector(-512, 0, 0);
                                else if (RotIterations == 3)
                                    location = location + FVector(-256, -256, 0);
                            }
                            else if (Yaw > 170 && Yaw < 190) // 180
                            {
                                if (RotIterations == 1)
                                    location = location + FVector(-256, -256, 0);
                                else if (RotIterations == 2)
                                    location = location + FVector(0, -512, 0);
                                else if (RotIterations == 3)
                                    location = location + FVector(256, -256, 0);
                            }
                            else if (Yaw > 260 && Yaw < 280) // 270
                            {
                                if (RotIterations == 1)
                                    location = location + FVector(256, -256, 0);
                                else if (RotIterations == 2)
                                    location = location + FVector(512, 0, 0);
                                else if (RotIterations == 3)
                                    location = location + FVector(256, 256, 0);
                            }
                            else // 0 - 360
                            {
                                if (RotIterations == 1)
                                    location = location + FVector(256, 256, 0);
                                else if (RotIterations == 2)
                                    location = location + FVector(0, 512, 0);
                                else if (RotIterations == 3)
                                    location = location + FVector(-256, 256, 0);
                            }
                        }

                        rotation.Yaw += 90 * RotIterations;

                        auto bWasInitiallyBuilding = BuildingActor->bIsInitiallyBuilding;
                        auto HealthPercent = BuildingActor->GetHealthPercent();
                        auto old_Team = BuildingActor->Team;

                        BuildingActor->SilentDie();

                        if (auto NewBuildingActor = (ABuildingSMActor*)SpawnActorByClass(NewBuildingClass, location, rotation, PC))
                        {
                            if(!bWasInitiallyBuilding)
                                NewBuildingActor->ForceBuildingHealth(NewBuildingActor->GetMaxHealth() * HealthPercent);

                            NewBuildingActor->SetMirrored(Params->bMirrored);
                            NewBuildingActor->InitializeKismetSpawnedBuildingActor(NewBuildingActor, PC);
                            NewBuildingActor->Team = old_Team; //set team for build
                        }
                    }
                }

                return false;
            });

            HandlePEFunction("Function FortniteGame.FortPlayerController.ServerEndEditingBuildingActor", {
                auto Params = (AFortPlayerController_ServerEndEditingBuildingActor_Params*)Parameters;
                auto PC = (AFortPlayerControllerAthena*)Object;

                if (!PC->IsInAircraft() && Params->BuildingActorToStopEditing)
                {
                    Params->BuildingActorToStopEditing->EditingPlayer = nullptr;
                    Params->BuildingActorToStopEditing->OnRep_EditingPlayer();

                    auto EditTool = (AFortWeap_EditingTool*)((APlayerPawn_Athena_C*)PC->Pawn)->CurrentWeapon;

                    if (EditTool)
                    {
                        EditTool->bEditConfirmed = true;
                        EditTool->EditActor = nullptr;
                        EditTool->OnRep_EditActor();
                    }
                }

                return false;
            })
		}
	}
}