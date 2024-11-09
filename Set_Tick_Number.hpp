__int32 Shot_Tick;

void Redirected_Set_Tick_Number(void* Input, void* Unknown_Parameter, __int32* Output)
{
	__int32 Player_Tick = *(__int32*)((unsigned __int64)Input + 8);

	Shot_Tick *= Player_Tick < Shot_Tick;

	*Output = Player_Tick;
}