float Update_Animation_Time;

__int8 Update_Animation_Type;

Redirection_Manager::Manager_Structure Update_Animation_Manager;

void Redirected_Update_Animation(void* Player)
{
	Global_Variables_Structure* Global_Variables = Get_Global_Variables();

	float Previous_Current_Time = Global_Variables->Current_Time;

	Global_Variables->Current_Time = Update_Animation_Time;

	float Previous_Frame_Time = Global_Variables->Frame_Time;

	Global_Variables->Frame_Time = Global_Variables->Interval_Per_Tick * Update_Animation_Type;

	*(float*)((unsigned __int64)Player + 152) = Update_Animation_Time - Global_Variables->Frame_Time;

	(decltype(&Redirected_Update_Animation)(Update_Animation_Manager.Caller))(Player);

	Global_Variables->Frame_Time = Previous_Frame_Time;

	Global_Variables->Current_Time = Previous_Current_Time;
}