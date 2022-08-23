#pragma once

namespace Abilities
{
	namespace Aircraft
	{
		void Initialize()
		{
            HandlePEFunction("Function FortniteGame.FortPlayerControllerAthena.ServerAttemptAircraftJump", {
                auto Params = (AFortPlayerControllerAthena_ServerAttemptAircraftJump_Params*)Parameters;
                auto PC = (AFortPlayerControllerAthena*)Object;
                auto GameState = (AFortGameStateAthena*)GetWorld()->AuthorityGameMode->GameState;

                if (PC && Params && !PC->Pawn && PC->IsInAircraft())
                {
                    auto Aircraft = (AFortAthenaAircraft*)GameState->Aircrafts[0];

                    if (Aircraft)
                    {
                        auto ExitLocation = Aircraft->K2_GetActorLocation();

                        if (PC->Pawn)
                            PC->Pawn->K2_DestroyActor();

                        //auto ExitRotation = PC->GetControlRotation();
                        InitializePawnNOCP(PC, ExitLocation/*, RotToQuat(ExitRotation)*/);

                        Inventory::Update(PC);
                        ApplyAbilities(PC->Pawn);

                        GameState->Aircrafts[0]->PlayEffectsForPlayerJumped();
                        PC->ActivateSlot(EFortQuickBars::Primary, 0, 0, true); // Select the pickaxe

                        bool bFound = false;
                        auto PickaxeEntry = FindItemInInventory<UFortWeaponMeleeItemDefinition>(PC, bFound);

                        if (bFound)
                            EquipInventoryItem(PC, PickaxeEntry.ItemGuid);
                    }
                }

                return false;
            });

            HandlePEFunction("Function FortniteGame.FortGameModeAthena.OnAircraftExitedDropZone", {

                if (GetWorld() && GetWorld()->NetDriver && GetWorld()->NetDriver->ClientConnections.Data)
                {
                    auto Connections = GetWorld()->NetDriver->ClientConnections;//HostBeacon->NetDriver->ClientConnections;

                    for (int i = 0; i < Connections.Num(); i++)
                    {
                        auto Controller = (AFortPlayerControllerAthena*)Connections[i]->PlayerController;

                        if (!Controller || !Controller->IsA(AFortPlayerControllerAthena::StaticClass()) || Controller->PlayerState->bIsSpectator)
                            continue;

                        if (Controller && Controller->IsInAircraft())
                            Controller->ServerAttemptAircraftJump(FRotator());
                    }
                }

                return false;
            });
		}
	}
}