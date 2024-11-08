SafetyHookInline Original_Precache_Caller{};

__int8 Redirected_Precache(void* Material)
{
	if ((*(unsigned __int16*)((unsigned __int64)Material + 48) & 8) == 0)
	{
		static __int8 Precache;

		if (Precache == 0)
		{
			Precache = 1;

			using Get_Group_Type = char*(**)(void* Material);

			if (*(unsigned __int16*)(*Get_Group_Type(*(unsigned __int64*)Material + 8))(Material) == 'oW')
			{
				using Alpha_Modulate_Type = void(**)(void* Material, float Alpha);

				(*Alpha_Modulate_Type(*(unsigned __int64*)Material + 216))(Material, 0.25f);

				using Color_Modulate_Type = void(**)(void* Material, float Red, float Green, float Blue);

				(*Color_Modulate_Type(*(unsigned __int64*)Material + 224))(Material, 1.f, 0.5f, 0.5f);
			}

			Precache = 0;
		}
	}

	return Original_Precache_Caller.call<__int8>(Material);
}