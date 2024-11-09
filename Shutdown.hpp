Redirection_Manager::Manager_Structure Shutdown_Manager;

void Redirected_Shutdown(void* Unknown_Parameter, char* Reason)
{
	(decltype(&Redirected_Shutdown)(Shutdown_Manager.Caller))(Unknown_Parameter, (char*)"Segregation");
}