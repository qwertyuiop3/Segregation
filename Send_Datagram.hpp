Redirection_Manager::Manager_Structure Send_Datagram_Manager;

__int32 Redirected_Send_Datagram(void* Unknown_Parameter_1, void* Unknown_Parameter_2)
{
	__int32 Sequence_Number = (decltype(&Redirected_Send_Datagram)(Send_Datagram_Manager.Caller))(Unknown_Parameter_1, Unknown_Parameter_2);
	
	static void* Send_Datagram_Return = Byte_Manager::Find_Bytes(387, (unsigned __int8*)Engine_Module, 16417728077454269531ull);
	
	if (__builtin_return_address(0) == Send_Datagram_Return)
	{
		__int32 Next_Command_Number = Get_Last_Command_Number() + Get_Choked_Commands() + 1;
		
		Sequences[Sequence_Number % 90] = Next_Command_Number;

		Sequence_Number = Next_Command_Number;
	}
	
	return Sequence_Number;
}