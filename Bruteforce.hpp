void Bruteforce_Reset_Memory_Tolerance()
{
	__int32 Entity_Number = 0;

	Traverse_Players_Data_Label:
	{
		Player_Data_Structure* Player_Data = &Players_Data[Entity_Number];

		if (Player_Data->Memory_Tolerance != 0)
		{
			Player_Data->Memory_Tolerance = Interface_Bruteforce_Memory_Tolerance.Integer;
		}

		Entity_Number += 1;

		if (Entity_Number != sizeof(Players_Data) / sizeof(Player_Data_Structure))
		{
			goto Traverse_Players_Data_Label;
		}
	}
}

void Bruteforce_Reset_Tolerance()
{
	__int32 Entity_Number = 0;

	Traverse_Players_Data_Label:
	{
		Player_Data_Structure* Player_Data = &Players_Data[Entity_Number];

		if (Player_Data->Memory_Tolerance == 0)
		{
			Player_Data->Tolerance = Interface_Bruteforce_Tolerance.Integer;
		}

		Entity_Number += 1;

		if (Entity_Number != sizeof(Players_Data) / sizeof(Player_Data_Structure))
		{
			goto Traverse_Players_Data_Label;
		}
	}
}

void Bruteforce_Reset()
{
	__int32 Entity_Number = 0;

	Traverse_Players_Data_Label:
	{
		Player_Data_Structure* Player_Data = &Players_Data[Entity_Number];

		Player_Data->Memory_Tolerance = 0;

		Player_Data->Tolerance = Interface_Bruteforce_Tolerance.Integer;

		Player_Data->Shots_Fired = 0;

		Entity_Number += 1;

		if (Entity_Number != sizeof(Players_Data) / sizeof(Player_Data_Structure))
		{
			goto Traverse_Players_Data_Label;
		}
	}
}

__int8 Bruteforce_Angles_Count;

float* Bruteforce_Angles;

void Bruteforce_Set_Angles(Interface_Structure* Console_Variable)
{
	Bruteforce_Angles_Count = 1;

	Bruteforce_Angles = (float*)realloc(Bruteforce_Angles, Bruteforce_Angles_Count * sizeof(Bruteforce_Angles));

	Bruteforce_Angles[Bruteforce_Angles_Count - 1] = atof(Console_Variable->String);

	char* String = strchr(Console_Variable->String, ',');

	Set_Bruteforce_Angles_Label:
	{
		if (String != nullptr)
		{
			Bruteforce_Angles_Count += 1;

			Bruteforce_Angles = (float*)realloc(Bruteforce_Angles, Bruteforce_Angles_Count * sizeof(Bruteforce_Angles));

			String = (char*)((unsigned __int32)String + 1);

			Bruteforce_Angles[Bruteforce_Angles_Count - 1] = atof(String);

			String = strchr(String, ',');

			goto Set_Bruteforce_Angles_Label;
		}
	}

	Bruteforce_Reset();
}