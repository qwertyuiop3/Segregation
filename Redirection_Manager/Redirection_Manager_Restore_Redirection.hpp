#pragma once

void Restore_Redirection(__int8 Modify_Access_Rights, void* Original_Function_Location, void* Redirected_Function_Location)
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
		*(__int8*)Original_Function_Location = 104;

		*(void**)((unsigned __int32)Original_Function_Location + 1) = Redirected_Function_Location;

		*(unsigned __int8*)((unsigned __int32)Original_Function_Location + 5) = 195;
	#else
		*(__int8*)Original_Function_Location = 80;

		*(unsigned __int16*)((unsigned __int64)Original_Function_Location + 1) = 47176;

		*(void**)((unsigned __int64)Original_Function_Location + 3) = Redirected_Function_Location;

		*(__int32*)((unsigned __int64)Original_Function_Location + 11) = 604276552;

		*(unsigned __int8*)((unsigned __int64)Original_Function_Location + 15) = 195;
	#endif

	if (Modify_Access_Rights == 1)
	{
		#ifdef Bits_32
			VirtualProtect(Original_Function_Location, 6, Previous_Access_Rights, &Previous_Access_Rights);
		#else
			VirtualProtect(Original_Function_Location, 16, Previous_Access_Rights, &Previous_Access_Rights);
		#endif
	}
}