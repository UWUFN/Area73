#pragma once
#include <vector>

namespace ItemDefinitions
{
	enum WeaponItemDefinitionNames {
		AssaultRifle_Grey, AssaultRifle_Green, AssaultRifle_Blue, AssaultRifle_Purple, AssaultRifle_Gold,
		PumpShotgun_Green, PumpShotgun_Blue,
		TacticalShotgun_Grey, TacticalShotgun_Green, TacticalShotgun_Blue,
		HeavyShotgun_Purple, HeavyShotgun_Gold,
		BoltAction_Blue, BoltAction_Purple, BoltAction_Gold,
		SemiAutoSniper_Green, SemiAutoSniper_Blue,
		SMG_Grey, SMG_Green, SMG_Blue,
		TacticalSMG_Green, TacticalSMG_Blue, TacticalSMG_Purple,
		Minigun_Purple, Minigun_Gold,
		Pistol_Grey, Pistol_Green, Pistol_Blue,
		SilencedPistol_Blue, SilencedPistol_Purple,
		Revolver_Grey, Revolver_Green, Revolver_Blue,
		RocketLauncher_Blue, RocketLauncher_Purple, RocketLauncher_Gold
	};

	std::vector<std::string> WeaponItemDefinitionArray = {
		"/Game/Athena/Items/Weapons/WID_Assault_Auto_Athena_C_Ore_T02.WID_Assault_Auto_Athena_C_Ore_T02",
		"/Game/Athena/Items/Weapons/WID_Assault_Auto_Athena_UC_Ore_T03.WID_Assault_Auto_Athena_UC_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Assault_Auto_Athena_R_Ore_T03.WID_Assault_Auto_Athena_R_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Assault_AutoHigh_Athena_VR_Ore_T03.WID_Assault_AutoHigh_Athena_VR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Assault_AutoHigh_Athena_SR_Ore_T03.WID_Assault_AutoHigh_Athena_SR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Assault_Heavy_Athena_R_Ore_T03.WID_Assault_Heavy_Athena_R_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Assault_Heavy_Athena_VR_Ore_T03.WID_Assault_Heavy_Athena_VR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Assault_Heavy_Athena_SR_Ore_T03.WID_Assault_Heavy_Athena_SR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Assault_SemiAuto_Athena_SR_Ore_T03.WID_Assault_SemiAuto_Athena_SR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Assault_SemiAuto_Athena_VR_Ore_T03.WID_Assault_SemiAuto_Athena_VR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Assault_Suppressed_Athena_SR_Ore_T03.WID_Assault_Suppressed_Athena_SR_Ore_T03", //left off at the suppressed scar
		"/Game/Athena/Items/Weapons/WID_Assault_Suppressed_Athena_VR_Ore_T03.WID_Assault_Suppressed_Athena_VR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Shotgun_Standard_Athena_SR_Ore_T03.WID_Shotgun_Standard_Athena_SR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Shotgun_Standard_Athena_VR_Ore_T03.WID_Shotgun_Standard_Athena_VR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Shotgun_Standard_Athena_C_Ore_T03.WID_Shotgun_Standard_Athena_C_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Shotgun_Standard_Athena_UC_Ore_T03.WID_Shotgun_Standard_Athena_UC_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Shotgun_SemiAuto_Athena_UC_Ore_T03.WID_Shotgun_SemiAuto_Athena_UC_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Shotgun_SemiAuto_Athena_R_Ore_T03.WID_Shotgun_SemiAuto_Athena_R_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Shotgun_SemiAuto_Athena_VR_Ore_T03.WID_Shotgun_SemiAuto_Athena_VR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Shotgun_SlugFire_Athena_VR.WID_Shotgun_SlugFire_Athena_VR",
		"/Game/Athena/Items/Weapons/WID_Shotgun_SlugFire_Athena_SR.WID_Shotgun_SlugFire_Athena_SR",
		"/Game/Athena/Items/Weapons/WID_Sniper_Heavy_Athena_SR_Ore_T03.WID_Sniper_Heavy_Athena_SR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Sniper_Heavy_Athena_VR_Ore_T03.WID_Sniper_Heavy_Athena_VR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Sniper_BoltAction_Scope_Athena_R_Ore_T03.WID_Sniper_BoltAction_Scope_Athena_R_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Sniper_BoltAction_Scope_Athena_VR_Ore_T03.WID_Sniper_BoltAction_Scope_Athena_VR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Sniper_BoltAction_Scope_Athena_SR_Ore_T03.WID_Sniper_BoltAction_Scope_Athena_SR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Sniper_Standard_Scope_Athena_VR_Ore_T03.WID_Sniper_Standard_Scope_Athena_VR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Sniper_Standard_Scope_Athena_SR_Ore_T03.WID_Sniper_Standard_Scope_Athena_SR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Pistol_AutoHeavyPDW_Athena_C_Ore_T03.WID_Pistol_AutoHeavyPDW_Athena_C_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Pistol_AutoHeavyPDW_Athena_UC_Ore_T03.WID_Pistol_AutoHeavyPDW_Athena_UC_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Pistol_AutoHeavyPDW_Athena_R_Ore_T03.WID_Pistol_AutoHeavyPDW_Athena_R_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Pistol_AutoHeavyPDW_Athena_VR_Ore_T03.WID_Pistol_AutoHeavyPDW_Athena_VR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Pistol_AutoHeavyPDW_Athena_R_Ore_T03.WID_Pistol_AutoHeavyPDW_Athena_R_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Pistol_SemiAuto_Athena_C_Ore_T02.WID_Pistol_SemiAuto_Athena_C_Ore_T02",
		"/Game/Athena/Items/Weapons/WID_Pistol_SemiAuto_Athena_UC_Ore_T03.WID_Pistol_SemiAuto_Athena_UC_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Pistol_SemiAuto_Athena_R_Ore_T03.WID_Pistol_SemiAuto_Athena_R_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Pistol_SemiAuto_Athena_VR_Ore_T03.WID_Pistol_SemiAuto_Athena_VR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Pistol_SemiAuto_Athena_SR_Ore_T03.WID_Pistol_SemiAuto_Athena_SR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_DualPistol_SemiAuto_Athena_SR_Ore_T03.WID_DualPistol_SemiAuto_Athena_SR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_DualPistol_SemiAuto_Athena_VR_Ore_T03.WID_DualPistol_SemiAuto_Athena_VR_Ore_T03",
	};

	std::vector<UFortItemDefinition*> WeaponItemDefinitionAddresses = {};



	enum ConsumableItemDefinitionNames {
		Shields,
		ShieldSmall,
		PurpleStuff,
		SuperMedkit,
		Grenade,
		KnockGrenade,
		ShockGrenade,
		SmokeGrenade,
		StickyGrenade,
		Bush,
		Medkit,
		DanceGrenade
	};

	std::vector<std::string> ConsumableItemDefinitionArray = {
		"/Game/Athena/Items/Consumables/Shields/Athena_Shields.Athena_Shields",
		"/Game/Athena/Items/Consumables/ShieldSmall/Athena_ShieldSmall.Athena_ShieldSmall",
		"/Game/Athena/Items/Consumables/PurpleStuff/Athena_PurpleStuff.Athena_PurpleStuff",
		"/Game/Athena/Items/Consumables/SuperMedkit/Athena_SuperMedkit.Athena_SuperMedkit",
		"/Game/Athena/Items/Consumables/Grenade/Athena_Grenade.Athena_Grenade",
		"/Game/Athena/Items/Consumables/KnockGrenade/Athena_KnockGrenade.Athena_KnockGrenade",
		"/Game/Athena/Items/Consumables/ShockwaveGrenade/Athena_ShockGrenade.Athena_ShockGrenade",
		"/Game/Athena/Items/Consumables/SmokeGrenade/Athena_SmokeGrenade.Athena_SmokeGrenade",
		"/Game/Athena/Items/Consumables/StickyGrenade/Athena_StickyGrenade.Athena_StickyGrenade",
		"/Game/Athena/Items/Consumables/Bush/Athena_Bush.Athena_Bush",
		"/Game/Athena/Items/Consumables/Medkit/Athena_Medkit.Athena_Medkit",
		"/Game/Athena/Items/Consumables/DanceGrenade/Athena_DanceGrenade.Athena_DanceGrenade"
	};

	std::vector<UFortItemDefinition*> ConsumableItemDefinitionAddresses = {};



	enum AmmoItemDefinitionNames {
		Rockets,
		Shells,
		Medium,
		Light,
		Heavy
	};

	std::vector<std::string> AmmoItemDefinitionArray = {
		"/Game/Athena/Items/Ammo/AmmoDataRockets.AmmoDataRockets",
		"/Game/Athena/Items/Ammo/AthenaAmmoDataShells.AthenaAmmoDataShells",
		"/Game/Athena/Items/Ammo/AthenaAmmoDataBulletsMedium.AthenaAmmoDataBulletsMedium",
		"/Game/Athena/Items/Ammo/AthenaAmmoDataBulletsLight.AthenaAmmoDataBulletsLight",
		"/Game/Athena/Items/Ammo/AthenaAmmoDataBulletsHeavy.AthenaAmmoDataBulletsHeavy"
	};

	std::vector<UFortItemDefinition*> AmmoItemDefinitionAddresses = {};



	enum MaterialItemDefinitionNames {
		Wood,
		Stone,
		Metal
	};

	std::vector<std::string> MaterialItemDefinitionArray = {
		"/Game/Items/ResourcePickups/WoodItemData.WoodItemData",
		"/Game/Items/ResourcePickups/StoneItemData.StoneItemData",
		"/Game/Items/ResourcePickups/MetalItemData.MetalItemData"
	};

	std::vector<UFortItemDefinition*> MaterialItemDefinitionAddresses = {};



	enum TrapItemDefinitionNames {
		LaunchPad,
		Campfire,
		Spike,
		Bouncer
	};

	std::vector<std::string> TrapItemDefinitionArray = {
		"/Game/Athena/Items/Traps/TID_Floor_Player_Launch_Pad_Athena.TID_Floor_Player_Launch_Pad_Athena",
		"/Game/Athena/Items/Traps/TID_Floor_Campfire_R_T04.TID_Floor_Campfire_R_T04",
		"/Game/Athena/Items/Traps/TID_Floor_Spikes_Athena_R_T03.TID_Floor_Spikes_Athena_R_T03",
		"/Game/Athena/Items/Traps/TID_Context_BouncePad_Athena.TID_Context_BouncePad_Athena"
	};

	std::vector<UFortItemDefinition*> TrapItemDefinitionAddresses = {};



	UFortItemDefinition* Pickaxe;



	UFortItemDefinition* GetWeapon(bool bRandom, WeaponItemDefinitionNames name = {})
	{
		return WeaponItemDefinitionAddresses[bRandom ? (rand() % WeaponItemDefinitionArray.size()) : name];
	}

	UFortItemDefinition* GetConsumable(bool bRandom, int* count, ConsumableItemDefinitionNames name = {})
	{
		auto Consumable = ConsumableItemDefinitionAddresses[bRandom ? (rand() % ConsumableItemDefinitionArray.size()) : name];
		auto ConsumableName = Consumable->GetPersistentName().c_str();

		if (wcsstr(ConsumableName, L"athena_shieldsmall"))
			*count = 3;
		else if (wcsstr(ConsumableName, L"athena_shields"))
			*count = 1;
		else if (wcsstr(ConsumableName, L"athena_purplestuff"))
			*count = 1;
		else if (wcsstr(ConsumableName, L"athena_supermedkit"))
			*count = 1;
		else if (wcsstr(ConsumableName, L"athena_grenade"))
			*count = 3;
		else if (wcsstr(ConsumableName, L"athena_knockgrenade"))
			*count = 3;
		else if (wcsstr(ConsumableName, L"athena_shockgrenade"))
			*count = 3;
		else if (wcsstr(ConsumableName, L"athena_smokegrenade"))
			*count = 3;
		else if (wcsstr(ConsumableName, L"athena_stickygrenade"))
			*count = 3;
		else if (wcsstr(ConsumableName, L"athena_bush"))
			*count = 1;
		else if (wcsstr(ConsumableName, L"athena_medkit"))
			*count = 1;
		else if (wcsstr(ConsumableName, L"athena_dancegrenade"))
			*count = 1;

		return Consumable;
	}

	bool IsConsumable(UFortItemDefinition* Definition)
	{
		if (!Definition) return false;

		auto ConsumableName = Definition->GetPersistentName().c_str();

		if (wcsstr(ConsumableName, L"athena_shieldsmall"))
			return true;
		else if (wcsstr(ConsumableName, L"athena_shields"))
			return true;
		else if (wcsstr(ConsumableName, L"athena_purplestuff"))
			return true;
		else if (wcsstr(ConsumableName, L"athena_supermedkit"))
			return true;
		else if (wcsstr(ConsumableName, L"athena_grenade"))
			return true;
		else if (wcsstr(ConsumableName, L"athena_knockgrenade"))
			return true;
		else if (wcsstr(ConsumableName, L"athena_shockgrenade"))
			return true;
		else if (wcsstr(ConsumableName, L"athena_smokegrenade"))
			return true;
		else if (wcsstr(ConsumableName, L"athena_stickygrenade"))
			return true;
		else if (wcsstr(ConsumableName, L"athena_bush"))
			return true;
		else if (wcsstr(ConsumableName, L"athena_medkit"))
			return true;
		else if (wcsstr(ConsumableName, L"athena_dancegrenade"))
			return true;

		return false;
	}

	UFortItemDefinition* GetAmmo(bool bRandom, int* count, AmmoItemDefinitionNames name = {})
	{
		auto Ammo =  AmmoItemDefinitionAddresses[bRandom ? (rand() % AmmoItemDefinitionArray.size()) : name];
		*count = ((UFortAmmoItemDefinition*)Ammo)->DropCount;
		return Ammo;
	}

	UFortItemDefinition* GetAmmoOfWeapon(UFortItemDefinition* Weapon, int* count)
	{
		if (Weapon)
		{
			auto Ammo = ((UFortWorldItemDefinition*)Weapon)->GetAmmoWorldItemDefinition_BP();
			*count = ((UFortAmmoItemDefinition*)Ammo)->DropCount;
			return Ammo;
		}

		return GetAmmo(false, count, AmmoItemDefinitionNames::Medium);
	}

	UFortItemDefinition* GetMaterial(bool bRandom, MaterialItemDefinitionNames name = {})
	{
		return MaterialItemDefinitionAddresses[bRandom ? (rand() % MaterialItemDefinitionArray.size()) : name];
	}

	UFortItemDefinition* GetTrap(bool bRandom, TrapItemDefinitionNames name = {})
	{
		return TrapItemDefinitionAddresses[bRandom ? (rand() % TrapItemDefinitionArray.size()) : name];
	}

	UFortItemDefinition* GetPickaxe()
	{
		return Pickaxe;//UObject::FindObject<UFortItemDefinition>(/*"WID_Harvest_Pickaxe_Athena_C_T01.WID_Harvest_Pickaxe_Athena_C_T01"*/"/Game/Athena/Items/Weapons/WID_Harvest_Pickaxe_Carrot.WID_Harvest_Pickaxe_Carrot");
	}


}