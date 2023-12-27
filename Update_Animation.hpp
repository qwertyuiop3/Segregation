float Update_Animation_Angles[2];

void* Original_Update_Animation_Caller;

void __thiscall Redirected_Update_Animation(void* Player)
{
	if (Player == *(void**)607867332)
	{
		Byte_Manager::Copy_Bytes(0, (void*)((unsigned __int32)Player + 4124), sizeof(Update_Animation_Angles), Update_Animation_Angles);
	}

	(decltype(&Redirected_Update_Animation)(Original_Update_Animation_Caller))(Player);
}