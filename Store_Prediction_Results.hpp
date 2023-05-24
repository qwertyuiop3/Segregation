void* Original_Store_Prediction_Results_Caller_Location;

void __thiscall Redirected_Store_Prediction_Results(void* Unknown_Parameter_1, void* Unknown_Parameter_2)
{
	void* Local_Player = *(void**)((unsigned __int32)Client_Module_Location + 5015784);

	__int32 Tick_Number = *(__int32*)((unsigned __int32)Local_Player + 4332);

	Prediction_Data_Structure* Predicted_Data = &Prediction_Data[Tick_Number % 90];

	Predicted_Data->Tick_Number = Tick_Number;

	void* Weapon = *(void**)((unsigned __int32)Client_Module_Location + 5135076 + (((*(unsigned __int32*)((unsigned __int32)Local_Player + 3456) & 4095) - 4097) << 4));

	Predicted_Data->Weapon = Weapon;

	if (Weapon != nullptr)
	{
		Predicted_Data->Delay_Fire = *(__int8*)((unsigned __int32)Weapon + 2340);

		Predicted_Data->Shots_Fired_Decrementor = *(float*)((unsigned __int32)Weapon + 2356);
	}

	(decltype(&Redirected_Store_Prediction_Results)(Original_Store_Prediction_Results_Caller_Location))(Unknown_Parameter_1, Unknown_Parameter_2);
}