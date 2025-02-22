Redirection_Manager::Manager_Structure Item_Post_Frame_Manager;

void Redirected_Item_Post_Frame(void* Unknown_Parameter)
{
	if (*(void**)((unsigned __int64)__builtin_frame_address(0) + 152) == (void*)((unsigned __int64)Client_Module + 633300))
	{
		(decltype(&Redirected_Item_Post_Frame)(Item_Post_Frame_Manager.Caller))(Unknown_Parameter);
	}
}