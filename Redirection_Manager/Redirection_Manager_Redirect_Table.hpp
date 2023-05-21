#pragma once

void Redirect_Table(void* Original_Table_Container_Location, void* Redirected_Table_Location)
{
	*(void**)Original_Table_Container_Location = Redirected_Table_Location;
}