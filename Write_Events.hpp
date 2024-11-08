struct Sequence_Structure
{
	__int32 Network_Sequence_Number;

	__int32 Prediction_Sequence_Number;
};

Sequence_Structure Sequences[90];

Redirection_Manager::Manager_Structure Write_Events_Manager;

void Redirected_Write_Events(void* Unknown_Parameter_1, void* Unknown_Parameter_2)
{
	static void* State = Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(1073539, (unsigned __int8*)Engine_Module, 14964054701647811381ull), 2);

	if (*(__int32*)State != 6)
	{
		Byte_Manager::Set_Bytes(1, Players_Data, sizeof(Players_Data), 0);

		Bruteforce_Reset_Tolerance();

		Recent_Player_Data_Number = 0;

		Byte_Manager::Set_Bytes(1, Sequences, sizeof(Sequences), 0);
	}

	(decltype(&Redirected_Write_Events)(Write_Events_Manager.Caller))(Unknown_Parameter_1, Unknown_Parameter_2);
}