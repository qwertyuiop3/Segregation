SafetyHookInline Original_Read_Packets_Caller{};

void Redirected_Read_Packets(__int8 Final)
{
	static __int8 Parsed_Packets;

	if (Parsed_Packets == 0)
	{
		Original_Read_Packets_Caller.call<void>(Final);
	}

	Parsed_Packets = __builtin_return_address(0) != (void*)((unsigned __int64)Engine_Module + 1815028);
}