void* Original_Compute_Move_Rotation_Caller;

void __thiscall Redirected_Compute_Move_Rotation(void* Animation_State, void* Unknown_Parameter)
{
	if (*(__int32*)((unsigned __int32)Animation_State + 12) != 1)
	{
		float* Rotation = (float*)((unsigned __int32)(*(void**)((unsigned __int32)Animation_State + 20)) + 680);

		Rotation[0] = 0.f;

		Rotation[1] = *(float*)((unsigned __int32)Animation_State + 36);

		Rotation[2] = 0.f;
	}

	(decltype(&Redirected_Compute_Move_Rotation)(Original_Compute_Move_Rotation_Caller))(Animation_State, Unknown_Parameter);
}