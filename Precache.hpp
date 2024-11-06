void* Original_Precache_Caller;

void __thiscall Redirected_Precache(void* Material)
{
	if ((*(unsigned __int16*)((unsigned __int32)Material + 32) & 2) == 0)
	{
		static __int8 Precache;

		if (Precache == 0)
		{
			Precache = 1;

			using Get_Group_Type = char*(__thiscall**)(void* Material);

			if (*(unsigned __int16*)(*Get_Group_Type(*(unsigned __int32*)Material + 4))(Material) == 'oW')
			{
				using Alpha_Modulate_Type = void(__thiscall**)(void* Material, float Alpha);

				(*Alpha_Modulate_Type(*(unsigned __int32*)Material + 116))(Material, 0.25f);

				using Color_Modulate_Type = void(__thiscall**)(void* Material, float Red, float Green, float Blue);

				(*Color_Modulate_Type(*(unsigned __int32*)Material + 120))(Material, 1.f, 0.5f, 0.5f);
			}

			Precache = 0;
		}
	}

	(decltype(&Redirected_Precache)(Original_Precache_Caller))(Material);
}