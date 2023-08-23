void* Original_Interpolate_Caller;

__int8 __thiscall Redirected_Interpolate(void* Entity, void* Unknown_Parameter)
{
	if (Entity != *(void**)((unsigned __int32)Client_Module + 5015784))
	{
		if (*(void**)Entity == (void*)((unsigned __int32)Client_Module + 3952404))
		{
			return 1;
		}
	}

	return (decltype(&Redirected_Interpolate)(Original_Interpolate_Caller))(Entity, Unknown_Parameter);
}