namespace Redirection_Manager
{
	struct Manager_Structure
	{
		void* Original_Function;

		void* Redirected_Function;

		void Redirect_Function(void* Original_Function, void* Redirected_Function)
		{
			this->Original_Function = Original_Function;

			this->Redirected_Function = Redirected_Function;

			DWORD Previous_Access_Rights;

			VirtualProtect(Original_Function, 16, PAGE_EXECUTE_READWRITE, &Previous_Access_Rights);

			*(__int8*)Original_Function = 80;

			*(unsigned __int16*)((unsigned __int64)Original_Function + 1) = 47176;

			*(void**)((unsigned __int64)Original_Function + 3) = Redirected_Function;

			*(__int32*)((unsigned __int64)Original_Function + 11) = 604276552;

			*(unsigned __int8*)((unsigned __int64)Original_Function + 15) = 195;

			VirtualProtect(Original_Function, 16, Previous_Access_Rights, &Previous_Access_Rights);
		}

		void* Caller;

		void Redirect_Function(unsigned __int32 Offset, void* Original_Function, void* Redirected_Function)
		{
			Caller = VirtualAlloc(nullptr, 32 + Offset, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

			__builtin_memcpy(Caller, Original_Function, 16 + Offset);

			Redirect_Function((void*)((unsigned __int64)Caller + 16 + Offset), (void*)((unsigned __int64)Original_Function + 16 + Offset));

			Redirect_Function(Original_Function, Redirected_Function);
		}

		//templates?
		void Restore_Function()
		{
			DWORD Previous_Access_Rights;

			VirtualProtect(Original_Function, 16, PAGE_EXECUTE_READWRITE, &Previous_Access_Rights);

			__builtin_memcpy(Original_Function, Caller, 16);

			VirtualProtect(Original_Function, 16, Previous_Access_Rights, &Previous_Access_Rights);
		}

		void Restore_Redirection()
		{
			Redirect_Function(Original_Function, Redirected_Function);
		}
	};
}