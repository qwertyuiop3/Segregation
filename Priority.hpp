void* Get_Engine()
{
	static void* Engine = Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(136933539719, (unsigned __int8*)Engine_Module, 16409920955244565394ull), 3);

	return Engine;
}

struct Global_Variables_Structure
{
	__int8 Additional_Bytes[12];

	float Current_Time;

	float Frame_Time;

	__int32 Maximum_Clients;

	__int32 Tick_Number;

	float Interval_Per_Tick;
};

Global_Variables_Structure* Get_Global_Variables()
{
	static void* Global_Variables = Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(7617415, (unsigned __int8*)Client_Module, 6990183020127034944), 3);

	return *(Global_Variables_Structure**)Global_Variables;
}

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

		static void* Get_Name = Byte_Manager::Find_Bytes(223, (unsigned __int8*)Client_Module, 3955253202869131490);

		char Name[324];

		Get_Name_Type((unsigned __int64)Get_Name)(Get_Engine(), Entity_Number, Name);

		if (Name[0] != 0)
		{
			wprintf(L"[ ? ] \"%hs\" %i %i\n", Name, Entity_Number, Players_Data[Entity_Number].Priority);
		}

		if (Entity_Number < Get_Global_Variables()->Maximum_Clients)
		{
			Entity_Number += 1;

			goto Traverse_Entity_List_Label;
		}
	}
}

void Set_Priority(Interface_Structure* Interface)
{
	Interface = (Interface_Structure*)((unsigned __int64)Interface - 48);

	__int32 Entity_Number = atoi(Interface->String);

	Players_Data[Entity_Number].Priority = atoi((char*)((unsigned __int64)Interface->String + 4 - (Entity_Number < 10) - (Entity_Number < 100)));
}