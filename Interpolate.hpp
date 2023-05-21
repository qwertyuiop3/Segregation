void* Original_Interpolate_Caller_Location;

__int8 __thiscall Redirected_Interpolate(void* Entity, void* Unknown_Parameter)
{
	if (Entity != *(void**)607867332)
	{
		if (*(void**)Entity == (void*)607350148)
		{
			return 1;
		}
	}

	return (decltype(&Redirected_Interpolate)(Original_Interpolate_Caller_Location))(Entity, Unknown_Parameter);
}