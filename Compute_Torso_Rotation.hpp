SafetyHookInline Original_Compute_Torso_Rotation_Caller{};

__int8 Compute_Custom_Torso_Rotation(void* Animation_State, void* Studio_Header)
{
	if (Interface_Bruteforce.Get_Integer() == 1)
	{
		if (*(void**)Animation_State == (void*)((unsigned __int64)Client_Module + 7364104))
		{
			void* Entity = *(void**)((unsigned __int64)Animation_State + 304);

			if (Entity != *(void**)((unsigned __int64)Client_Module + 9394464))
			{
				Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int64)Entity + 128)];

				if (Player_Data->Priority != -2)
				{
					using Set_Pose_Parameter_Type = float(*)(void* Entity, void* Studio_Header, __int32 Parameter, float Value);

					if (*(float*)((unsigned __int64)Animation_State + 144) == 180.f)
					{
						Set_Pose_Parameter_Type((unsigned __int64)Client_Module + 1673728)(Entity, Studio_Header, *(__int32*)((unsigned __int64)Animation_State + 84), Player_Data->Switch_X == 0 ? 90.f : -90.f);
					}

					if (Player_Data->Memory_Tolerance == 0)
					{
						*(float*)((unsigned __int64)Animation_State + 60) = *(float*)((unsigned __int64)Animation_State + 140) - Bruteforce_Angles[Player_Data->Shots_Fired];
					}
					else
					{
						*(float*)((unsigned __int64)Animation_State + 60) = *(float*)((unsigned __int64)Animation_State + 140) - Player_Data->Memorized_Y;
					}

					Set_Pose_Parameter_Type((unsigned __int64)Client_Module + 1673728)(Entity, Studio_Header, *(__int32*)((unsigned __int64)Animation_State + 80), __builtin_remainderf(*(float*)((unsigned __int64)Animation_State + 140) - *(float*)((unsigned __int64)Animation_State + 60), 360.f));

					return 1;
				}
			}
		}
	}
	
	return 0;
}

void Redirected_Compute_Torso_Rotation(void* Animation_State, void* Studio_Header)
{
	if (Compute_Custom_Torso_Rotation(Animation_State, Studio_Header) == 0)
	{
		Original_Compute_Torso_Rotation_Caller.call<void>(Animation_State, Studio_Header);
	}
}