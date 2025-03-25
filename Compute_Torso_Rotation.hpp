void* Original_Compute_Torso_Rotation_Caller;

void __thiscall Redirected_Compute_Torso_Rotation(void* Animation_State)
{
	if (__builtin_return_address(0) == (void*)((unsigned __int32)Client_Module + 3882990))
	{
		(decltype(&Redirected_Compute_Torso_Rotation)(Original_Compute_Torso_Rotation_Caller))(Animation_State);
	}

	void* Entity = *(void**)((unsigned __int32)Animation_State + 96);

	if (Interface_Bruteforce.Get_Integer() == 1)
	{
		if (Entity != *(void**)((unsigned __int32)Client_Module + 82926756))
		{
			if (*(void**)Entity == (void*)((unsigned __int32)Client_Module + 9483064))
			{
				Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int32)Entity + 100)];

				if (Player_Data->Priority != -2)
				{
					using Set_Pose_Parameter_Type = void(__thiscall*)(void* Entity, char* Parameter, float Value);

					if (Interface_Bruteforce_Perpendicular.Get_Integer() != -1)
					{
						float Angles[3] = { 90.f, -90.f, *(float*)((unsigned __int32)Animation_State + 124) };

						Set_Pose_Parameter_Type((unsigned __int32)Client_Module + 1676480)(Entity, (char*)"body_pitch", Angles[Player_Data->Switch_X % max(1, 3 - Interface_Bruteforce_Perpendicular.Get_Integer())]);
					}

					if (Player_Data->Memory_Tolerance == 0)
					{
						Player_Data->Animation_Angle = *(float*)((unsigned __int32)Animation_State + 128) = *(float*)((unsigned __int32)Animation_State + 120) - Bruteforce_Angles[Player_Data->Shots_Fired];
					}
					else
					{
						Player_Data->Animation_Angle = *(float*)((unsigned __int32)Animation_State + 128) = *(float*)((unsigned __int32)Animation_State + 120) - Player_Data->Memorized_Y;
					}

					Set_Pose_Parameter_Type((unsigned __int32)Client_Module + 1676480)(Entity, (char*)"body_yaw", __builtin_remainderf(*(float*)((unsigned __int32)Animation_State + 120) - *(float*)((unsigned __int32)Animation_State + 128), 360.f) * Interface_Bruteforce_Relative.Get_Floating_Point());
				}
			}
		}
	}
}