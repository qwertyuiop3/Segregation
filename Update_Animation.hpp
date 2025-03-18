__int8 Update_Animation_Type;

void* Original_Update_Animation_Caller;

float Animation_Angle[65];

float Pose_Parameters[65][24];

float Animation_Layers[65][210];

void __thiscall Redirected_Update_Animation(void* Player)
{
	if (Update_Animation_Type != 0)
	{
		if (Player == *(void**)((unsigned __int32)Client_Module + 82926756))
		{
			if (Update_Animation_Type != 2)
			{
				return;
			}
		}

		*(__int8*)((unsigned __int32)Player + 14817) = 1;

		*(__int32*)(*(unsigned __int32*)((unsigned __int32)Player + 14452) + 112) = (*(Global_Variables_Structure**)((unsigned __int32)Client_Module + 10871344))->Frame + 1;

		(decltype(&Redirected_Update_Animation)(Original_Update_Animation_Caller))(Player);

		__int32 Entity_Number = *(__int32*)((unsigned __int32)Player + 100);

		Animation_Angle[Entity_Number] = *(float*)((unsigned __int32)Player + 200);

		Byte_Manager::Copy_Bytes(1, Pose_Parameters[Entity_Number], sizeof(Pose_Parameters[0]), (void*)((unsigned __int32)Player + 10084));

		Byte_Manager::Copy_Bytes(1, Animation_Layers[Entity_Number], sizeof(Animation_Layers[0]), *(void**)((unsigned __int32)Player + 10608));
	}
}