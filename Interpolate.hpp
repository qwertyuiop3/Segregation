Redirection_Manager::Manager_Structure Interpolate_Manager;

__int8 Redirected_Interpolate(void* Entity, void* Unknown_Parameter)
{
	if (Entity == Get_Local_Player())
	{
		return (decltype(&Redirected_Interpolate)(Interpolate_Manager.Caller))(Entity, Unknown_Parameter);
	}

	return 1;
}