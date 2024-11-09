void* Original_Set_Simulation_Time;

void Redirected_Set_Simulation_Time(void* Input, void* Unknown_Parameter_1, void* Unknown_Parameter_2)
{
	if (*(__int32*)((unsigned __int64)Input + 8) != 0)
	{
		(decltype(&Redirected_Set_Simulation_Time)(Original_Set_Simulation_Time))(Input, Unknown_Parameter_1, Unknown_Parameter_2);
	}
}