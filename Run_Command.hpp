Redirection_Manager::Manager_Structure Run_Command_Manager;

void Redirected_Run_Command(void* Prediction, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Move_Helper)
{
	using Get_Angles_Type = void(**)(void* Engine, float* Angles);

	void* Engine = Get_Engine();

	float Angles[3];

	(*Get_Angles_Type(*(unsigned __int64*)Engine + 152))(Engine, Angles);

	(decltype(&Redirected_Run_Command)(Run_Command_Manager.Caller))(Prediction, Unknown_Parameter_1, Unknown_Parameter_2, Move_Helper);

	using Set_Angles_Type = void(**)(void* Engine, float* Angles);

	(*Set_Angles_Type(*(unsigned __int64*)Engine + 160))(Engine, Angles);
}