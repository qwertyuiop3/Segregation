Redirection_Manager::Manager_Structure Draw_Crosshair_Manager;

void Redirected_Draw_Crosshair(void* Unknown_Parameter)
{
	static float Rotation_Angle;

	auto Uber_Alles = [&](__int32 Red, __int32 X, __int32 Y) -> void
	{
		using Set_Color_Type = void(**)(void* Surface, __int32 Red, __int32 Green, __int32 Blue, __int32 Alpha);

		static void* Surface = *(void**)Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(113543, (unsigned __int8*)Client_Module, 2457970300653241385), 3);

		(*Set_Color_Type(*(unsigned __int64*)Surface + 120))(Surface, Red, 0, 0, 255);

		__int32 Points[12]
		{
			(__int32)(Interface_Uber_Alles_Scale.Get_Integer() * __builtin_sinf((Rotation_Angle - 90.f) * 3.1415927f / 180.f)),

			(__int32)(Interface_Uber_Alles_Scale.Get_Integer() * __builtin_cosf((Rotation_Angle - 90.f) * 3.1415927f / 180.f)),

			(__int32)(Interface_Uber_Alles_Scale.Get_Integer() * __builtin_cosf((Rotation_Angle - 90.f) * 3.1415927f / 180.f + 1.f)),

			(__int32)(Interface_Uber_Alles_Scale.Get_Integer() * __builtin_sinf(Rotation_Angle * 3.1415927f / 180.f)),

			(__int32)(Interface_Uber_Alles_Scale.Get_Integer() * __builtin_cosf(Rotation_Angle * 3.1415927f / 180.f)),

			(__int32)(Interface_Uber_Alles_Scale.Get_Integer() * __builtin_sinf(Rotation_Angle * 3.1415927f / 180.f + 1.f)),

			(__int32)(Interface_Uber_Alles_Scale.Get_Integer() * __builtin_sinf((Rotation_Angle + 90.f) * 3.1415927f / 180.f)),

			(__int32)(Interface_Uber_Alles_Scale.Get_Integer() * __builtin_cosf((Rotation_Angle + 90.f) * 3.1415927f / 180.f)),

			(__int32)(Interface_Uber_Alles_Scale.Get_Integer() * __builtin_cosf((Rotation_Angle + 90.f) * 3.1415927f / 180.f + 1.f)),

			(__int32)(Interface_Uber_Alles_Scale.Get_Integer() * __builtin_sinf((Rotation_Angle + 180.f) * 3.1415927f / 180.f)),

			(__int32)(Interface_Uber_Alles_Scale.Get_Integer() * __builtin_cosf((Rotation_Angle + 180.f) * 3.1415927f / 180.f)),

			(__int32)(Interface_Uber_Alles_Scale.Get_Integer() * __builtin_sinf((Rotation_Angle + 180.f) * 3.1415927f / 180.f + 1.f))
		};

		using Draw_Line_Type = void(**)(void* Surface, float From_X, float From_Y, float To_X, float To_Y);

		(*Draw_Line_Type(*(unsigned __int64*)Surface + 152))(Surface, X, Y, X + Points[0], Y - Points[1]);

		(*Draw_Line_Type(*(unsigned __int64*)Surface + 152))(Surface, X + Points[0], Y - Points[1], X + Points[0], Y - Points[2]);

		(*Draw_Line_Type(*(unsigned __int64*)Surface + 152))(Surface, X, Y, X + Points[3], Y - Points[4]);

		(*Draw_Line_Type(*(unsigned __int64*)Surface + 152))(Surface, X + Points[3], Y - Points[4], X + Points[5], Y - Points[4]);

		(*Draw_Line_Type(*(unsigned __int64*)Surface + 152))(Surface, X, Y, X + Points[6], Y - Points[7]);

		(*Draw_Line_Type(*(unsigned __int64*)Surface + 152))(Surface, X + Points[6], Y - Points[7], X + Points[6], Y - Points[8]);

		(*Draw_Line_Type(*(unsigned __int64*)Surface + 152))(Surface, X, Y, X + Points[9], Y - Points[10]);

		(*Draw_Line_Type(*(unsigned __int64*)Surface + 152))(Surface, X + Points[9], Y - Points[10], X + Points[11], Y - Points[10]);
	};

	using Get_Screen_Size_Type = void(**)(void* Engine, __int32* Width, __int32* Height);

	void* Engine = Get_Engine();

	__int32 Screen_Width;

	__int32 Screen_Height;

	(*Get_Screen_Size_Type(*(unsigned __int64*)Engine + 40))(Engine, &Screen_Width, &Screen_Height);

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

	Rotation_Angle = __builtin_remainderf(Rotation_Angle - Get_Global_Variables()->Frame_Time * Interface_Uber_Alles_Speed.Get_Integer(), 180.f);
}