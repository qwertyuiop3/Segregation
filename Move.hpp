void* Original_Move_Caller;

void Redirected_Move(float Unknown_Parameter, __int8 Final)
{
	if (*(void**)607867332 != nullptr)
	{
		Redirected_Read_Packets(Final);

		using Run_Prediction_Type = void(__cdecl*)();

		Run_Prediction_Type(537158848)();

		using Update_Animations_Type = void(__cdecl*)();

		Update_Animations_Type(604212176)();

		using Fire_Events_Type = void(__cdecl*)();

		Fire_Events_Type(537149456)();

		Update_Animation_Time = (*(Global_Variables_Structure**)607726732)->Current_Time;

		Update_Animation_Type = 1;

		Update_Animations_Type(604212176)();

		Update_Animation_Type = 0;
	}

	(decltype(&Redirected_Move)(Original_Move_Caller))(Unknown_Parameter, Final);

	__int32 Entity_Number = 0;

	Traverse_Players_Data_Label:
	{
		Players_Data[Entity_Number].Simulated = 0;

		Entity_Number += 1;

		if (Entity_Number != sizeof(Players_Data) / sizeof(Player_Data_Structure))
		{
			goto Traverse_Players_Data_Label;
		}
	}
}