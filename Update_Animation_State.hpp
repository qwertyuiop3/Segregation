float Update_Animation_Angles[2];

SafetyHookInline Original_Update_Animation_State_Caller{};

void Redirected_Update_Animation_State(void* Animation_State, float Eye_Yaw, float Eye_Pitch)
{
	if (*(void**)((unsigned __int64)Animation_State + 304) == *(void**)((unsigned __int64)Client_Module + 9394464))
	{
		Eye_Pitch = Update_Animation_Angles[0];

		Eye_Yaw = Update_Animation_Angles[1];
	}

	Original_Update_Animation_State_Caller.call<void>(Animation_State, Eye_Yaw, Eye_Pitch);
}