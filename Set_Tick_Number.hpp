__int32 Shot_Tick_Number;

void Redirected_Set_Tick_Number(void* Input, void* Unknown_Parameter, __int32* Output)
{
	__int32 Tick_Number = *(__int32*)((unsigned __int64)Input + 8);

	Shot_Tick_Number *= Tick_Number < Shot_Tick_Number;

	*Output = Tick_Number;
}