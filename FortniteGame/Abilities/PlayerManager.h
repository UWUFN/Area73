#pragma once
inline UKismetMathLibrary* GetMath()
{
    return (UKismetMathLibrary*)UKismetMathLibrary::StaticClass();
}

namespace Abilities
{
    namespace PlayerManager
    {
        void Spectate(UNetConnection* SpectatingConnection, AFortPlayerStateAthena* StateToSpectate)
        {
            /*
            if (!SpectatingConnection || !StateToSpectate)
                return;

            auto PawnToSpectate = StateToSpectate->GetCurrentPawn();
            auto DeadPC = (AFortPlayerControllerAthena*)SpectatingConnection->PlayerController;

            if (!DeadPC)
                return;

            auto DeadPlayerState = (AFortPlayerStateAthena*)DeadPC->PlayerState;

            if (DeadPlayerState && PawnToSpectate)
            {
                DeadPC->PlayerToSpectateOnDeath = PawnToSpectate;
                DeadPC->ClientSetSpectatorCamera(PawnToSpectate->K2_GetActorLocation(), PawnToSpectate->K2_GetActorRotation());
                DeadPC->SpectateOnDeath();

                DeadPlayerState->SpectatingTarget = StateToSpectate;
                DeadPlayerState->bIsSpectator = true;
                DeadPlayerState->OnRep_SpectatingTarget();

                auto SpectatorPC = SpawnActor<ABP_SpectatorPC_C>(PawnToSpectate->K2_GetActorLocation());
                SpectatorPC->SetNewCameraType(ESpectatorCameraType::Gameplay, true);
                //SpectatorPC->CurrentCameraType = ESpectatorCameraType::Gameplay;
                SpectatorPC->ResetCamera();
                SpectatingConnection->PlayerController = SpectatorPC;
                SpectatingConnection->ViewTarget = PawnToSpectate;
                SpectatorPC->FollowedPlayerPrivate = StateToSpectate;
                SpectatorPC->HoveredPlayerPrivate = StateToSpectate;
                SpectatorPC->ToggleSpectatorHUD();

                if (SpectatorPC->CurrentSpectatorCamComp)
                    SpectatorPC->CurrentSpectatorCamComp->IntendedViewTarget = PawnToSpectate;

                auto SpectatorPawn = SpawnActor<AArenaCamPawn>(PawnToSpectate->K2_GetActorLocation(), PawnToSpectate);

                SpectatorPawn->SpectatorController = SpectatorPC;

                if (SpectatorPawn->SpectatorCameraComponent)
                    SpectatorPawn->SpectatorCameraComponent->IntendedViewTarget = PawnToSpectate;

                SpectatorPC->SpectatorPawn = SpectatorPawn;
                SpectatorPC->Pawn = SpectatorPawn;
                SpectatorPC->AcknowledgedPawn = SpectatorPawn;
                SpectatorPawn->Owner = SpectatorPC;
                SpectatorPawn->OnRep_Owner();
                SpectatorPC->OnRep_Pawn();
                SpectatorPC->Possess(SpectatorPawn);
                DeadPC->K2_DestroyActor();

                SpectatorPC->Pawn->bUseControllerRotationPitch = true;
                SpectatorPC->Pawn->bUseControllerRotationYaw = true;
                SpectatorPC->Pawn->bUseControllerRotationRoll = true;

                if (DeadPC->QuickBars)
                    DeadPC->QuickBars->K2_DestroyActor();
            }
            */
        }

        void Initialize()
        {




            HandlePEFunction("Function FortniteGame.FortPlayerController.ServerLoadingScreenDropped", {
                auto Pawn = (APlayerPawn_Athena_C*)((AFortPlayerController*)Object)->Pawn;

            //Pawn->PlayerState->SavedNetworkAddress
            /*
            {
                KickController((APlayerController*)Pawn->Controller, L"Sei bannato bozo haha");
                return false;
            }*/

            if (Pawn)
            {
                Pawn->bCanBeDamaged = false;
                //Pawn->bGodMode = true;

                if (Pawn->AbilitySystemComponent)
                    ApplyAbilities(Pawn);
            }

            return false;
                });


            HandlePEFunction("Function FortniteGame.FortPlayerPawn.ServerChoosePart", {
                return false;
                });

            
                        
            HandlePEFunction("Function FortniteGame.FortPlayerControllerZone.ClientOnPawnDied", {
                auto Params = (AFortPlayerControllerZone_ClientOnPawnDied_Params*)Parameters;
                auto DeathReport = Params->DeathReport;
                auto DeadPC = (AFortPlayerControllerAthena*)Object;
                auto DeadPawn = (APlayerPawn_Athena_C*)DeadPC->Pawn;
                auto DeadPawnLocation = DeadPawn->K2_GetActorLocation();
                auto DeadPlayerState = (AFortPlayerStateAthena*)DeadPC->PlayerState;
                auto GameMode = (AFortGameModeAthena*)GetWorld()->AuthorityGameMode;
                auto GameState = (AFortGameStateAthena*)GameMode->GameState;

                if (DeadPC && DeadPawn)
                {
                    auto KillerPlayerState = (AFortPlayerStateAthena*)DeathReport.KillerPlayerState;
                    auto KillerPawn = (APlayerPawn_Athena_C*)DeathReport.KillerPawn;

                    if (!bRespawn)
                    {
                        GameState->PlayersLeft--;
                        GameState->OnRep_PlayersLeft();
                        GameState->PlayerArray.RemoveSingle(DeadPC->NetPlayerIndex);
                    }

                    SpawnActor<ABP_VictoryDrone_C>(FVector(DeadPawnLocation.X, DeadPawnLocation.Y, DeadPawnLocation.Z - 60));//->PlaySpawnOutAnim();

                    FDeathInfo DeathInfo;
                    DeathInfo.bDBNO = false;
                    DeathInfo.DeathLocation = DeadPawnLocation;

                    if (KillerPawn && KillerPlayerState)
                    {
                        DeathInfo.Distance = KillerPawn->GetDistanceTo(DeadPC->Pawn);
                        DeathInfo.DeathCause = EDeathCause::Sniper; // TODO: Determine death cause
                        DeathInfo.FinisherOrDowner = KillerPlayerState;

                        KillerPlayerState->ClientReportKill(DeadPlayerState);

                        DeadPlayerState->DeathInfo = DeathInfo;
                        DeadPlayerState->OnRep_DeathInfo();

                        if (KillerPawn != DeadPawn)
                        {
                            ((AFortPlayerControllerPvP*)KillerPawn->Controller)->ClientReceiveKillNotification(KillerPlayerState, DeadPlayerState);

                            KillerPlayerState->KillScore++;
                            KillerPlayerState->TeamKillScore++;
                            KillerPlayerState->OnRep_Kills();
                        }

                        if (!bRespawn)
                        {
                            DeadPawn->K2_DestroyActor();
                            Spectate(DeadPC->NetConnection, KillerPlayerState);
                        }
                    }
                    else
                    {
                        DeathInfo.Distance = 100;
                        DeathInfo.DeathCause = EDeathCause::FallDamage;
                        DeathInfo.FinisherOrDowner = DeadPlayerState;

                        DeadPlayerState->ClientReportKill(DeadPlayerState);

                        DeadPlayerState->DeathInfo = DeathInfo;
                        DeadPlayerState->OnRep_DeathInfo();

                        ((AFortPlayerControllerPvP*)DeadPawn->Controller)->ClientReceiveKillNotification(DeadPlayerState, DeadPlayerState);

                        if (!bRespawn)
                        {
                            DeadPawn->K2_DestroyActor();

                            if (GameState->PlayersLeft > 0)
                            {
                                TArray<AActor*> Pawns;
                                static auto GameplayStatics = (UGameplayStatics*)UGameplayStatics::StaticClass()->CreateDefaultObject();
                                GameplayStatics->STATIC_GetAllActorsOfClass(GetWorld(), APlayerPawn_Athena_C::StaticClass(), &Pawns);
                                auto RandomPawn = (AFortPlayerPawnAthena*)Pawns[rand() % Pawns.Num()];
                                if (RandomPawn)
                                    Spectate(DeadPC->NetConnection, (AFortPlayerStateAthena*)RandomPawn->Controller->PlayerState);
                            }
                        }
                    }

                    if (!bRespawn && GameState->PlayersLeft == 1)
                    {
                        TArray<AActor*> Pawns;
                        static auto GameplayStatics = (UGameplayStatics*)UGameplayStatics::StaticClass()->CreateDefaultObject();
                        GameplayStatics->STATIC_GetAllActorsOfClass(GetWorld(), APlayerPawn_Athena_C::StaticClass(), &Pawns);
                        auto WinnerPawn = (AFortPlayerPawnAthena*)Pawns[0];
                        if (WinnerPawn)
                        {
                            auto WinnerPC = (AFortPlayerControllerAthena*)WinnerPawn->Controller;
                            auto WinnerState = (AFortPlayerStateAthena*)WinnerPC->PlayerState;
                            if (!WinnerPC->IsClientNotifiedOfWin())
                            {
                                //GameState->WinningPlayerName = WinnerState->PlayerName;
                                //GameState->OnRep_WinningPlayerName();
                                GameMode->ReadyToEndMatch();
                                GameMode->EndMatch();

                                WinnerPC->ClientNotifyWon(WinnerPawn, WinnerPawn->CurrentWeapon ? WinnerPawn->CurrentWeapon->WeaponData : (UFortWeaponItemDefinition*)ItemDefinitions::GetWeapon(false, ItemDefinitions::WeaponItemDefinitionNames::BoltAction_Blue), EDeathCause::Sniper);
                                WinnerPC->ClientNotifyTeamWon(WinnerPawn, WinnerPawn->CurrentWeapon ? WinnerPawn->CurrentWeapon->WeaponData : (UFortWeaponItemDefinition*)ItemDefinitions::GetWeapon(false, ItemDefinitions::WeaponItemDefinitionNames::BoltAction_Blue), EDeathCause::Sniper);
                                WinnerPC->PlayWinEffects(WinnerPawn, WinnerPawn->CurrentWeapon ? WinnerPawn->CurrentWeapon->WeaponData : (UFortWeaponItemDefinition*)ItemDefinitions::GetWeapon(false, ItemDefinitions::WeaponItemDefinitionNames::BoltAction_Blue), EDeathCause::Sniper);
                                WinnerPC->bClientNotifiedOfWin = true;
                                WinnerPC->bClientNotifiedOfTeamWin = true;
                                WinnerState->bHasWonAGame = true;
                                WinnerPC->ClientGameEnded(WinnerPawn, true);
                            }
                        }
                    }




                    //RESPAWN
                    if (bRespawn)
                    {
                        auto RespawnedPawn = InitializePawnNOCP(DeadPC, FVector(DeadPawnLocation.X, DeadPawnLocation.Y, DeadPawnLocation.Z + 2000), {}, true);

                        auto& HealthSet = RespawnedPawn->HealthSet;
                        HealthSet->CurrentShield.CurrentValue = 100;
                        DeadPlayerState->CurrentShield = 100;
                        HealthSet->OnRep_CurrentShield();


                        Inventory::Update(DeadPC);
                        ApplyAbilities(RespawnedPawn);

                        DeadPC->ActivateSlot(EFortQuickBars::Primary, 0, 0, true); // Select the pickaxe

                        bool bFound = false;
                        auto PickaxeEntry = FindItemInInventory<UFortWeaponMeleeItemDefinition>(DeadPC, bFound);

                        if (bFound)
                            EquipInventoryItem(DeadPC, PickaxeEntry.ItemGuid);

                        DeadPC->RespawnPlayerAfterDeath();

                        auto CM = CreateCheatManager(DeadPC);
                        CM->RespawnPlayer();
                        CM->RespawnPlayerServer();

                        /*
                        if (KillerPlayerState)
                        {
                            KillerPlayerState->KillScore++;
                            KillerPlayerState->OnRep_Kills();
                        }
                        */
                    }


                }

                return false;
                });

            HandlePEFunction("Function FortniteGame.FortPlayerPawn.ServerReviveFromDBNO", {
                auto Params = (AFortPlayerPawn_ServerReviveFromDBNO_Params*)Parameters;
                auto DBNOPawn = (APlayerPawn_Athena_C*)Object;
                auto DBNOPC = (AFortPlayerControllerAthena*)DBNOPawn->Controller;
                auto InstigatorPC = (AFortPlayerControllerAthena*)Params->EventInstigator;

                if (InstigatorPC && DBNOPawn && DBNOPC)
                {
                    DBNOPawn->bIsDBNO = false;
                    DBNOPawn->OnRep_IsDBNO();

                    DBNOPC->ClientOnPawnRevived(InstigatorPC);
                    DBNOPawn->SetHealth(/*30*/200);
                }

                return false;
            });
            HandlePEFunction("Function FortniteGame.FortPlayerController.ServerReturnToMainMenu", {
                ((AFortPlayerController*)Object)->ClientTravel(L"Frontend", ETravelType::TRAVEL_Absolute, false, FGuid());

                return false;
            });
            }
        }
    }