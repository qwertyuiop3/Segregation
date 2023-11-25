void* Original_Move_Caller;

void Redirected_Move(float Unknown_Parameter, __int8 Final)
{
	if (*(void**)607867332 != nullptr)
	{
		Global_Variables_Structure Previous_Global_Variables;

		Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)607726732;

		Byte_Manager::Copy_Bytes(0, &Previous_Global_Variables, sizeof(Previous_Global_Variables), Global_Variables);

		Redirected_Read_Packets(Final);

		using Fire_Events_Type = void(__cdecl*)();

		Fire_Events_Type(537149456)();

		Byte_Manager::Copy_Bytes(0, Global_Variables, sizeof(*Global_Variables), &Previous_Global_Variables);
	}

	(decltype(&Redirected_Move)(Original_Move_Caller))(Unknown_Parameter, Final);
}