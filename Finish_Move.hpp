void* Original_Finish_Move_Caller;

void __thiscall Redirected_Finish_Move(void* Unknown_Parameter_1, void* Player, void* Unknown_Parameter_2, void* Unknown_Parameter_3)
{
	(decltype(&Redirected_Finish_Move)(Original_Finish_Move_Caller))(Unknown_Parameter_1, Player, Unknown_Parameter_2, Unknown_Parameter_3);

	*(__int32*)((unsigned __int32)Player + 304) |= 4096;
}