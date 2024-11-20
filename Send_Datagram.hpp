Redirection_Manager::Manager_Structure Send_Datagram_Manager;

__int32 Redirected_Send_Datagram(void* Network_Channel, void* Unknown_Parameter)
{
	__int32 Sequence_Number = (decltype(&Redirected_Send_Datagram)(Send_Datagram_Manager.Caller))(Network_Channel, Unknown_Parameter);

	static void* Send_Datagram_Return = Byte_Manager::Find_Bytes(387, (unsigned __int8*)Engine_Module, 16417728077454269531ull);

	if (__builtin_return_address(0) == Send_Datagram_Return)
	{
		Sequence_Number = Sequences[Sequence_Number % 90] = Get_Last_Command_Number() + Get_Choked_Commands() + 1;
	}

	return Sequence_Number;
}