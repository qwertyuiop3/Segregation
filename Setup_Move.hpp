void* Original_Setup_Move_Caller_Location;

void __thiscall Redirected_Setup_Move(void* Unknown_Parameter_1, void* Player, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4)
{
	Byte_Manager::Set_Bytes(0, (float*)((unsigned __int32)Player + 344), sizeof(float[3]), 0);

	(decltype(&Redirected_Setup_Move)(Original_Setup_Move_Caller_Location))(Unknown_Parameter_1, Player, Unknown_Parameter_2, Unknown_Parameter_3, Unknown_Parameter_4);
}