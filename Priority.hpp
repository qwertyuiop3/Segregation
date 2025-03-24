struct Global_Variables_Structure
{
	__int8 Additional_Bytes[16];

	float Current_Time;

	float Frame_Time;

	__int32 Maximum_Clients;

	__int32 Tick_Number;

	float Interval_Per_Tick;
};

struct Player_Data_Structure
{
	__int32 Priority;

	__int8 Simulated;

	float Angle;

	__int32 Memory_Tolerance;

	__int32 Tolerance;

	__int32 Shots_Fired;

	unsigned __int8 Switch_X;

	float Memorized_Y;
};

Player_Data_Structure Players_Data[65];

void Get_Priorities()
{
	__int32 Entity_Number = 1;

	Traverse_Entity_List_Label:
	{
		using Get_Name_Type = void(__thiscall*)(void* Engine, __int32 Number, char* Name);

		char Name[344];

		Get_Name_Type((unsigned __int32)Engine_Module + 697648)((void*)((unsigned __int32)Engine_Module + 5749856), Entity_Number, Name);

		if (Name[16] != 0)
		{
			wprintf(L"[ ? ] \"%hs\" %i %i\n", &Name[16], Entity_Number, Players_Data[Entity_Number].Priority);
		}

		if (Entity_Number < (*(Global_Variables_Structure**)((unsigned __int32)Client_Module + 10871344))->Maximum_Clients)
		{
			Entity_Number += 1;

			goto Traverse_Entity_List_Label;
		}
	}
}

void Set_Priority(Interface_Structure* Interface)
{
	Interface = (Interface_Structure*)((unsigned __int32)Interface - 24);

	__int32 Entity_Number = atoi(Interface->String);

	Players_Data[Entity_Number].Priority = atoi(__builtin_strchr(Interface->String, ' '));
}