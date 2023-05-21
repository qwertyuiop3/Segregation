#pragma once

void Restore_Function(__int8 Modify_Access_Rights, void* Original_Function_Location, void* Original_Function_Caller_Location, __int8 Delete_Original_Function_Caller)
{
	unsigned long __int32 Previous_Access_Rights;

	if (Modify_Access_Rights == 1)
	{
		#ifdef Bits_32
			VirtualProtect(Original_Function_Location, 6, PAGE_EXECUTE_READWRITE, &Previous_Access_Rights);
		#else
			VirtualProtect(Original_Function_Location, 16, PAGE_EXECUTE_READWRITE, &Previous_Access_Rights);
		#endif
	}

	#ifdef Bits_32
		*(void**)Original_Function_Location = *(void**)Original_Function_Caller_Location;

		*(unsigned __int16*)((unsigned __int32)Original_Function_Location + 4) = *(unsigned __int16*)((unsigned __int32)Original_Function_Caller_Location + 4);
	#else
		*(void**)Original_Function_Location = *(void**)Original_Function_Caller_Location;

		*(void**)((unsigned __int64)Original_Function_Location + 8) = *(void**)((unsigned __int64)Original_Function_Caller_Location + 8);
	#endif

	if (Modify_Access_Rights == 1)
	{
		#ifdef Bits_32
			VirtualProtect(Original_Function_Location, 6, Previous_Access_Rights, &Previous_Access_Rights);
		#else
			VirtualProtect(Original_Function_Location, 16, Previous_Access_Rights, &Previous_Access_Rights);
		#endif
	}

	if (Delete_Original_Function_Caller == 1)
	{
		free(Original_Function_Caller_Location);
	}
}