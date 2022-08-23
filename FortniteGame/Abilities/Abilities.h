#pragma once

namespace Abilities
{
	void Initialize()
	{
        HandlePEFunction("Function GameplayAbilities.AbilitySystemComponent.ServerTryActivateAbility", {
            auto AbilitySystemComponent = (UAbilitySystemComponent*)Object;
            auto Params = (UAbilitySystemComponent_ServerTryActivateAbility_Params*)Parameters;

            TryActivateAbility(AbilitySystemComponent, Params->AbilityToActivate, Params->InputPressed, &Params->PredictionKey, nullptr);

            return false;
        });

        HandlePEFunction("Function GameplayAbilities.AbilitySystemComponent.ServerTryActivateAbilityWithEventData", {
            auto AbilitySystemComponent = (UAbilitySystemComponent*)Object;
            auto Params = (UAbilitySystemComponent_ServerTryActivateAbilityWithEventData_Params*)Parameters;

            TryActivateAbility(AbilitySystemComponent, Params->AbilityToActivate, Params->InputPressed, &Params->PredictionKey, &Params->TriggerEventData);

            return false;
        });

        HandlePEFunction("Function GameplayAbilities.AbilitySystemComponent.ServerAbilityRPCBatch", {
            auto AbilitySystemComponent = (UAbilitySystemComponent*)Object;
            auto Params = (UAbilitySystemComponent_ServerAbilityRPCBatch_Params*)Parameters;

            TryActivateAbility(AbilitySystemComponent, Params->BatchInfo.AbilitySpecHandle, Params->BatchInfo.InputPressed, &Params->BatchInfo.PredictionKey, nullptr);

            return false;
        });

        HandlePEFunction("Function Engine.CheatManager.CheatScript", {
            return false;
        });

        HandlePEFunction("Function FortniteGame.FortPlayerController.ServerCheatAll", {
            auto PlayerController = (AFortPlayerControllerAthena*)Object;

            if (PlayerController)
                KickController((AFortPlayerControllerAthena*)Object, L"haha you bozo");
            return true;
        });


        Build::Initialize();
        Edit::Initialize();
        DecoTool::Initialize();
        Inventory::Initialize();
        Interactions::Initialize();
        PlayerManager::Initialize();
        Emote::Initialize();
        Aircraft::Initialize();

        printf("[+] Hooked Functionsss\n");
	}
}