Redirection_Manager::Manager_Structure Post_Data_Update_Manager;

void __thiscall Redirected_Post_Data_Update(void* Entity, void* Unknown_Parameter)
{
	if (*(float*)((unsigned __int64)Entity + 152) != *(float*)((unsigned __int64)Entity + 156))
	{
		Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int64)Entity + 240)];

		Player_Data->Simulated = 1;

		if (Interface_Target_On_Simulation.Integer == 2)
		{
			float* Origin = (float*)((unsigned __int64)Entity + 1048);

			float* Previous_Origin = (float*)((unsigned __int64)Entity + 784);

			if (__builtin_hypotf(Origin[0] - Previous_Origin[0], Origin[1] - Previous_Origin[1]) > 64.f)
			{
				Player_Data->Simulated = 0;
			}
		}
	}

	(decltype(&Redirected_Post_Data_Update)(Post_Data_Update_Manager.Caller))(Entity, Unknown_Parameter);
}