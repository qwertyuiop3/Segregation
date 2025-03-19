void* Original_Setup_Bones_Caller;

__int8 __thiscall Redirected_Setup_Bones(void* Entity, void* Bones, __int32 Maximum_Bones, __int32 Mask, float Current_Time)
{
	if (*(void**)Entity == (void*)((unsigned __int32)Client_Module + 9482876 - Update_Animation_Type))
	{
		*(float*)((unsigned __int32)Entity + 192) = 0.f;

		*(float*)((unsigned __int32)Entity + 196) = Animation_Angle[*(__int32*)((unsigned __int32)Entity + 96)];

		*(float*)((unsigned __int32)Entity + 200) = 0.f;

		if ((void*)((unsigned __int32)Entity - 4) == *(void**)((unsigned __int32)Client_Module + 82926756))
		{
			Byte_Manager::Copy_Bytes(1, (void*)((unsigned __int32)Entity + 10080), sizeof(Pose_Parameters), Pose_Parameters);

			Byte_Manager::Copy_Bytes(1, *(void**)((unsigned __int32)Entity + 10604), sizeof(Animation_Layers), Animation_Layers);
		}
	}

	return (decltype(&Redirected_Setup_Bones)(Original_Setup_Bones_Caller))(Entity, Bones, Maximum_Bones, Mask, Current_Time);
}