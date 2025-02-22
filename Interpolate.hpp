Redirection_Manager::Manager_Structure Interpolate_Manager;

__int8 Redirected_Interpolate(void* Entity, void* Unknown_Parameter)
{
	if (Entity == *(void**)((unsigned __int64)Client_Module + 6245224))
	{
		return (decltype(&Redirected_Interpolate)(Interpolate_Manager.Caller))(Entity, Unknown_Parameter);
	}

	return 1;
}