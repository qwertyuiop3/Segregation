void Redirected_Draw_Crosshair()
{
	*(__int8*)608051340 = 0;

	static float Rotation_Angle;

	auto Uber_Alles = [&](unsigned __int8 Red, __int32 X, __int32 Y)
	{
		using Set_Color_Type = void(__thiscall**)(void* Surface, unsigned __int8 Red, unsigned __int8 Green, unsigned __int8 Blue, unsigned __int8 Alpha);

		void* Surface = *(void**)608279384;

		(*Set_Color_Type(*(unsigned __int32*)Surface + 44))(Surface, Red, 0, 0, 255);

		float Uber_Alles = Interface_Uber_Alles_Scale.Integer;

		__int32 Points[16]
		{
			(__int32)(Uber_Alles * __builtin_sinf((Rotation_Angle - 90) * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_cosf((Rotation_Angle - 90) * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_sinf((Rotation_Angle - 90) * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_cosf((Rotation_Angle - 90) * 3.1415927f / 180 + 1)),

			(__int32)(Uber_Alles * __builtin_sinf(Rotation_Angle * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_cosf(Rotation_Angle * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_sinf(Rotation_Angle * 3.1415927f / 180 + 1)),

			(__int32)(Uber_Alles * __builtin_cosf(Rotation_Angle * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_sinf((Rotation_Angle + 90) * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_cosf((Rotation_Angle + 90) * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_sinf((Rotation_Angle + 90) * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_cosf((Rotation_Angle + 90) * 3.1415927f / 180 + 1)),

			(__int32)(Uber_Alles * __builtin_sinf((Rotation_Angle + 180) * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_cosf((Rotation_Angle + 180) * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_sinf((Rotation_Angle + 180) * 3.1415927f / 180 + 1)),

			(__int32)(Uber_Alles * __builtin_cosf((Rotation_Angle + 180) * 3.1415927f / 180)),
		};

		using Draw_Line_Type = void(__thiscall**)(void* Surface, __int32 From_X, __int32 From_Y, __int32 To_X, __int32 To_Y);

		(*Draw_Line_Type(*(unsigned __int32*)Surface + 60))(Surface, X, Y, X + Points[0], Y - Points[1]);

		(*Draw_Line_Type(*(unsigned __int32*)Surface + 60))(Surface, X + Points[0], Y - Points[1], X + Points[2], Y - Points[3]);

		(*Draw_Line_Type(*(unsigned __int32*)Surface + 60))(Surface, X, Y, X + Points[4], Y - Points[5]);

		(*Draw_Line_Type(*(unsigned __int32*)Surface + 60))(Surface, X + Points[4], Y - Points[5], X + Points[6], Y - Points[7]);

		(*Draw_Line_Type(*(unsigned __int32*)Surface + 60))(Surface, X, Y, X + Points[8], Y - Points[9]);

		(*Draw_Line_Type(*(unsigned __int32*)Surface + 60))(Surface, X + Points[8], Y - Points[9], X + Points[10], Y - Points[11]);

		(*Draw_Line_Type(*(unsigned __int32*)Surface + 60))(Surface, X, Y, X + Points[12], Y - Points[13]);

		(*Draw_Line_Type(*(unsigned __int32*)Surface + 60))(Surface, X + Points[12], Y - Points[13], X + Points[14], Y - Points[15]);
	};

	using Get_Screen_Size_Type = __int32(__cdecl*)();

	__int32 Screen_Width = Get_Screen_Size_Type(604542880)() / 2;

	__int32 Screen_Height = Get_Screen_Size_Type(604542848)() / 2;

	Uber_Alles(0, Screen_Width - 1, Screen_Height);

	Uber_Alles(0, Screen_Width, Screen_Height - 1);

	Uber_Alles(0, Screen_Width + 1, Screen_Height);

	Uber_Alles(0, Screen_Width, Screen_Height + 1);

	Uber_Alles(0, Screen_Width - 1, Screen_Height - 1);

	Uber_Alles(0, Screen_Width + 1, Screen_Height - 1);

	Uber_Alles(0, Screen_Width - 1, Screen_Height + 1);

	Uber_Alles(0, Screen_Width + 1, Screen_Height + 1);

	Uber_Alles(255, Screen_Width, Screen_Height);

	Rotation_Angle = __builtin_remainderf(Rotation_Angle - (*(Global_Variables_Structure**)607726732)->Frame_Time * Interface_Uber_Alles_Speed.Integer, 360);
}