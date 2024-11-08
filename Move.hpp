Redirection_Manager::Manager_Structure Move_Manager;

void Redirected_Move(float Unknown_Parameter, __int8 Final)
{
	if (Get_Local_Player() != nullptr)
	{
		Redirected_Read_Packets(Final);

		using Fire_Events_Type = void(*)();

		Fire_Events_Type((unsigned __int64)Engine_Module + 625008)();
	}

	(decltype(&Redirected_Move)(Move_Manager.Caller))(Unknown_Parameter, Final);

	using Update_Animations_Type = void(*)();

	Update_Animations_Type((unsigned __int64)Client_Module + 1682880)();

	Update_Animation_Time = (*(Global_Variables_Structure**)((unsigned __int64)Client_Module + 8690824))->Current_Time;

	Update_Animation_Type = 1;

	Update_Animations_Type((unsigned __int64)Client_Module + 1682880)();

	Update_Animation_Type = 0;
}