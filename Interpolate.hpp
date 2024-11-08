SafetyHookInline Original_Interpolate_Caller{};

__int8 Redirected_Interpolate(void* Entity, void* Unknown_Parameter)
{
	if (Entity == *(void**)((unsigned __int64)Client_Module + 9394464))
	{
		return Original_Interpolate_Caller.call<__int8>(Entity, Unknown_Parameter);
	}

	return 1;
}