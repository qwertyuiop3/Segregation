float Weapon_Spread;

void* Original_Weapon_Spread_Caller;

void* __thiscall Redirected_Weapon_Spread(void* Weapon)
{
	if (Weapon_Spread <= 0.f)
	{
		Weapon_Spread *= -1.f;

		return (decltype(&Redirected_Weapon_Spread)(Original_Weapon_Spread_Caller))(Weapon);
	}

	Weapon_Spread = *(float*)((unsigned __int32)__builtin_frame_address(0) + 72);

	return nullptr;
}