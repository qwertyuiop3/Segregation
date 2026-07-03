__int8 Update_Animation_Type;

Redirection_Manager::Manager_Structure Update_Animation_Manager;

void Redirected_Update_Animation(void* Player)
{
	Global_Variables_Structure* Global_Variables = Get_Global_Variables();

	float Previous_Frame_Time = Global_Variables->Frame_Time;

	Global_Variables->Frame_Time = Global_Variables->Interval_Per_Tick * Update_Animation_Type;

	*(double*)((unsigned __int64)Player + 160) = Global_Variables->Time - Global_Variables->Frame_Time;

	(decltype(&Redirected_Update_Animation)(Update_Animation_Manager.Caller))(Player);

	Global_Variables->Frame_Time = Previous_Frame_Time;

	Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int64)Player + 136)];

	if (Player_Data->Data[6148] == -1)
	{
		Byte_Manager::Copy_Bytes(1, Player_Data->Data, sizeof(Player_Data->Data), Player);

		Byte_Manager::Copy_Bytes(1, Player_Data->Animation_State, sizeof(Player_Data->Animation_State), *(void**)((unsigned __int64)Player + 13768));
	}
}