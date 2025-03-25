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

			Byte_Manager::Copy_Bytes(1, *(void**)((unsigned __int32)Entity + 10604), sizeof(Animation_Layers), Animation_Layers);
		}
		else
		{
			if (*(__int32*)((unsigned __int32)Entity + 10512) != *(__int32*)((unsigned __int32)Client_Module + 82621012))
			{
				*(__int32*)((unsigned __int32)Entity + 9852) = *(__int32*)((unsigned __int32)Client_Module + 83358788) - 1;

				*(__int32*)((unsigned __int32)Entity + 10512) = -8388609;
			}
		}
	}

	return (decltype(&Redirected_Setup_Bones)(Original_Setup_Bones_Caller))(Entity, Bones, Maximum_Bones, Mask, Current_Time);
}