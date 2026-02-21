float Update_Animation_Angles[2];

__int8 Update_Animation_Type;

Redirection_Manager::Manager_Structure Update_Animation_Manager;

void Redirected_Update_Animation(void* Player)
{
	if (Player == *(void**)((unsigned __int64)Client_Module + 6245224))
	{
		Byte_Manager::Copy_Bytes(1, (void*)((unsigned __int64)Player + 6824), sizeof(Update_Animation_Angles), Update_Animation_Angles);
	}

	Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)((unsigned __int64)Client_Module + 5956224);

	float Previous_Frame_Time = Global_Variables->Frame_Time;

	Global_Variables->Frame_Time = Global_Variables->Interval_Per_Tick * Update_Animation_Type;

	*(float*)((unsigned __int64)Player + 160) = Global_Variables->Time - Global_Variables->Frame_Time;

	(decltype(&Redirected_Update_Animation)(Update_Animation_Manager.Caller))(Player);

	Global_Variables->Frame_Time = Previous_Frame_Time;
}