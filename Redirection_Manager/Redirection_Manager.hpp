namespace Redirection_Manager
{
	void Redirect_Function(void* Original_Function, void* Redirected_Function)
	{
		DWORD Previous_Access_Rights;

		VirtualProtect(Original_Function, 6, PAGE_EXECUTE_READWRITE, &Previous_Access_Rights);

		*(__int8*)Original_Function = 104;

		*(void**)((unsigned __int32)Original_Function + 1) = Redirected_Function;

		*(unsigned __int8*)((unsigned __int32)Original_Function + 5) = 195;

		VirtualProtect(Original_Function, 6, Previous_Access_Rights, &Previous_Access_Rights);
	}

	void* Redirect_Function(unsigned __int32 Offset, void* Original_Function, void* Redirected_Function)
	{
		void* Original_Function_Caller = VirtualAlloc(nullptr, 12 + Offset, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

		__builtin_memcpy(Original_Function_Caller, Original_Function, 6 + Offset);

		Redirect_Function((void*)((unsigned __int32)Original_Function_Caller + 6 + Offset), (void*)((unsigned __int32)Original_Function + 6 + Offset));

		Redirect_Function(Original_Function, Redirected_Function);

		return Original_Function_Caller;
	}
};