Redirection_Manager::Manager_Structure Post_Data_Update_Manager;

void Redirected_Post_Data_Update(void* Entity, void* Unknown_Parameter)
{
	float* Origin = (float*)((unsigned __int64)Entity + 1064);

	float* Previous_Origin = (float*)((unsigned __int64)Entity + 804);

	Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int64)Entity + 120)];

	Global_Variables_Structure* Global_Variables = Get_Global_Variables();

	auto Update_Data = [&](__int32 Tick_Number) -> void
	{
		Player_Data->Tick_Number[0] = Tick_Number;

		Player_Data->Tick_Number[1] = Global_Variables->Tick_Number;

		Player_Data->Teleported = __builtin_powf(Origin[0] - Previous_Origin[0], 2.f) + __builtin_powf(Origin[1] - Previous_Origin[1], 2.f) + __builtin_powf(Origin[2] - Previous_Origin[2], 2.f) > 4096.f;
	};

	if (__builtin_memcmp(Origin, Previous_Origin, sizeof(float[3])) != 0)
	{
		Update_Data(Player_Data->Tick_Number[1]);
	}

	double Simulation_Time = *(double*)((unsigned __int64)Entity + 160);

	double Previous_Simulation_Time = *(double*)((unsigned __int64)Entity + 168);

	if (Simulation_Time > Previous_Simulation_Time)
	{
		Update_Data(Global_Variables->Tick_Number - (__int32)((Simulation_Time - Previous_Simulation_Time) / Global_Variables->Interval_Per_Tick + 0.5));

		Player_Data->Data[6148] = -1;
	}

	Post_Data_Update_Manager.Special_Call(Entity, Unknown_Parameter);
}