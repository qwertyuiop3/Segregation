void* Original_Reset_Animation_State_Caller;

void __thiscall Redirected_Reset_Animation_State(void* Animation_State)
{
	if (*(void**)((unsigned __int32)Animation_State + 96) == *(void**)((unsigned __int32)Client_Module + 82926756))
	{
		Byte_Manager::Set_Bytes(1, Animation_Layers, sizeof(Animation_Layers), 0);
	}

	(decltype(&Redirected_Reset_Animation_State)(Original_Reset_Animation_State_Caller))(Animation_State);
}