void* Original_Move_Caller;

void __vectorcall Redirected_Move(float Unknown_Parameter, __int8 Final)
{
	if (*(void**)((unsigned __int32)Client_Module + 82926756) != nullptr)
	{
		Redirected_Read_Packets(Final);

		using Run_Prediction_Type = void(__cdecl*)();

		Run_Prediction_Type((unsigned __int32)Engine_Module + 860016)();
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