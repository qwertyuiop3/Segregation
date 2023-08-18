std::vector<__int32> Sequences;

void* Original_Write_Events_Caller_Location;

void __thiscall Redirected_Write_Events(void* Unknown_Parameter_1, void* Unknown_Parameter_2)
{
	if (*(__int32*)((unsigned __int32)Engine_Module_Location + 4684008) == 5)
	{
		Byte_Manager::Set_Bytes(0, Players_Data, sizeof(Players_Data), 0);

		Bruteforce_Reset_Tolerance();

		Recent_Player_Data_Number = 0;

		Sequences.clear();
	}

	(decltype(&Redirected_Write_Events)(Original_Write_Events_Caller_Location))(Unknown_Parameter_1, Unknown_Parameter_2);
}