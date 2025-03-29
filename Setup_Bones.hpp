void* Original_Setup_Bones_Caller;

__int8 __thiscall Redirected_Setup_Bones(void* Entity, void* Bones, __int32 Maximum_Bones, __int32 Mask, float Current_Time)
{
	if (*(void**)Entity == (void*)((unsigned __int32)Client_Module + 9482876))
	{
		*(float*)((unsigned __int32)Entity + 192) = 0.f;

		*(float*)((unsigned __int32)Entity + 196) = Players_Data[*(__int32*)((unsigned __int32)Entity + 96)].Animation_Angle;

		*(float*)((unsigned __int32)Entity + 200) = 0.f;

		if ((void*)((unsigned __int32)Entity - 4) == *(void**)((unsigned __int32)Client_Module + 82926756))
		{
			Byte_Manager::Copy_Bytes(1, (void*)((unsigned __int32)Entity + 10080), sizeof(Pose_Parameters), Pose_Parameters);

			__int32 Layer_Number = 0;

			Animation_Layer_Structure* Frame_Animation_Layers = *(Animation_Layer_Structure**)((unsigned __int32)Entity + 10604);

			Traverse_Layers_Label:
			{
				Animation_Layers[Layer_Number].Sequence = Frame_Animation_Layers[Layer_Number].Sequence;
				
				Layer_Number += 1;

				if (Layer_Number != sizeof(Animation_Layers) / sizeof(Animation_Layer_Structure))
				{
					goto Traverse_Layers_Label;
				}
			}

			Byte_Manager::Copy_Bytes(1, Frame_Animation_Layers, sizeof(Animation_Layers), Animation_Layers);
		}
		else
		{
			if (*(void**)((unsigned __int32)__builtin_frame_address(0) + 52) == (void*)((unsigned __int32)Client_Module + 1683349))
			{
				if (*(__int32*)((unsigned __int32)__builtin_frame_address(0) + 72) == 6)
				{
					*(__int32*)((unsigned __int32)Entity + 9852) = *(__int32*)((unsigned __int32)Client_Module + 83358788) - 1;

					*(__int32*)((unsigned __int32)Entity + 10512) = -8388609;
				}
			}
		}
	}

	return (decltype(&Redirected_Setup_Bones)(Original_Setup_Bones_Caller))(Entity, Bones, Maximum_Bones, Mask, Current_Time);
}