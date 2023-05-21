#pragma once

void Redirect_Function_In_Table(__int8 Modify_Access_Rights, void* Original_Function_In_Table_Location, void* Redirected_Function_Location)
{
	unsigned long __int32 Previous_Access_Rights;

	if (Modify_Access_Rights == 1)
	{
		VirtualProtect(Original_Function_In_Table_Location, sizeof(void*), PAGE_EXECUTE_READWRITE, &Previous_Access_Rights);
	}

	*(void**)Original_Function_In_Table_Location = Redirected_Function_Location;

	if (Modify_Access_Rights == 1)
	{
		VirtualProtect(Original_Function_In_Table_Location, sizeof(void*), Previous_Access_Rights, &Previous_Access_Rights);
	}
}