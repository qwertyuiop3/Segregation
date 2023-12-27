void* Original_Item_Post_Frame_Caller;

void __thiscall Redirected_Item_Post_Frame(void* Unknown_Parameter)
{
	if (*(void**)((unsigned __int32)__builtin_frame_address(0) + 32) == (void*)604325657)
	{
		(decltype(&Redirected_Item_Post_Frame)(Original_Item_Post_Frame_Caller))(Unknown_Parameter);
	}
}