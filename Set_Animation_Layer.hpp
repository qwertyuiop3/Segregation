void Redirected_Set_Animation_Layer(void* Proxy, Animation_Layer_Structure* Animation_Layer)
{
	void* Value = *(void**)((unsigned __int32)Animation_Layer + *(__int32*)(*(unsigned __int32*)Proxy + 44));

	(decltype(&Redirected_Set_Animation_Layer)(*(void**)(*(unsigned __int32*)Proxy + 36)))(Proxy, Animation_Layer);

	if ((Animation_Layer->Owner != nullptr) * (Animation_Layer->Owner == *(void**)((unsigned __int32)Client_Module + 82926756)) == 1)
	{
		*(void**)((unsigned __int32)Animation_Layer + *(__int32*)(*(unsigned __int32*)Proxy + 44)) = Value;

		*(void**)((unsigned __int32)Networked_Animation_Layers + (__int32)Animation_Layer + *(__int32*)(*(unsigned __int32*)Proxy + 44) - *(__int32*)((unsigned __int32)Animation_Layer->Owner + 10608)) = *(void**)((unsigned __int32)Proxy + 8);
	}
}