struct Sequence_Structure
{
	__int32 Last_Sequence_Number;

	__int32 First_Sequence_Number;
};

Sequence_Structure Sequences[90];

void* Original_Write_Events_Caller;

void __thiscall Redirected_Write_Events(void* Unknown_Parameter_1, void* Unknown_Parameter_2)
{
	Byte_Manager::Set_Bytes(0, Players_Data, sizeof(Players_Data), 0);

	Bruteforce_Reset_Tolerance();

	Recent_Player_Data_Number = 0;

	Byte_Manager::Set_Bytes(0, Sequences, sizeof(Sequences), 0);

	(decltype(&Redirected_Write_Events)(Original_Write_Events_Caller))(Unknown_Parameter_1, Unknown_Parameter_2);
}