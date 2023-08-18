void* Original_Packet_End_Caller_Location;

void __thiscall Redirected_Packet_End(void* Network_Channel)
{
	decltype(Sequences)::iterator Sequence = Sequences.begin();

	__int32 Packet_Sequence = *(__int32*)((unsigned __int32)Network_Channel + 18984);

	Traverse_Sequences_Label:
	{
		if (Sequence != Sequences.end())
		{
			if (*(__int32*)Sequence._Unwrapped() == Packet_Sequence)
			{
				(decltype(&Redirected_Packet_End)(Original_Packet_End_Caller_Location))(Network_Channel);
			}

			if (*(__int32*)Sequence._Unwrapped() < Packet_Sequence)
			{
				Sequence = Sequences.erase(Sequence);
			}
			else
			{
				Sequence += 1;
			}

			goto Traverse_Sequences_Label;
		}
	}
}