Redirection_Manager::Manager_Structure Move_Manager;

void Redirected_Move(float Unknown_Parameter, __int8 Final)
{
	if (Get_Local_Player() != nullptr)
	{
		Redirected_Read_Packets(Final);

		using Run_Prediction_Type = void(*)();

		static void* Run_Prediction = Byte_Manager::Find_Bytes(26679, (unsigned __int8*)Engine_Module, 14835849722720403839ull);

		Run_Prediction_Type((unsigned __int64)Run_Prediction)();

		Update_Animation_Time = Get_Global_Variables()->Current_Time;

		Update_Animation_Type = 1;

		using Update_Animations_Type = void(*)();

		static void* Update_Animations = Byte_Manager::Find_Bytes(1013879, (unsigned __int8*)Client_Module, 8612103190241078388);

		Update_Animations_Type((unsigned __int64)Update_Animations)();

		Update_Animation_Type = 0;

		using Fire_Events_Type = void(*)();

		static void* Fire_Events = Byte_Manager::Find_Bytes(61442791308783, (unsigned __int8*)Engine_Module, 7283201772715103423);

		Fire_Events_Type((unsigned __int64)Fire_Events)();
	}

	(decltype(&Redirected_Move)(Move_Manager.Caller))(Unknown_Parameter, Final);
}