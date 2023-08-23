void* Original_Player_Move_Caller;

struct alignas(16) Ray_Structure
{
	__int8 Additional_Bytes[65];
};

struct Filter_Structure
{
	void* Table;

	void* Skip;

	__int32 Group;

	void* Handler;
};

struct Trace_Structure
{
	__int8 Additional_Bytes_1[44];

	float Fraction;

	__int8 Additional_Bytes_2[20];

	__int32 Group;

	__int8 Additional_Bytes_3[4];

	void* Entity;

	__int8 Additional_Bytes_4[4];
};

void __thiscall Redirected_Player_Move(void* Game_Movement)
{
	(decltype(&Redirected_Player_Move)(Original_Player_Move_Caller))(Game_Movement);

	using Trace_Ray_Type = void(__thiscall*)(void* Engine, Ray_Structure* Ray, __int32 Mask, Filter_Structure* Filter, Trace_Structure* Trace);

	using Initialize_Ray_Type = void(__thiscall*)(Ray_Structure* Ray, float* Start, float* End, float* Minimum, float* Maximum);

	Ray_Structure Ray;

	void* Player = *(void**)((unsigned __int32)Game_Movement + 3744);

	float* Origin = (float*)((unsigned __int32)Player + 824);

	__int8 Ducked = *(__int8*)((unsigned __int32)Player + 3616);

	float Start[3] =
	{
		Origin[0],

		Origin[1],

		Origin[2] + (Ducked == 1 ? 45.f : 62.f)
	};

	float End[3] =
	{
		Start[0],

		Start[1],

		Start[2] + 14
	};

	float Minimum[3] =
	{
		-15,

		-15,

		0
	};

	float Maximum[3] =
	{
		15,

		15,

		0
	};

	Initialize_Ray_Type(((unsigned __int32)Client_Module + 419584))(&Ray, Start, End, Minimum, Maximum);

	Filter_Structure Filter;

	Filter.Table = (void*)((unsigned __int32)Client_Module + 3908280);

	Filter.Skip = (void*)Player;

	Filter.Group = 8;

	Filter.Handler = nullptr;

	Trace_Structure Trace;

	Trace_Ray_Type((unsigned __int32)Engine_Module + 1658128)((void*)((unsigned __int32)Engine_Module + 3941436), &Ray, 33636363, &Filter, &Trace);

	__int8 Ducking = *(__int8*)((unsigned __int32)Player + 3617);

	if (Trace.Fraction < 1)
	{
		float Estimation = Start[2] + (End[2] - Start[2]) * Trace.Fraction - Origin[2] - 12;

		if (Ducked + Ducking == 0)
		{
			*(float*)((unsigned __int32)Player + 240) = Estimation;
		}
		else
		{
			*(float*)((unsigned __int32)Player + 240) = min(Estimation, *(float*)((unsigned __int32)Player + 240));
		}
	}
	else
	{
		if (Ducked + Ducking == 0)
		{
			*(float*)((unsigned __int32)Player + 240) = 64;
		}
		else
		{
			if (Ducked > Ducking)
			{
				*(float*)((unsigned __int32)Player + 240) = 47;
			}
		}
	}
}