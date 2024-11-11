Redirection_Manager::Manager_Structure Post_Data_Update_Manager;

void Redirected_Post_Data_Update(void* Entity, void* Unknown_Parameter)
{
	float* Origin = (float*)((unsigned __int64)Entity + 1048);

	float* Previous_Origin = (float*)((unsigned __int64)Entity + 784);

	Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int64)Entity + 112)];

	Global_Variables_Structure* Global_Variables = Get_Global_Variables();

	if ((Origin[0] != Previous_Origin[0]) + (Origin[1] != Previous_Origin[1]) + (Origin[2] != Previous_Origin[2]) != 0)
	{
		Player_Data->Simulation_Ticks[0] = Global_Variables->Tick_Number - Player_Data->Tick_Number[0];

		Player_Data->Tick_Number[0] = Global_Variables->Tick_Number;
	}

	float Simulation_Time = *(float*)((unsigned __int64)Entity + 144);

	float Previous_Simulation_Time = *(float*)((unsigned __int64)Entity + 148);

	if (Simulation_Time != Previous_Simulation_Time)
	{
		Player_Data->Simulation_Ticks[1] = (Simulation_Time - Previous_Simulation_Time) / Global_Variables->Interval_Per_Tick + 0.5f;

		Player_Data->Tick_Number[1] = Global_Variables->Tick_Number;

		float* Origin = (float*)((unsigned __int64)Entity + 1048);

		Player_Data->Breaks_Lag_Compensation = __builtin_powf(Origin[0] - Player_Data->Origin[0], 2.f) + __builtin_powf(Origin[1] - Player_Data->Origin[1], 2.f) + __builtin_powf(Origin[2] - Player_Data->Origin[2], 2.f) > 4096.f;

		Byte_Manager::Copy_Bytes(1, Player_Data->Origin, sizeof(Player_Data->Origin), Origin);
	}

	Post_Data_Update_Manager.Special_Call(Entity, Unknown_Parameter);
}