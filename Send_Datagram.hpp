void* Original_Send_Datagram_Caller;

__int32 __thiscall Redirected_Send_Datagram(void* Network_Channel, void* Unknown_Parameter)
{
	__int32 Sequence_Number = (decltype(&Redirected_Send_Datagram)(Original_Send_Datagram_Caller))(Network_Channel, Unknown_Parameter);

	if (__builtin_return_address(0) == (void*)((unsigned __int32)Engine_Module + 841852))
	{
		void* Client = *(void**)((unsigned __int32)Engine_Module + 5757076);

		Sequence_Number = Sequences[Sequence_Number % 150] = *(__int32*)((unsigned __int32)Client + 19628) + *(__int32*)((unsigned __int32)Client + 19632) + 1;
	}

	return Sequence_Number;
}