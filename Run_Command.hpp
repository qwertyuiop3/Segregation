Redirection_Manager::Manager_Structure Run_Command_Manager;

void Redirected_Run_Command(void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4)
{
	float Angles[3];

	using Get_Angles_Type = void(*)(void* Engine, float* Angles);

	Get_Angles_Type((unsigned __int64)Engine_Module + 492160)((void*)((unsigned __int64)Engine_Module + 4670832), Angles);

	(decltype(&Redirected_Run_Command)(Run_Command_Manager.Caller))(Unknown_Parameter_1, Unknown_Parameter_2, Unknown_Parameter_3, Unknown_Parameter_4);

	using Set_Angles_Type = void(*)(void* Engine, float* Angles);

	Set_Angles_Type((unsigned __int64)Engine_Module + 494464)((void*)((unsigned __int64)Engine_Module + 4670832), Angles);
}