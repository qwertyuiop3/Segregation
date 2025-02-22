Redirection_Manager::Manager_Structure Send_Datagram_Manager;

__int32 Redirected_Send_Datagram(void* Network_Channel, void* Unknown_Parameter)
{
	__int32 Sequence_Number = (decltype(&Redirected_Send_Datagram)(Send_Datagram_Manager.Caller))(Network_Channel, Unknown_Parameter);

	if (__builtin_return_address(0) == (void*)((unsigned __int64)Engine_Module + 577073))
	{
		Sequence_Number = Sequences[Sequence_Number % 90] = *(__int32*)((unsigned __int64)Engine_Module + 5497988) + *(__int32*)((unsigned __int64)Engine_Module + 5497992) + 1;
	}

	return Sequence_Number;
}