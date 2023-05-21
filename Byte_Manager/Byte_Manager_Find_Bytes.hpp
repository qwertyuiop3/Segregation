#pragma once

#ifdef Bits_32
	void* Find_Bytes(void* Starting_Location, void* Bytes, unsigned __int32 Bytes_Amount)
#else
	void* Find_Bytes(void* Starting_Location, void* Bytes, unsigned __int64 Bytes_Amount)
#endif
	{
		Compare_Bytes_Label:
		{
			if (__builtin_memcmp(Starting_Location, Bytes, Bytes_Amount) == 0)
			{
				return Starting_Location;
			}

			#ifdef Bits_32
				Starting_Location = (void*)((unsigned __int32)Starting_Location + 1);
			#else
				Starting_Location = (void*)((unsigned __int64)Starting_Location + 1);
			#endif

			goto Compare_Bytes_Label;
		}
	}