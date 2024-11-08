SafetyHookInline Original_Shutdown_Caller{};

void Redirected_Shutdown(void* Unknown_Parameter, char* Reason)
{
	Original_Shutdown_Caller.call<void>(Unknown_Parameter, (char*)"Segregation");
}