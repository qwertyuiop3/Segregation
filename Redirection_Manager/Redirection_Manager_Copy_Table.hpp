#pragma once

void* Copy_Table(void* Table_Location)
{
	#ifdef Bits_32
		unsigned __int32 Functions_Count = 0;
	#else
		unsigned __int64 Functions_Count = 0;
	#endif

	Take_Function_Into_Account_Label:
	{
		#ifdef Bits_32
			if (*(void**)((unsigned __int32)Table_Location + Functions_Count) != nullptr)
		#else
			if (*(void**)((unsigned __int64)Table_Location + Functions_Count) != nullptr)
		#endif
			{
				Functions_Count += sizeof(void*);

				goto Take_Function_Into_Account_Label;
			}
	}

	void* Copied_Table_Location = malloc(Functions_Count);

	__builtin_memcpy(Copied_Table_Location, Table_Location, Functions_Count);

	return Copied_Table_Location;
}