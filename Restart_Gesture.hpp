Redirection_Manager::Manager_Structure Restart_Gesture_Manager;

void Redirected_Restart_Gesture(void* Unknown_Parameter_1, void* Unknown_Parameter_2, __int32 Activity, void* Unknown_Parameter_3)
{
	if (Activity != 2019)
	{
		(decltype(&Redirected_Restart_Gesture)(Restart_Gesture_Manager.Caller))(Unknown_Parameter_1, Unknown_Parameter_2, Activity, Unknown_Parameter_3);
	}
}