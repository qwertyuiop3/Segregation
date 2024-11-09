Redirection_Manager::Manager_Structure Setup_Move_Manager;

void Redirected_Setup_Move(void* Unknown_Parameter_1, void* Player, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4)
{
	Byte_Manager::Set_Bytes(1, (float*)((unsigned __int64)Player + 464), sizeof(float[3]), 0);

	Setup_Move_Manager.Special_Call(Unknown_Parameter_1, Player, Unknown_Parameter_2, Unknown_Parameter_3, Unknown_Parameter_4);
}