__int8 Compute_Torso_Rotation(void* Animation_State, void* Studio_Header)
{
	if (Interface_Bruteforce.Get_Integer() == 1)
	{
		void* Local_Player = Get_Local_Player();

		if (*(void**)Animation_State == **(void***)((unsigned __int64)Local_Player + 13768))
		{
			void* Entity = *(void**)((unsigned __int64)Animation_State + 48);

			if (Entity != Local_Player)
			{
				Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int64)Entity + 136)];

				if (Player_Data->Priority != -2)
				{
					using Set_Pose_Parameter_Type = void(*)(void* Entity, void* Studio_Header, __int32 Parameter, float Value);

					static void* Set_Pose_Parameter = Byte_Manager::Find_Bytes(1007, (unsigned __int8*)Client_Module, 12382850545958547287ull);

					if (*(float*)((unsigned __int64)Animation_State + 140) == 180.f)
					{
						Set_Pose_Parameter_Type((unsigned __int64)Set_Pose_Parameter)(Entity, Studio_Header, *(__int32*)((unsigned __int64)Animation_State + 80), Player_Data->Switch_X == 0 ? 90.f : -90.f);
					}

					if (Player_Data->Memory_Tolerance == 0)
					{
						*(float*)((unsigned __int64)Animation_State + 60) = *(float*)((unsigned __int64)Animation_State + 136) - Bruteforce_Angles[Player_Data->Shots_Fired];
					}
					else
					{
						*(float*)((unsigned __int64)Animation_State + 60) = *(float*)((unsigned __int64)Animation_State + 136) - Player_Data->Memorized_Y;
					}

					Set_Pose_Parameter_Type((unsigned __int64)Set_Pose_Parameter)(Entity, Studio_Header, *(__int32*)((unsigned __int64)Animation_State + 76), __builtin_remainderf(*(float*)((unsigned __int64)Animation_State + 136) - *(float*)((unsigned __int64)Animation_State + 60), 360.f));

					return 1;
				}
			}
		}
	}

	return 0;
}

Redirection_Manager::Manager_Structure Compute_Torso_Rotation_Manager;

void Redirected_Compute_Torso_Rotation(void* Animation_State, void* Studio_Header)
{
	if (Compute_Torso_Rotation(Animation_State, Studio_Header) == 0)
	{
		(decltype(&Redirected_Compute_Torso_Rotation)(Compute_Torso_Rotation_Manager.Caller))(Animation_State, Studio_Header);
	}
}