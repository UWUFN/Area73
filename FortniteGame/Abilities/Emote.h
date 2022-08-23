#pragma once

namespace Abilities
{
	namespace Emote
	{
		void Initialize()
		{
            HandlePEFunction("Function FortniteGame.FortPlayerController.ServerPlayEmoteItem", {
                if (!Object->IsA(AFortPlayerControllerAthena::StaticClass()))
                    return false;

                auto CurrentPC = (AFortPlayerControllerAthena*)Object;
                auto CurrentPawn = (APlayerPawn_Athena_C*)CurrentPC->Pawn;

                auto EmoteParams = (AFortPlayerController_ServerPlayEmoteItem_Params*)Parameters;
                auto AnimInstance = (UFortAnimInstance*)CurrentPawn->Mesh->GetAnimInstance();

                if (CurrentPC && !CurrentPC->IsInAircraft() && CurrentPawn && EmoteParams->EmoteAsset && AnimInstance && !AnimInstance->bIsJumping && !AnimInstance->bIsFalling)
                {
                    if (EmoteParams->EmoteAsset->IsA(UAthenaDanceItemDefinition::StaticClass()))
                    {
                        if (auto Montage = EmoteParams->EmoteAsset->GetAnimationHardReference(CurrentPawn->CharacterBodyType, CurrentPawn->CharacterGender))
                        {
                            auto& RepAnimMontageInfo = CurrentPawn->RepAnimMontageInfo;
                            auto& ReplayRepAnimMontageInfo = CurrentPawn->ReplayRepAnimMontageInfo;
                            auto& RepCharPartAnimMontageInfo = CurrentPawn->RepCharPartAnimMontageInfo;
                            auto& LocalAnimMontageInfo = CurrentPawn->AbilitySystemComponent->LocalAnimMontageInfo;
                            auto Ability = CurrentPawn->AbilitySystemComponent->AllReplicatedInstancedAbilities[0];

                            const auto Duration = AnimInstance->Montage_Play(Montage, 1.0f, EMontagePlayReturnType::Duration, 0.0f, true);

                            if (Duration > 0.f)
                            {
                                ReplayRepAnimMontageInfo.AnimMontage = Montage;
                                LocalAnimMontageInfo.AnimMontage = Montage;
                                if (Ability)
                                {
                                    LocalAnimMontageInfo.AnimatingAbility = Ability;
                                }
                                LocalAnimMontageInfo.PlayBit = 1;

                                RepAnimMontageInfo.AnimMontage = Montage;
                                RepAnimMontageInfo.ForcePlayBit = 1;

                                RepCharPartAnimMontageInfo.PawnMontage = Montage;

                                if (Ability)
                                {
                                    Ability->CurrentMontage = Montage;
                                }

                                bool bIsStopped = AnimInstance->Montage_GetIsStopped(Montage);

                                if (!bIsStopped)
                                {
                                    RepAnimMontageInfo.PlayRate = AnimInstance->Montage_GetPlayRate(Montage);
                                    RepAnimMontageInfo.Position = AnimInstance->Montage_GetPosition(Montage);
                                    RepAnimMontageInfo.BlendTime = AnimInstance->Montage_GetBlendTime(Montage);
                                }

                                RepAnimMontageInfo.IsStopped = bIsStopped;
                                RepAnimMontageInfo.NextSectionID = 0;

                                CurrentPawn->OnRep_ReplicatedMovement();
                                CurrentPawn->OnRep_CharPartAnimMontageInfo();
                                CurrentPawn->OnRep_ReplicatedAnimMontage();
                                CurrentPawn->OnRep_RepAnimMontageStartSection();
                                CurrentPawn->OnRep_ReplayRepAnimMontageInfo();
                                CurrentPawn->ForceNetUpdate();
                            }
                        }
                    }
                }

                return false;
            });

            HandlePEFunction("Function BP_VictoryDrone.BP_VictoryDrone_C.OnSpawnOutAnimEnded", {
                if (Object->IsA(ABP_VictoryDrone_C::StaticClass()))
                {
                    auto Drone = (ABP_VictoryDrone_C*)Object;

                    if (Drone)
                    {
                        Drone->K2_DestroyActor();
                    }
                }

                return false;
            });
		}
	}
}