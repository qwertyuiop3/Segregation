SafetyHookInline Original_Move_Caller{};

void Redirected_Move(float Unknown_Parameter, __int8 Final)
{
	if (*(void**)((unsigned __int64)Client_Module + 9394464) != nullptr)
	{
		Redirected_Read_Packets(Final);

		using Fire_Events_Type = void(*)();

		Fire_Events_Type((unsigned __int64)Engine_Module + 625008)();
	}

	Original_Move_Caller.call<void>(Unknown_Parameter, Final);

	using Update_Animations_Type = void(*)();

	Update_Animations_Type((unsigned __int64)Client_Module + 1682880)();

	Update_Animation_Time = (*(Global_Variables_Structure**)((unsigned __int64)Client_Module + 8690824))->Current_Time;

	Update_Animation_Type = 1;

	Update_Animations_Type((unsigned __int64)Client_Module + 1682880)();

	Update_Animation_Type = 0;
}