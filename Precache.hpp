Redirection_Manager::Manager_Structure Precache_Manager;

void Redirected_Precache(void* Material)
{
	using Get_Group_Type = char*(**)(void* Material);

	if (*(unsigned __int16*)(*Get_Group_Type(*(unsigned __int64*)Material + 8))(Material) == 'oW')
	{
		using Alpha_Modulate_Type = void(**)(void* Material, float Alpha);

		(*Alpha_Modulate_Type(*(unsigned __int64*)Material + 216))(Material, 0.25f);

		using Color_Modulate_Type = void(**)(void* Material, float Red, float Green, float Blue);

		(*Color_Modulate_Type(*(unsigned __int64*)Material + 224))(Material, 1.f, 0.5f, 0.5f);
	}

	return (decltype(&Redirected_Precache)(Precache_Manager.Caller))(Material);
}