#pragma once

namespace Abilities
{
	namespace DecoTool
	{
        void SpawnDeco(AFortDecoTool* Tool, void* _Params)
        {
            if (!_Params)
                return;

            auto Params = (AFortDecoTool_ServerSpawnDeco_Params*)_Params;

            FTransform Transform{};
            Transform.Scale3D = FVector(1, 1, 1);
            Transform.Rotation = RotToQuat(Params->Rotation);
            Transform.Translation = Params->Location;

            auto TrapDef = (UFortTrapItemDefinition*)Tool->ItemDefinition;

            if (TrapDef)
            {
                auto Trap = (ABuildingTrap*)SpawnActorTrans(TrapDef->GetBlueprintClass(), Transform);

                if (Trap)
                {
                    Trap->TrapData = TrapDef;

                    auto Pawn = (APlayerPawn_Athena_C*)Tool->Owner;

                    Trap->InitializeKismetSpawnedBuildingActor(Trap, (AFortPlayerController*)Pawn->Controller);

                    Trap->AttachedTo = Params->AttachedActor;
                    Trap->OnRep_AttachedTo();

                    auto PlayerState = (AFortPlayerStateAthena*)Pawn->Controller->PlayerState;
                    Trap->Team = PlayerState->TeamIndex;

                    auto TrapAbilitySet = Trap->AbilitySet;

                    for (int i = 0; i < TrapAbilitySet->GameplayAbilities.Num(); i++)
                    {
                        auto Ability = TrapAbilitySet->GameplayAbilities[i];

                        if (!Ability)
                            continue;

                        GrantGameplayAbility(Pawn, Ability);
                    }
                }
            }
        }

		void Initialize()
		{
            HandlePEFunction("Function FortniteGame.FortDecoTool.ServerSpawnDeco", {
                SpawnDeco((AFortDecoTool*)Object, Parameters);
                return false;
            });
		}
	}
}