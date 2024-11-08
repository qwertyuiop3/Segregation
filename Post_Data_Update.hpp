SafetyHookInline Original_Post_Data_Update_Caller{};

void Redirected_Post_Data_Update(void* Entity, void* Unknown_Parameter)
{
	Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)((unsigned __int64)Client_Module + 8690824);
	
	Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int64)Entity + 112)];
	
	float* Networked_Origin = (float*)((unsigned __int64)Entity + 1048);
	
	float* Previous_Origin = (float*)((unsigned __int64)Entity + 784);
	
	if ((Networked_Origin[0] != Previous_Origin[0]) + (Networked_Origin[1] != Previous_Origin[1]) + (Networked_Origin[2] != Previous_Origin[2]) != 0)
	{
		Player_Data->Simulation_Ticks[0] = Global_Variables->Tick_Number - Player_Data->Last_Update_Tick_Number[0];
		
		Player_Data->Last_Update_Tick_Number[0] = Global_Variables->Tick_Number;
	}
	
	float Simulation_Time = *(float*)((unsigned __int64)Entity + 144);
	
	float Previous_Simulation_Time = *(float*)((unsigned __int64)Entity + 148);
	
	if (Simulation_Time != Previous_Simulation_Time)
	{
		Player_Data->Breaks_Lag_Compensation = __builtin_powf(Networked_Origin[0] - Player_Data->Last_Update_Origin[0], 2.f) + __builtin_powf(Networked_Origin[1] - Player_Data->Last_Update_Origin[1], 2.f) + __builtin_powf(Networked_Origin[2] - Player_Data->Last_Update_Origin[2], 2.f) > 4096.f;
		
		Player_Data->Simulation_Ticks[1] = (Simulation_Time - Previous_Simulation_Time) / Global_Variables->Interval_Per_Tick + 0.5f;
		
		Player_Data->Last_Update_Tick_Number[1] = Global_Variables->Tick_Number;
		
		Byte_Manager::Copy_Bytes(1, Player_Data->Last_Update_Origin, sizeof(Player_Data->Last_Update_Origin), Networked_Origin);
	}
	
	Original_Post_Data_Update_Caller.call<void>(Entity, Unknown_Parameter);
}