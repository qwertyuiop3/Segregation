namespace Byte_Manager
{
	void Set_Bytes(__int8 Writeable, void* Address, unsigned __int64 Size, unsigned __int8 Byte)
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

	void Copy_Bytes(__int8 Writeable, void* Address, unsigned __int64 Size, void* Bytes)
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

	unsigned __int64 Compute_Hash(unsigned __int64 Mask, unsigned __int8* Bytes)
	{
		unsigned __int8 Bit_Number = 0;

		unsigned __int64 Hash = 14695981039346656037ull;

		Traverse_Bits_Label:
		{
			if (Bit_Number != sizeof(Mask) * 8)
			{
				if ((Mask & (1ull << Bit_Number)) == 1ull << Bit_Number)
				{
					Hash = (Bytes[Bit_Number] ^ Hash) * 1099511628211;
				}

				Bit_Number += 1;

				goto Traverse_Bits_Label;
			}
		}

		return Hash;
	}

	void* Find_Bytes(unsigned __int64 Mask, unsigned __int8* Address, unsigned __int64 Hash)
	{
		Traverse_Bytes_Label:
		{
			if (Compute_Hash(Mask, Address) == Hash)
			{
				return Address;
			}

			Address += 1;

			goto Traverse_Bytes_Label;
		}
	}

	void* Solve_Relative(void* Address, unsigned __int64 Offset)
	{
		return (void*)((unsigned __int64)Address + *(__int32*)((unsigned __int64)Address + Offset) + Offset + 4 + (*(unsigned __int8*)Address == 131));
	}
};