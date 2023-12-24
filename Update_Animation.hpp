float Update_Animation_Angles[2];

void* Original_Update_Animation_Caller;

void __thiscall Redirected_Update_Animation(void* Player)
{
	if (Player == *(void**)((unsigned __int32)Client_Module + 5015784))
	{
		Byte_Manager::Copy_Bytes(0, (void*)((unsigned __int32)Player + 5276), sizeof(Update_Animation_Angles), Update_Animation_Angles);
	}

	(decltype(&Redirected_Update_Animation)(Original_Update_Animation_Caller))(Player);
}