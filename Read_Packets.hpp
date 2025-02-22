Redirection_Manager::Manager_Structure Read_Packets_Manager;

void Redirected_Read_Packets(__int8 Final)
{
	static __int8 Parsed_Packets;

	if (Parsed_Packets == 0)
	{
		(decltype(&Redirected_Read_Packets)(Read_Packets_Manager.Caller))(Final);
	}

	Parsed_Packets = __builtin_return_address(0) != (void*)((unsigned __int64)Engine_Module + 1726562);
}