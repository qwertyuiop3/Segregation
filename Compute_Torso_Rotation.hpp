void* Original_Compute_Torso_Rotation_Caller_Location;

void __thiscall Redirected_Compute_Torso_Rotation(void* Animation_State)
{
	if (Interface_Bruteforce.Integer == 1)
	{
		void* Entity = *(void**)((unsigned __int32)Animation_State + 20);

		if (Entity != *(void**)((unsigned __int32)Client_Module_Location + 5015784))
		{
			if (*(void**)Entity == (void*)((unsigned __int32)Client_Module_Location + 3952404))
			{
				Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int32)Entity + 84)];

				if (Player_Data->Priority != -2)
				{
					using Set_Pose_Parameter_Type = float(__thiscall*)(void* Entity, void* Studio_Header, __int32 Parameter, float Value);

					using Get_Studio_Header_Type = void* (__thiscall*)(void* Entity);

					void* Studio_Header = Get_Studio_Header_Type(((unsigned __int32)Client_Module_Location + 541120))(Entity);

					if (*(float*)((unsigned __int32)Animation_State + 28) == -179.91206f)
					{
						Set_Pose_Parameter_Type((unsigned __int32)Client_Module_Location + 559920)(Entity, Studio_Header, 1, Player_Data->Switch_X == 0 ? 90 : -90);
					}

					if (Player_Data->Memory_Tolerance == 0)
					{
						*(float*)((unsigned __int32)Animation_State + 64) = *(float*)((unsigned __int32)Animation_State + 24) - Bruteforce_Angles[Player_Data->Shots_Fired];
					}
					else
					{
						*(float*)((unsigned __int32)Animation_State + 64) = *(float*)((unsigned __int32)Animation_State + 24) - Player_Data->Memorized_Y;
					}

					Set_Pose_Parameter_Type((unsigned __int32)Client_Module_Location + 559920)(Entity, Studio_Header, 2, __builtin_remainderf(*(float*)((unsigned __int32)Animation_State + 24) - *(float*)((unsigned __int32)Animation_State + 64), 360));

					return;
				}
			}
		}
	}

	if (__builtin_return_address(0) == (void*)((unsigned __int32)Client_Module_Location + 384578))
	{
		(decltype(&Redirected_Compute_Torso_Rotation)(Original_Compute_Torso_Rotation_Caller_Location))(Animation_State);
	}
}