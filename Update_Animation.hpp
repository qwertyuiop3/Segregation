float Update_Animation_Time;

__int8 Update_Animation_Type;

SafetyHookInline Original_Update_Animation_Caller{};

void Redirected_Update_Animation(void* Player)
{
	Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)((unsigned __int64)Client_Module + 8690824);

	float Previous_Current_Time = Global_Variables->Current_Time;

	Global_Variables->Current_Time = Update_Animation_Time;

	float Previous_Frame_Time = Global_Variables->Frame_Time;

	Global_Variables->Frame_Time = Global_Variables->Interval_Per_Tick * Update_Animation_Type;

	*(float*)((unsigned __int64)Player + 152) = Update_Animation_Time - Global_Variables->Frame_Time;

	Original_Update_Animation_Caller.call<void>(Player);

	Global_Variables->Frame_Time = Previous_Frame_Time;

	Global_Variables->Current_Time = Previous_Current_Time;
}