void* Original_Post_Data_Update_Caller;

void __thiscall Redirected_Post_Data_Update(void* Entity, void* Unknown_Parameter)
{
	if (*(float*)((unsigned __int32)Entity + 104) != *(float*)((unsigned __int32)Entity + 108))
	{
		Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int32)Entity + 72)];

		Player_Data->Simulated = 1;

		if (Interface_Target_On_Simulation.Integer == 2)
		{
			float* Origin = (float*)((unsigned __int32)Entity + 660);

			float* Previous_Origin = (float*)((unsigned __int32)Entity + 624);

			if (__builtin_powf(Origin[0] - Previous_Origin[0], 2.f) + __builtin_powf(Origin[1] - Previous_Origin[1], 2.f) + __builtin_powf(Origin[2] - Previous_Origin[2], 2.f) > 4096.f)
			{
				Player_Data->Simulated = 0;
			}
		}
	}

	(decltype(&Redirected_Post_Data_Update)(Original_Post_Data_Update_Caller))(Entity, Unknown_Parameter);
}