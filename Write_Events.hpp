__int32 Sequences[90];

void* Original_Write_Events_Caller;

void __thiscall Redirected_Write_Events(void* Unknown_Parameter_1, void* Unknown_Parameter_2)
{
	Byte_Manager::Set_Bytes(1, Players_Data, sizeof(Players_Data), 0);

	Bruteforce_Reset_Tolerance();

	Recent_Player_Data_Number = 0;

	Byte_Manager::Set_Bytes(1, Sequences, sizeof(Sequences), 0);

	(decltype(&Redirected_Write_Events)(Original_Write_Events_Caller))(Unknown_Parameter_1, Unknown_Parameter_2);
}