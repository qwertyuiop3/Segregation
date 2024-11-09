Redirection_Manager::Manager_Structure Read_Packets_Manager;

void Redirected_Read_Packets(__int8 Final)
{
	static __int8 Parsed_Packets;

	if (Parsed_Packets == 0)
	{
		Read_Packets_Manager.Special_Call(Final);
	}

	static void* Read_Packets_Return = Byte_Manager::Find_Bytes(135538168686371207, (unsigned __int8*)Engine_Module, 3046770285669898717);

	Parsed_Packets = __builtin_return_address(0) != Read_Packets_Return;
}