#pragma once

void Restore_Table(void* Original_Table_Container_Location, void* Original_Table_Location, __int8 Delete_Redirected_Table, void* Redirected_Table_Location)
{
	*(void**)Original_Table_Container_Location = Original_Table_Location;

	if (Delete_Redirected_Table == 1)
	{
		free(Redirected_Table_Location);
	}
}