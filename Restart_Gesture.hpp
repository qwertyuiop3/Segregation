SafetyHookInline Original_Restart_Gesture_Caller{};

void Redirected_Restart_Gesture(void* Unknown_Parameter_1, __int32 Gesture_Slot, void* Unknown_Parameter_2, void* Unknown_Parameter_3)
{
	if (Gesture_Slot != 5)
	{
		Original_Restart_Gesture_Caller.call<void>(Unknown_Parameter_1, Gesture_Slot, Unknown_Parameter_2, Unknown_Parameter_3);
	}
}