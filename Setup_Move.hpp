void* Original_Setup_Move_Caller;

void __thiscall Redirected_Setup_Move(void* Unknown_Parameter_1, void* Player, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4)
{
	*(float*)((unsigned __int32)Player + 268) = min(*(float*)((unsigned __int32)Player + 268) == 46.044968f ? 46.f : *(float*)((unsigned __int32)Player + 268), 64.f);

	Byte_Manager::Set_Bytes(1, (float*)((unsigned __int32)Player + 284), sizeof(float[3]), 0);

	(decltype(&Redirected_Setup_Move)(Original_Setup_Move_Caller))(Unknown_Parameter_1, Player, Unknown_Parameter_2, Unknown_Parameter_3, Unknown_Parameter_4);
}