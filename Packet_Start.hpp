void* Original_Packet_Start_Caller;

void __thiscall Redirected_Packet_Start(void* Unknown_Parameter_1, void* Unknown_Parameter_2, __int32 Outgoing_Sequence_Number)
{
	(decltype(&Redirected_Packet_Start)(Original_Packet_Start_Caller))(Unknown_Parameter_1, Unknown_Parameter_2, Sequences[Outgoing_Sequence_Number % 90]);
}