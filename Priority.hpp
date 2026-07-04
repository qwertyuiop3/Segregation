struct Global_Variables_Structure
{
	__int8 Additional_Bytes[16];

	float Time;

	float Frame_Time;

	__int32 Maximum_Clients;

	__int32 Tick_Number;

	float Interval_Per_Tick;
};

struct Player_Data_Structure
{
	__int32 Priority;

	__int8 Simulated;

	float Networked_Angle[2];

	__int32 Memory_Tolerance;

	__int32 Tolerance;

	__int32 Shots_Fired;

	__int32 Switch_X;

	float Memorized_Y;

	float Animation_Angle;
};

Player_Data_Structure Players_Data[65];

void Get_Priorities()
{
	__int32 Player_Number = 1;

	Traverse_Entity_List_Label:
	{
		using Get_Name_Type = void(__thiscall*)(void* Engine, __int32 Number, char* Name);

		char Name[344];

		Get_Name_Type((unsigned __int32)Engine_Module + 697648)((void*)((unsigned __int32)Engine_Module + 5749856), Player_Number, Name);

		if (Name[16] != 0)
		{
			wprintf(L"[ ? ] \"%hs\" %i %i\n", &Name[16], Player_Number, Players_Data[Player_Number].Priority);
		}

		if (Player_Number < (*(Global_Variables_Structure**)((unsigned __int32)Client_Module + 10871344))->Maximum_Clients)
		{
			Player_Number += 1;

			goto Traverse_Entity_List_Label;
		}
	}
}

void Set_Priority(Interface_Structure* Interface)
{
	Interface = (Interface_Structure*)((unsigned __int32)Interface - 24);

	__int32 Player_Number = atoi(Interface->String);

	Players_Data[Player_Number].Priority = atoi(__builtin_strchr(Interface->String, ' '));
}