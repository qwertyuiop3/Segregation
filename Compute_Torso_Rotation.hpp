Redirection_Manager::Manager_Structure Compute_Torso_Rotation_Manager;

void Redirected_Compute_Torso_Rotation(void* Animation_State)
{
	if (Interface_Bruteforce.Integer == 1)
	{
		void* Entity = *(void**)((unsigned __int64)Animation_State + 32);

		if (Entity != *(void**)((unsigned __int64)Client_Module + 6245224))
		{
			if (*(void**)Entity == (void*)((unsigned __int64)Client_Module + 4657304))
			{
				Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int64)Entity + 256)];

				if (Player_Data->Priority != -2)
				{
					using Set_Pose_Parameter_Type = float(*)(void* Entity, void* Studio_Header, __int32 Parameter, float Value);

					using Get_Studio_Header_Type = void*(*)(void* Entity);

					void* Studio_Header = Get_Studio_Header_Type((unsigned __int64)Client_Module + 479648)(Entity);

					if (*(float*)((unsigned __int64)Animation_State + 44) == -179.91206f)
					{
						Set_Pose_Parameter_Type((unsigned __int64)Client_Module + 504592)(Entity, Studio_Header, 1, Player_Data->Switch_X == 0 ? 90.f : -90.f);
					}

					if (Player_Data->Memory_Tolerance == 0)
					{
						*(float*)((unsigned __int64)Animation_State + 80) = *(float*)((unsigned __int64)Animation_State + 40) - Bruteforce_Angles[Player_Data->Shots_Fired];
					}
					else
					{
						*(float*)((unsigned __int64)Animation_State + 80) = *(float*)((unsigned __int64)Animation_State + 40) - Player_Data->Memorized_Y;
					}

					Set_Pose_Parameter_Type((unsigned __int64)Client_Module + 504592)(Entity, Studio_Header, 2, __builtin_remainderf(*(float*)((unsigned __int64)Animation_State + 40) - *(float*)((unsigned __int64)Animation_State + 80), 360.f));

					return;
				}
			}
		}
	}

	if (__builtin_return_address(0) == (void*)((unsigned __int64)Client_Module + 299907))
	{
		(decltype(&Redirected_Compute_Torso_Rotation)(Compute_Torso_Rotation_Manager.Caller))(Animation_State);
	}
}