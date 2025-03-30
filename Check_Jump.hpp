void* Original_Check_Jump_Caller;

__int8 __thiscall Redirected_Check_Jump(void* Movement)
{
	if ((decltype(&Redirected_Check_Jump)(Original_Check_Jump_Caller))(Movement) == 0)
	{
		return 0;
	}

	if (*(void**)((unsigned __int32)Engine_Module + 8406032) == nullptr)
	{
		Animation_Layer_Structure* Frame_Animation_Layers = *(Animation_Layer_Structure**)(*(unsigned __int32*)((unsigned __int32)Movement + 3668) + 10608);

		Networked_Animation_Layers[4].Weight = Frame_Animation_Layers[4].Weight = 0.f;

		Networked_Animation_Layers[4].Cycle = Frame_Animation_Layers[4].Cycle = 0.f;
	}

	return 1;
}