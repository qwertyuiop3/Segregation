__int32 Sequences[90];

Redirection_Manager::Manager_Structure Write_Events_Manager;

void Redirected_Write_Events(void* Unknown_Parameter_1, void* Unknown_Parameter_2)
{
	static void* State = Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(1073539, (unsigned __int8*)Engine_Module, 14964054701647811381ull), 2);

	if (*(__int32*)State != 6)
	{
		__int32 Player_Number = 0;

		Traverse_Players_Data_Label:
		{
			Player_Data_Structure* Player_Data = &Players_Data[Player_Number];

			Player_Data->Modifications_Data.clear();

			Player_Data->Priority = 0;

			Player_Data->Memory_Tolerance = 0;

			Player_Data->Tolerance = Interface_Bruteforce_Tolerance.Get_Integer();

			Player_Data->Shots_Fired = 0;

			Player_Data->Switch_X = 0;

			Player_Number += 1;

			if (Player_Number != sizeof(Players_Data) / sizeof(Player_Data_Structure))
			{
				goto Traverse_Players_Data_Label;
			}
		}

		Recent_Player_Data_Number = 0;

		Byte_Manager::Set_Bytes(1, Sequences, sizeof(Sequences), 0);
	}

	(decltype(&Redirected_Write_Events)(Write_Events_Manager.Caller))(Unknown_Parameter_1, Unknown_Parameter_2);
}