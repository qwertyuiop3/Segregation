Redirection_Manager::Manager_Structure Draw_Crosshair_Manager;

void Redirected_Draw_Crosshair()
{
	*(__int32*)((unsigned __int64)Client_Module + 6758152) = 0;

	static float Rotation_Angle;

	auto Uber_Alles = [&](unsigned __int8 Red, __int32 X, __int32 Y)
	{
		using Set_Color_Type = void(**)(void* Surface, unsigned __int8 Red, unsigned __int8 Green, unsigned __int8 Blue, unsigned __int8 Alpha);

		void* Surface = *(void**)((unsigned __int64)Client_Module + 7146864);

		(*Set_Color_Type(*(unsigned __int64*)Surface + 88))(Surface, Red, 0, 0, 255);

		__int32 Points[12]
		{
			(__int32)(Interface_Uber_Alles_Scale.Integer * __builtin_sinf((Rotation_Angle - 90.f) * 3.1415927f / 180.f)),

			(__int32)(Interface_Uber_Alles_Scale.Integer * __builtin_cosf((Rotation_Angle - 90.f) * 3.1415927f / 180.f)),

			(__int32)(Interface_Uber_Alles_Scale.Integer * __builtin_cosf((Rotation_Angle - 90.f) * 3.1415927f / 180.f + 1.f)),

			(__int32)(Interface_Uber_Alles_Scale.Integer * __builtin_sinf(Rotation_Angle * 3.1415927f / 180.f)),

			(__int32)(Interface_Uber_Alles_Scale.Integer * __builtin_cosf(Rotation_Angle * 3.1415927f / 180.f)),

			(__int32)(Interface_Uber_Alles_Scale.Integer * __builtin_sinf(Rotation_Angle * 3.1415927f / 180.f + 1.f)),

			(__int32)(Interface_Uber_Alles_Scale.Integer * __builtin_sinf((Rotation_Angle + 90.f) * 3.1415927f / 180.f)),

			(__int32)(Interface_Uber_Alles_Scale.Integer * __builtin_cosf((Rotation_Angle + 90.f) * 3.1415927f / 180.f)),

			(__int32)(Interface_Uber_Alles_Scale.Integer * __builtin_cosf((Rotation_Angle + 90.f) * 3.1415927f / 180.f + 1.f)),

			(__int32)(Interface_Uber_Alles_Scale.Integer * __builtin_sinf((Rotation_Angle + 180.f) * 3.1415927f / 180.f)),

			(__int32)(Interface_Uber_Alles_Scale.Integer * __builtin_cosf((Rotation_Angle + 180.f) * 3.1415927f / 180.f)),

			(__int32)(Interface_Uber_Alles_Scale.Integer * __builtin_sinf((Rotation_Angle + 180.f) * 3.1415927f / 180.f + 1.f))
		};

		using Draw_Line_Type = void(**)(void* Surface, __int32 From_X, __int32 From_Y, __int32 To_X, __int32 To_Y);

		(*Draw_Line_Type(*(unsigned __int64*)Surface + 120))(Surface, X, Y, X + Points[0], Y - Points[1]);

		(*Draw_Line_Type(*(unsigned __int64*)Surface + 120))(Surface, X + Points[0], Y - Points[1], X + Points[0], Y - Points[2]);

		(*Draw_Line_Type(*(unsigned __int64*)Surface + 120))(Surface, X, Y, X + Points[3], Y - Points[4]);

		(*Draw_Line_Type(*(unsigned __int64*)Surface + 120))(Surface, X + Points[3], Y - Points[4], X + Points[5], Y - Points[4]);

		(*Draw_Line_Type(*(unsigned __int64*)Surface + 120))(Surface, X, Y, X + Points[6], Y - Points[7]);

		(*Draw_Line_Type(*(unsigned __int64*)Surface + 120))(Surface, X + Points[6], Y - Points[7], X + Points[6], Y - Points[8]);

		(*Draw_Line_Type(*(unsigned __int64*)Surface + 120))(Surface, X, Y, X + Points[9], Y - Points[10]);

		(*Draw_Line_Type(*(unsigned __int64*)Surface + 120))(Surface, X + Points[9], Y - Points[10], X + Points[11], Y - Points[10]);
	};

	using Get_Screen_Size_Type = __int32(*)(__int32* Width, __int32* Height);

	__int32 Screen_Width;

	__int32 Screen_Height;

	Get_Screen_Size_Type((unsigned __int64)Client_Module + 1780880)(&Screen_Width, &Screen_Height);

	Screen_Width /= 2;

	Screen_Height /= 2;

	Uber_Alles(0, Screen_Width - 1, Screen_Height);

	Uber_Alles(0, Screen_Width, Screen_Height - 1);

	Uber_Alles(0, Screen_Width + 1, Screen_Height);

	Uber_Alles(0, Screen_Width, Screen_Height + 1);

	Uber_Alles(0, Screen_Width - 1, Screen_Height - 1);

	Uber_Alles(0, Screen_Width + 1, Screen_Height - 1);

	Uber_Alles(0, Screen_Width - 1, Screen_Height + 1);

	Uber_Alles(0, Screen_Width + 1, Screen_Height + 1);

	Uber_Alles(255, Screen_Width, Screen_Height);

	Rotation_Angle = __builtin_remainderf(Rotation_Angle - (*(Global_Variables_Structure**)((unsigned __int64)Client_Module + 5956224))->Frame_Time * Interface_Uber_Alles_Speed.Integer, 180.f);
}