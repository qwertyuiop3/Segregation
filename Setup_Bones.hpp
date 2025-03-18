void* Original_Setup_Bones_Caller;

__int8 __thiscall Redirected_Setup_Bones(void* Entity, void* Bones, __int32 Maximum_Bones, __int32 Mask, float Current_Time)
{
	if (Update_Animation_Type != 2)
	{
		if ((void*)((unsigned __int32)Entity - 4) == *(void**)((unsigned __int32)Client_Module + 82926756))
		{
			*(float*)((unsigned __int32)Entity + 192) = 0.f;

			__int32 Entity_Number = *(__int32*)((unsigned __int32)Entity + 96);

			*(float*)((unsigned __int32)Entity + 196) = Animation_Angle[Entity_Number];

			*(float*)((unsigned __int32)Entity + 200) = 0.f;

			Byte_Manager::Copy_Bytes(1, (void*)((unsigned __int32)Entity + 10080), sizeof(Pose_Parameters[0]), Pose_Parameters[Entity_Number]);

			Byte_Manager::Copy_Bytes(1, *(void**)((unsigned __int32)Entity + 10604), sizeof(Animation_Layers[0]), Animation_Layers[Entity_Number]);
		}
	}

	return (decltype(&Redirected_Setup_Bones)(Original_Setup_Bones_Caller))(Entity, Bones, Maximum_Bones, Mask, Current_Time);
}