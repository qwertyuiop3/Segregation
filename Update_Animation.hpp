__int8 Update_Animation_Type;

Redirection_Manager::Manager_Structure Update_Animation_Manager;

void Save_Player_Data(void* Data, void* Player, std::vector<Player_Data_Structure::Modification_Structure> Modifications_Data, void* Animations_Data)
{
	Byte_Manager::Copy_Bytes(1, (void*)((unsigned __int64)Data + 1), sizeof(Player_Data_Structure::Data) - 1, (void*)((unsigned __int64)Player + 1));

	Modifications_Data.clear();

	void* Modification_Table = *(void**)((unsigned __int64)Player + 5688);

	Player_Data_Structure::Modification_Structure* Modifications = (Player_Data_Structure::Modification_Structure*)(*(unsigned __int64*)((unsigned __int64)Modification_Table + 16) + 24);

	Modifications_Data.insert(Modifications_Data.end(), Modifications, &Modifications[*(__int16*)((unsigned __int64)Modification_Table + 38) + 1]);

	Byte_Manager::Copy_Bytes(1, Animations_Data, sizeof(Player_Data_Structure::Animations_Data), *(void**)((unsigned __int64)Player + 13768));
}

void Redirected_Update_Animation(void* Player)
{
	Global_Variables_Structure* Global_Variables = Get_Global_Variables();

	float Previous_Frame_Time = Global_Variables->Frame_Time;

	Global_Variables->Frame_Time = Global_Variables->Interval_Per_Tick * Update_Animation_Type;

	*(double*)((unsigned __int64)Player + 160) = Global_Variables->Time - Global_Variables->Frame_Time;

	(decltype(&Redirected_Update_Animation)(Update_Animation_Manager.Caller))(Player);

	Global_Variables->Frame_Time = Previous_Frame_Time;

	Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int64)Player + 136)];

	if (Player_Data->Data[0] == 1)
	{
		Player_Data->Data[0] = 0;

		Save_Player_Data(Player_Data->Data, Player, Player_Data->Modifications_Data, Player_Data->Animations_Data);
	}
}