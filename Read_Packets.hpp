void* Original_Read_Packets_Caller;

void Redirected_Read_Packets(__int8 Final)
{
	static __int8 Parsed_Packets;

	if (Parsed_Packets == 0)
	{
		(decltype(&Redirected_Read_Packets)(Original_Read_Packets_Caller))(Final);
	}

	Parsed_Packets = __builtin_return_address(0) != (void*)537729110;
}