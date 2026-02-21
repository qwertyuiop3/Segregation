Redirection_Manager::Manager_Structure Move_Manager;

void Redirected_Move(float Unknown_Parameter, __int8 Final)
{
	if (*(void**)((unsigned __int64)Client_Module + 6245224) != nullptr)
	{
		Redirected_Read_Packets(Final);

		using Run_Prediction_Type = void(*)();

		Run_Prediction_Type((unsigned __int64)Engine_Module + 599696)();

		using Update_Animations_Type = void(*)();

		Update_Animations_Type((unsigned __int64)Client_Module + 512112)();

		using Fire_Events_Type = void(*)();

		Fire_Events_Type((unsigned __int64)Engine_Module + 591184)();

		Update_Animation_Type = 1;

		Update_Animations_Type((unsigned __int64)Client_Module + 512112)();

		Update_Animation_Type = 0;
	}

	(decltype(&Redirected_Move)(Move_Manager.Caller))(Unknown_Parameter, Final);

	__int32 Player_Number = 0;

	Traverse_Players_Data_Label:
	{
		Players_Data[Player_Number].Simulated = 0;

		Player_Number += 1;

		if (Player_Number != sizeof(Players_Data) / sizeof(Player_Data_Structure))
		{
			goto Traverse_Players_Data_Label;
		}
	}
}