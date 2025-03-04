void* Original_Setup_Move_Caller;

void __thiscall Redirected_Setup_Move(void* Unknown_Parameter_1, void* Player, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4)
{
	Byte_Manager::Set_Bytes(1, (float*)((unsigned __int32)Player + 276), sizeof(float[3]), 0);

	using Get_Weapon_Type = void* (__thiscall*)(void* Entity);

	void* Weapon = Get_Weapon_Type(604036352)(Player);

	if (Weapon != nullptr)
	{
		using Get_Weapon_Data_Type = void*(__thiscall*)(void* Weapon);

		*(float*)((unsigned __int32)Player + 3488) = *(float*)((unsigned __int32)Get_Weapon_Data_Type(604037872)(Weapon) + 1620);
	}

	(decltype(&Redirected_Setup_Move)(Original_Setup_Move_Caller))(Unknown_Parameter_1, Player, Unknown_Parameter_2, Unknown_Parameter_3, Unknown_Parameter_4);
}