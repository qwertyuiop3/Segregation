void* Original_Shutdown_Caller;

void __thiscall Redirected_Shutdown(void* Unknown_Parameter, char* Reason)
{
	(decltype(&Redirected_Shutdown)(Original_Shutdown_Caller))(Unknown_Parameter, (char*)"Segregation");
}