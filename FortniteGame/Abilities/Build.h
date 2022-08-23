#pragma once

namespace Abilities
{
	namespace Build
	{

		void Initialize()
		{
            
            HandlePEFunction("Function FortniteGame.FortPlayerController.ServerCreateBuildingActor", {
                auto PC = (AFortPlayerControllerAthena*)Object;

                auto Params = (AFortPlayerController_ServerCreateBuildingActor_Params*)Parameters;
                auto CurrentBuildClass = Params->BuildingClassData.BuildingClass;

                static auto GameState = reinterpret_cast<AFortGameStateAthena*>(GetWorld()->GameState);

                if (PC && Params && CurrentBuildClass)
                {
                    {
                        auto BuildingActor = (ABuildingSMActor*)SpawnActorByClass(CurrentBuildClass, Params->BuildLoc, Params->BuildRot, PC, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
                        
                        TArray<ABuildingActor*> ExistingBuildings;
                        EFortStructuralGridQueryResults bCanBuild = GameState->StructuralSupportSystem->K2_CanAddBuildingActorToGrid(GetWorld(), BuildingActor, BuildingActor->K2_GetActorLocation(), BuildingActor->K2_GetActorRotation(), false, false, &ExistingBuildings, 0);

                        if (BuildingActor && bCanBuild == EFortStructuralGridQueryResults::CanAdd || ExistingBuildings.Num() == 0)
                        {
                            BuildingActor->DynamicBuildingPlacementType = EDynamicBuildingPlacementType::DestroyAnythingThatCollides;
                            BuildingActor->SetMirrored(Params->bMirrored);
                            BuildingActor->InitializeKismetSpawnedBuildingActor(BuildingActor, PC);
                            Inventory::RemoveBuildingMaterials(PC, CurrentBuildClass);
                            auto PlayerState = (AFortPlayerStateAthena*)PC->PlayerState;
                            BuildingActor->Team = PlayerState->TeamIndex; //set team for build
                        }
                        else
                        {
                            BuildingActor->SetActorScale3D({});
                            BuildingActor->SilentDie();
                        }
                    }
                }

                return false;
            });
            
            HandlePEFunction("Function FortniteGame.FortPlayerController.ServerRepairBuildingActor", {
                auto Params = (AFortPlayerController_ServerRepairBuildingActor_Params*)Parameters;
                auto Controller = (AFortPlayerControllerAthena*)Object;
                auto Pawn = (APlayerPawn_Athena_C*)Controller->Pawn;

                if (Controller && Pawn && Params->BuildingActorToRepair)
                {
                    Params->BuildingActorToRepair->RepairBuilding(Controller, 10); //10 non è corretto prob
                }

                return false;
            });
		}
	}
}