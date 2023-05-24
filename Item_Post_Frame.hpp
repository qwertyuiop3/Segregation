void* Original_Item_Post_Frame_Caller_Location;

void __thiscall Redirected_Item_Post_Frame(void* Player)
{
	if (*(void**)((unsigned __int32)__builtin_frame_address(0) + 40) == (void*)((unsigned __int32)Client_Module_Location + 668170))
	{
		(decltype(&Redirected_Item_Post_Frame)(Original_Item_Post_Frame_Caller_Location))(Player);
	}
}