void* Original_Compute_Torso_Rotation_Caller;

void __thiscall Redirected_Compute_Torso_Rotation(void* Animation_State)
{
	if (Interface_Bruteforce.Integer == 1)
	{
		void* Entity = *(void**)((unsigned __int32)Animation_State + 20);

		if (Entity != *(void**)607867332)
		{
			if (*(void**)Entity == (void*)607350148)
			{
				Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int32)Entity + 80)];

				if (Player_Data->Priority != -2)
				{
					using Set_Torso_Rotation_Type = float(__thiscall*)(void* Animation_State, float Rotation);

					if (Player_Data->Memory_Tolerance == 0)
					{
						*(float*)((unsigned __int32)Animation_State + 64) = *(float*)((unsigned __int32)Animation_State + 24) - Bruteforce_Angles[Player_Data->Shots_Fired];
					}
					else
					{
						*(float*)((unsigned __int32)Animation_State + 64) = *(float*)((unsigned __int32)Animation_State + 24) - Player_Data->Memorized_Y;
					}

					Set_Torso_Rotation_Type(604022992)(Animation_State, __builtin_remainderf(*(float*)((unsigned __int32)Animation_State + 24) - *(float*)((unsigned __int32)Animation_State + 64), 360));

					return;
				}
			}
		}
	}

	if (__builtin_return_address(0) == (void*)604026641)
	{
		(decltype(&Redirected_Compute_Torso_Rotation)(Original_Compute_Torso_Rotation_Caller))(Animation_State);
	}
}