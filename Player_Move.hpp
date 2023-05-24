void* Original_Player_Move_Caller_Location;

void __thiscall Redirected_Player_Move(void* Game_Movement)
{
	void* Local_Player = *(void**)((unsigned __int32)Game_Movement + 3744);

	int flags = *(__int32*)((unsigned __int32)Local_Player + 848);
	bool ducked = *(__int8*)((unsigned __int32)Local_Player + 3548 + 68);
	bool ducking = *(__int8*)((unsigned __int32)Local_Player + 3548 + 69);
	constexpr int FL_DUCKING = 2;

	const float eyeClearance = 12.0f;

	float offset = *(float*)((unsigned __int32)Local_Player + 240);

	float vHullMin[3] = { -16, -16, 0 };
	float vHullMax[3] = { 16, 16, ducked ? 45.f : 62.f };

	float start[3] = { *(float*)((unsigned __int32)Local_Player + 824),
		*(float*)((unsigned __int32)Local_Player + 824 + 4),
		*(float*)((unsigned __int32)Local_Player + 824 + 8)
	};
	start[2] += vHullMax[2];
	float end[3] = { start[0], start[1], start[2] };
	end[2] += eyeClearance - vHullMax[2];
	end[2] += ducked ? 47 : 64;
	vHullMax[2] = 0;

	vHullMin[0] += 1;
	vHullMin[1] += 1;
	vHullMax[0] -= 1;
	vHullMax[1] -= 1;

	struct alignas(4) Ray_Structure
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

		__int8 Additional_Bytes_2[36];
	};

	using Initialize_Ray_Type = void(__thiscall*)(Ray_Structure* Ray, float* Start, float* End, float* Minimum, float* Maximum);

	Trace_Structure trace;
	Ray_Structure ray;
	Filter_Structure filter;
	filter.Table = (void*)((unsigned __int32)Client_Module_Location + 0x3BA2B8);
	filter.Skip = (void*)Local_Player;
	filter.Group = 8;
	filter.Handler = nullptr;
	Initialize_Ray_Type(((unsigned __int32)Client_Module_Location + 419584))(&ray, start, end, vHullMin, vHullMax);
	using Trace_Ray_Type = void(__thiscall*)(void* Engine, Ray_Structure* Ray, __int32 Mask, Filter_Structure* Filter, Trace_Structure* Trace);
	Trace_Ray_Type((unsigned __int32)Engine_Module_Location + 1658128)((void*)((unsigned __int32)Engine_Module_Location + 3941436), &ray, 33636363, &filter, &trace);

	if (trace.Fraction < 1.0f)
	{
		float est = start[2] + trace.Fraction * (end[2] - start[2]) - *(float*)((unsigned __int32)Local_Player + 824 + 8) - eyeClearance;
		if ((flags & FL_DUCKING) == 0 && !ducking && !ducked)
		{	
			offset = est;
		}
		else
		{
			offset = min(est, offset);
		}
		*(float*)((unsigned __int32)Local_Player + 240) = offset;
	}
	else
	{
		if ((flags & FL_DUCKING) == 0 && !ducking && !ducked)
		{
			*(float*)((unsigned __int32)Local_Player + 240) = 64;
		}
		else if (*(__int8*)((unsigned __int32)Local_Player + 5208))
		{
			*(float*)((unsigned __int32)Local_Player + 240) = 47;
		}
		else if (ducked && !ducking)
		{
			*(float*)((unsigned __int32)Local_Player + 240) = 47;
		}
	}

	(decltype(&Redirected_Player_Move)(Original_Player_Move_Caller_Location))(Game_Movement);
}