void* Original_Move_Caller;

void Redirected_Move(float Unknown_Parameter, __int8 Final)
{
	if (*(void**)((unsigned __int32)Client_Module + 5015784) != nullptr)
	{
		Redirected_Read_Packets(Final);

		using Run_Prediction_Type = void(__cdecl*)();

		Run_Prediction_Type((unsigned __int32)Engine_Module + 792144)();

		using Update_Animations_Type = void(__cdecl*)();

		Update_Animations_Type((unsigned __int32)Client_Module + 566576)();

		using Fire_Events_Type = void(__cdecl*)();

		Fire_Events_Type((unsigned __int32)Engine_Module + 785424)();

		Update_Animation_Time = (*(Global_Variables_Structure**)((unsigned __int32)Client_Module + 4825720))->Current_Time;

		Update_Animation_Type = 1;

		Update_Animations_Type((unsigned __int32)Client_Module + 566576)();

		Update_Animation_Type = 0;
	}

	(decltype(&Redirected_Move)(Original_Move_Caller))(Unknown_Parameter, Final);
}