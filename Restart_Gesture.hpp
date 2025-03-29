Redirection_Manager::Manager_Structure Restart_Gesture_Manager;

void Redirected_Restart_Gesture(void* Unknown_Parameter_1, void* Unknown_Parameter_2, __int32 Gesture_Activity, void* Unknown_Parameter_3)
{
	if (Gesture_Activity != 2019)
	{
		(decltype(&Redirected_Restart_Gesture)(Restart_Gesture_Manager.Caller))(Unknown_Parameter_1, Unknown_Parameter_2, Gesture_Activity, Unknown_Parameter_3);
	}
}