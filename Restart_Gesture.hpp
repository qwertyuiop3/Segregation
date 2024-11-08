Redirection_Manager::Manager_Structure Restart_Gesture_Manager;

void Redirected_Restart_Gesture(void* Unknown_Parameter_1, __int32 Gesture_Slot, void* Unknown_Parameter_2, void* Unknown_Parameter_3)
{
	if (Gesture_Slot != 5)
	{
		(decltype(&Redirected_Restart_Gesture)(Restart_Gesture_Manager.Caller))(Unknown_Parameter_1, Gesture_Slot, Unknown_Parameter_2, Unknown_Parameter_3);
	}
}