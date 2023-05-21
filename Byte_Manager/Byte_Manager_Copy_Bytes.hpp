#pragma once

#ifdef Bits_32
	void Copy_Bytes(__int8 Modify_Access_Rights, void* Starting_Location, unsigned __int32 Bytes_Amount, void* Bytes)
#else
	void Copy_Bytes(__int8 Modify_Access_Rights, void* Starting_Location, unsigned __int64 Bytes_Amount, void* Bytes)
#endif
	{
		unsigned long __int32 Previous_Access_Rights;

		if (Modify_Access_Rights == 1)
		{
			VirtualProtect(Starting_Location, Bytes_Amount, PAGE_EXECUTE_READWRITE, &Previous_Access_Rights);
		}

		__builtin_memcpy(Starting_Location, Bytes, Bytes_Amount);

		if (Modify_Access_Rights == 1)
		{
			VirtualProtect(Starting_Location, Bytes_Amount, Previous_Access_Rights, &Previous_Access_Rights);
		}
	}