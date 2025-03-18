void* Original_Item_Post_Frame_Caller;

void __thiscall Redirected_Item_Post_Frame(void* Unknown_Parameter)
{
	if (*(void**)((unsigned __int32)Engine_Module + 8406032) != nullptr)
	{
		(decltype(&Redirected_Item_Post_Frame)(Original_Item_Post_Frame_Caller))(Unknown_Parameter);
	}
}