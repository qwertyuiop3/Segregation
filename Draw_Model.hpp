void* Original_Draw_Model_Caller_Location;

__int32 __thiscall Redirected_Draw_Model(void* Entity, void* Unknown_Parameter)
{
	if (*(__int32*)((unsigned __int32)Entity + 140) == *(__int32*)((unsigned __int32)Entity + 2180))
	{
		using Set_Model_Index_Type = void(__thiscall*)(void* Entity, __int32 Index);

		Set_Model_Index_Type((unsigned __int32)Client_Module_Location + 622160)((void*)((unsigned __int32)Entity - 4), *(__int32*)((unsigned __int32)Entity + 2184));
	}

	return (decltype(&Redirected_Draw_Model)(Original_Draw_Model_Caller_Location))(Entity, Unknown_Parameter);
}