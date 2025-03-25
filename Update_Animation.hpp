__int8 Update_Animation_Type;

void* Original_Update_Animation_Caller;

__int32 Update_Animation_Delta[2];

float Pose_Parameters[24];

float Animation_Layers[210];

void __thiscall Redirected_Update_Animation(void* Player)
{
	*(__int8*)((unsigned __int32)Player + 14817) = Update_Animation_Type;

	if (*(__int8*)((unsigned __int32)Player + 14817) == 0)
	{
		(decltype(&Redirected_Update_Animation)(Original_Update_Animation_Caller))(Player);
	}
	else
	{
		if (Player == *(void**)((unsigned __int32)Client_Module + 82926756))
		{
			if (Update_Animation_Type == 1)
			{
				return;
			}
		}

		Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)((unsigned __int32)Client_Module + 10871344);

		*(float*)(*(unsigned __int32*)((unsigned __int32)Player + 14452) + 108) = Global_Variables->Current_Time - Global_Variables->Interval_Per_Tick * max(1, Update_Animation_Delta[Update_Animation_Type - 1]);

		(decltype(&Redirected_Update_Animation)(Original_Update_Animation_Caller))(Player);

		Players_Data[*(__int32*)((unsigned __int32)Player + 100)].Animation_Angle = *(float*)((unsigned __int32)Player + 200);

		if (Update_Animation_Type == 2)
		{
			Byte_Manager::Copy_Bytes(1, Pose_Parameters, sizeof(Pose_Parameters), (void*)((unsigned __int32)Player + 10084));

			Byte_Manager::Copy_Bytes(1, Animation_Layers, sizeof(Animation_Layers), *(void**)((unsigned __int32)Player + 10608));
		}
	}

	*(__int8*)((unsigned __int32)Player + 14817) = 1;
}