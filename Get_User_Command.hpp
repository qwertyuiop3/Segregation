void* Original_Get_User_Command_Caller_Location;

void* __thiscall Redirected_Get_User_Command(void* Unknown_Parameter, __int32 Command_Number)
{
	/*
	if (__builtin_return_address(0) == (void*)0x2412C305)
	{
		__int32 start = *(__int32*)((unsigned __int32)__builtin_frame_address(0) + 0x14);
		__int32 current_frame = Command_Number - start - 1;
		__int32 end = *(__int32*)((unsigned __int32)__builtin_frame_address(0) + 0x30);
		using RestoreEntityToPredictedFrame = void(__thiscall*)(void* pred, int predicted_frame); //0x2412AC70
	}
	*/
	return (decltype(&Redirected_Get_User_Command)(Original_Get_User_Command_Caller_Location))(Unknown_Parameter, Command_Number);
}