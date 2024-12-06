void* Original_Set_Simulation_Time;

void Redirected_Set_Simulation_Time(void* Input, void* Unknown_Parameter)
{
	if (*(__int32*)((unsigned __int64)Input + 8) != 0)
	{
		(decltype(&Redirected_Set_Simulation_Time)(Original_Set_Simulation_Time))(Input, Unknown_Parameter);
	}
}