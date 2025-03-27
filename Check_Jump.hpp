void* Original_Check_Jump_Caller;

__int8 __thiscall Redirected_Check_Jump(void* Unknown_Parameter)
{
	if ((decltype(&Redirected_Check_Jump)(Original_Check_Jump_Caller))(Unknown_Parameter) == 0)
	{
		return 0;
	}

	if (*(void**)((unsigned __int32)Engine_Module + 8406032) == nullptr)
	{
		Animation_Layers[4].Weight = 0.f;

		Animation_Layers[4].Cycle = 0.f;
	}

	return 1;
}