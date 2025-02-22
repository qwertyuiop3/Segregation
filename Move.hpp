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

		Update_Animation_Time = (*(Global_Variables_Structure**)((unsigned __int64)Client_Module + 5956224))->Current_Time;

		Update_Animation_Type = 1;

		Update_Animations_Type((unsigned __int64)Client_Module + 512112)();

		Update_Animation_Type = 0;
	}

	(decltype(&Redirected_Move)(Move_Manager.Caller))(Unknown_Parameter, Final);
}