struct Global_Variables_Structure
{
	__int8 Additional_Bytes[12];

	float Current_Time;

	float Frame_Time;

	__int32 Maximum_Clients;

	__int32 Tick_Number;

	float Interval_Per_Tick;
};

struct Player_Data_Structure
{
	__int8 Breaks_Lag_Compensation;
	
	__int32 Simulation_Ticks[2];
	
	__int32 Last_Update_Tick_Number[2];
	
	float Last_Update_Origin[3];
	
	__int32 Priority;

	__int32 Memory_Tolerance;

	__int32 Tolerance;

	__int32 Shots_Fired;

	__int8 Switch_X;

	float Memorized_Y;
};

Player_Data_Structure Players_Data[129];

void Get_Priorities()
{
	__int32 Entity_Number = 1;

	Traverse_Entity_List_Label:
	{
		using Get_Name_Type = __int8(*)(void* Engine, __int32 Number, char* Name);

		char Name[324];

		Get_Name_Type((unsigned __int64)Engine_Module + 491536)((void*)((unsigned __int64)Engine_Module + 4670832), Entity_Number, Name);

		if (Name[0] != 0)
		{
			wprintf(L"[ ? ] \"%hs\" %i %i\n", Name, Entity_Number, Players_Data[Entity_Number].Priority);
		}

		if (Entity_Number < (*(Global_Variables_Structure**)((unsigned __int64)Client_Module + 8690824))->Maximum_Clients)
		{
			Entity_Number += 1;

			goto Traverse_Entity_List_Label;
		}
	}
}

void Set_Priority(Interface_Structure* Interface)
{
	Interface = (Interface_Structure*)((unsigned __int64)Interface - 48);

	__int32 Player_Number = atoi(Interface->String);

	Players_Data[Player_Number].Priority = atoi((char*)((unsigned __int64)Interface->String + 4 - (Player_Number < 10) - (Player_Number < 100)));
}