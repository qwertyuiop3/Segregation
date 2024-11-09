void* Original_Entity_Time_Received;

void Entity_Time_Received(void* Data, void* Unknown_Parameter_1, void* Unknown_Parameter_2)
{
	__int32 Offset = *(__int32*)((unsigned __int64)Data + 8);

	if (Offset != 0)
	{
		(decltype(&Entity_Time_Received)(Original_Entity_Time_Received))(Data, Unknown_Parameter_1, Unknown_Parameter_2);
	}
}