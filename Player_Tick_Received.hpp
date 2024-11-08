__int32 Shot_Tick;

float Shot_Time;

void Player_Tick_Received(void* Data, void* Unknown_Parameter, __int32* Output)
{
	__int32 Player_Tick = *(__int32*)((unsigned __int64)Data + 8);

	Shot_Time *= Player_Tick < Shot_Tick;

	*Output = Player_Tick;
}