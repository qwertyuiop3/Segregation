SafetyHookInline Original_Packet_Start_Caller{};

void Redirected_Packet_Start(void* Unknown_Parameter_1, void* Unknown_Parameter_2, __int32 Outgoing_Sequence_Number)
{
	Sequence_Structure* Sequence = &Sequences[Outgoing_Sequence_Number % 90];

	if (Outgoing_Sequence_Number == Sequence->Network_Sequence_Number)
	{
		Original_Packet_Start_Caller.call<void>(Unknown_Parameter_1, Unknown_Parameter_2, Sequence->Prediction_Sequence_Number);
	}
	else
	{
		Original_Packet_Start_Caller.call<void>(Unknown_Parameter_1, Unknown_Parameter_2, Outgoing_Sequence_Number);
	}
}