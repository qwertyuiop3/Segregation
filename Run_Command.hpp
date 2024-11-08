SafetyHookInline Original_Run_Command_Caller{};

void Redirected_Run_Command(void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4)
{
	float View_Angles[3];

	using Get_View_Angles_Type = void(*)(void* Engine, float* View_Angles);

	Get_View_Angles_Type((unsigned __int64)Engine_Module + 492160)((void*)((unsigned __int64)Engine_Module + 4670832), View_Angles);

	Original_Run_Command_Caller.call<void>(Unknown_Parameter_1, Unknown_Parameter_2, Unknown_Parameter_3, Unknown_Parameter_4);

	using Set_View_Angles_Type = void(*)(void* Engine, float* View_Angles);

	Set_View_Angles_Type((unsigned __int64)Engine_Module + 494464)((void*)((unsigned __int64)Engine_Module + 4670832), View_Angles);
}