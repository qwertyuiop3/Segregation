void* Original_Shutdown_Caller_Location;

void __thiscall Redirected_Shutdown(void* Unknown_Parameter, char* Reason)
{
	(decltype(&Redirected_Shutdown)(Original_Shutdown_Caller_Location))(Unknown_Parameter, (char*)"Segregation");
}