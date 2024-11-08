Redirection_Manager::Manager_Structure Interpolate_Manager;

__int8 Redirected_Interpolate(void* Entity, void* Unknown_Parameter)
{
	if (Entity == *(void**)((unsigned __int64)Client_Module + 9394464))
	{
		(decltype(&Redirected_Interpolate)(Interpolate_Manager.Caller))(Entity, Unknown_Parameter);
	}

	return 1;
}