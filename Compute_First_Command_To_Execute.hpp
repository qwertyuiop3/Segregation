void* Original_Compute_First_Command_To_Execute_Caller_Location;

struct Prediction_Data_Structure
{
	__int32 Tick_Number;

	void* Weapon;

	__int8 Delay_Fire;

	float Shots_Fired_Decrementor;
};

Prediction_Data_Structure Prediction_Data[90];

__int32 __thiscall Redirected_Compute_First_Command_To_Execute(void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4)
{
	__int32 Return_Value = (decltype(&Redirected_Compute_First_Command_To_Execute)(Original_Compute_First_Command_To_Execute_Caller_Location))(Unknown_Parameter_1, Unknown_Parameter_2, Unknown_Parameter_3, Unknown_Parameter_4);

	void* Local_Player = *(void**)((unsigned __int32)Client_Module_Location + 5015784);

	__int32 Tick_Number = *(__int32*)((unsigned __int32)Local_Player + 4332);

	Prediction_Data_Structure* Predicted_Data = &Prediction_Data[Tick_Number % 90];

	if (Predicted_Data->Tick_Number == Tick_Number)
	{
		void* Weapon = Predicted_Data->Weapon;

		if (Weapon != nullptr)
		{
			*(__int8*)((unsigned __int32)Weapon + 2340) = Predicted_Data->Delay_Fire;

			*(float*)((unsigned __int32)Weapon + 2356) = Predicted_Data->Shots_Fired_Decrementor;
		}
	}

	return Return_Value;
}