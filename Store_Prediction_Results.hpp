void* Original_Store_Prediction_Results_Caller;

void __thiscall Redirected_Store_Prediction_Results(void* Unknown_Parameter_1, void* Unknown_Parameter_2)
{
	void* Local_Player = *(void**)607867332;

	__int32 Tick_Number = *(__int32*)((unsigned __int32)Local_Player + 3592);

	Prediction_Data_Structure* Predicted_Data = &Prediction_Data[Tick_Number % 90];

	Predicted_Data->Tick_Number = Tick_Number;

	Predicted_Data->Friction = *(float*)((unsigned __int32)Local_Player + 3936);

	void* Weapon = *(void**)((unsigned __int32)607973860 + (((*(unsigned __int32*)((unsigned __int32)Local_Player + 2872) & 4095) - 4097) << 4));

	Predicted_Data->Weapon = Weapon;

	if (Weapon != nullptr)
	{
		Predicted_Data->Delay_Fire = *(__int8*)((unsigned __int32)Weapon + 1884);

		Predicted_Data->Accuracy = *(float*)((unsigned __int32)Weapon + 1888);

		Predicted_Data->Shots_Fired_Decrementor = *(float*)((unsigned __int32)Weapon + 1892);

		Predicted_Data->Last_Fire = *(float*)((unsigned __int32)Weapon + 1912);
	}

	(decltype(&Redirected_Store_Prediction_Results)(Original_Store_Prediction_Results_Caller))(Unknown_Parameter_1, Unknown_Parameter_2);
}