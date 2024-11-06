namespace Byte_Manager
{
	void Set_Bytes(__int8 Writeable, void* Address, unsigned __int32 Size, unsigned __int8 Byte)
	{
		if (Writeable == 0)
		{
			DWORD Previous_Access_Rights;

			VirtualProtect(Address, Size, PAGE_EXECUTE_READWRITE, &Previous_Access_Rights);

			__builtin_memset(Address, Byte, Size);

			VirtualProtect(Address, Size, Previous_Access_Rights, &Previous_Access_Rights);
		}
		else
		{
			__builtin_memset(Address, Byte, Size);
		}
	}

	void Copy_Bytes(__int8 Writeable, void* Address, unsigned __int32 Size, void* Bytes)
	{
		if (Writeable == 0)
		{
			DWORD Previous_Access_Rights;

			VirtualProtect(Address, Size, PAGE_EXECUTE_READWRITE, &Previous_Access_Rights);

			__builtin_memcpy(Address, Bytes, Size);

			VirtualProtect(Address, Size, Previous_Access_Rights, &Previous_Access_Rights);
		}
		else
		{
			__builtin_memcpy(Address, Bytes, Size);
		}
	}
};