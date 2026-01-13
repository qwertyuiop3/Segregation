Redirection_Manager::Manager_Structure Draw_Crosshair_Manager;

void Redirected_Draw_Crosshair(void* Unknown_Parameter)
{
	static float Rotation_Angle;

	auto Uber_Alles = [&](__int32 Scale, __int32 X, __int32 Radius, __int32 Additional_Angle, __int32 Y) -> void
	{
		using Set_Color_Type = void(**)(void* Surface, __int32 Red, __int32 Green, __int32 Blue, __int32 Alpha);

		static void* Surface = *(void**)Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(113543, (unsigned __int8*)Client_Module, 2457970300653241385), 3);

		(*Set_Color_Type(*(unsigned __int64*)Surface + 120))(Surface, 0, 0, 0, 255);

		float Points[12]
		{
			Scale * __builtin_sinf((Rotation_Angle - 90.f) * 3.1415927f / 180.f),

			Scale * __builtin_cosf((Rotation_Angle - 90.f) * 3.1415927f / 180.f),

			Scale * __builtin_cosf((Rotation_Angle - 90.f) * 3.1415927f / 180.f + 1.f),

			Scale * __builtin_sinf(Rotation_Angle * 3.1415927f / 180.f),

			Scale * __builtin_cosf(Rotation_Angle * 3.1415927f / 180.f),

			Scale * __builtin_sinf(Rotation_Angle * 3.1415927f / 180.f + 1.f),

			Scale * __builtin_sinf((Rotation_Angle + 90.f) * 3.1415927f / 180.f),

			Scale * __builtin_cosf((Rotation_Angle + 90.f) * 3.1415927f / 180.f),

			Scale * __builtin_cosf((Rotation_Angle + 90.f) * 3.1415927f / 180.f + 1.f),

			Scale * __builtin_sinf((Rotation_Angle + 180.f) * 3.1415927f / 180.f),

			Scale * __builtin_cosf((Rotation_Angle + 180.f) * 3.1415927f / 180.f),

			Scale * __builtin_sinf((Rotation_Angle + 180.f) * 3.1415927f / 180.f + 1.f)
		};

		auto Draw = [&](__int32 X, __int32 Y) -> void
		{
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

		X += Radius * __builtin_cosf((Rotation_Angle + Additional_Angle) * 3.1415927f / 180.f);

		Y += Radius * __builtin_sinf((Rotation_Angle + Additional_Angle) * 3.1415927f / 180.f);

		Draw(X - 1, Y);

		Draw(X, Y - 1);

		Draw(X + 1, Y);

		Draw(X, Y + 1);

		Draw(X - 1, Y - 1);

		Draw(X + 1, Y - 1);

		Draw(X - 1, Y + 1);

		Draw(X + 1, Y + 1);

		(*Set_Color_Type(*(unsigned __int64*)Surface + 120))(Surface, 255, 0, 0, 255);

		Draw(X, Y);
	};

	float Absolute_Rotation_Angle = __builtin_fabsf(Rotation_Angle);

	using Get_Screen_Size_Type = void(**)(void* Engine, __int32* Width, __int32* Height);

	void* Engine = Get_Engine();

	__int32 Screen_Width;

	__int32 Screen_Height;

	(*Get_Screen_Size_Type(*(unsigned __int64*)Engine + 40))(Engine, &Screen_Width, &Screen_Height);

	Screen_Width /= 2;

	Screen_Height /= 2;

	if (Interface_Uber_Alles_Multiplicative.Get_Integer() * (Absolute_Rotation_Angle >= 360.f) == 0)
	{
		Uber_Alles(Interface_Uber_Alles_Scale.Get_Integer(), Screen_Width, 0, 0, Screen_Height);
	}
	else
	{
		__int32 Uber_Alles_Number = 0;

		Draw_Uber_Alles_Label:
		{
			float Distance = Absolute_Rotation_Angle < (720.f - Interface_Uber_Alles_Multiplicative_Interval.Get_Floating_Point()) ? min((Absolute_Rotation_Angle - 360.f) / Interface_Uber_Alles_Multiplicative_Interval.Get_Floating_Point(), 1.f) : (720.f - Absolute_Rotation_Angle) / Interface_Uber_Alles_Multiplicative_Interval.Get_Floating_Point();

			Uber_Alles(Interface_Uber_Alles_Scale.Get_Integer() - (Interface_Uber_Alles_Scale.Get_Integer() - Interface_Uber_Alles_Multiplicative_Scale.Get_Integer()) * Distance, Screen_Width, Interface_Uber_Alles_Multiplicative_Radius.Get_Integer() * Distance, Uber_Alles_Number * 360 / Interface_Uber_Alles_Multiplicative.Get_Integer(), Screen_Height);

			Uber_Alles_Number += 1;

			if (Uber_Alles_Number != Interface_Uber_Alles_Multiplicative.Get_Integer())
			{
				goto Draw_Uber_Alles_Label;
			}
		}
	}

	Rotation_Angle = __builtin_remainderf(Rotation_Angle - Get_Global_Variables()->Frame_Time * Interface_Uber_Alles_Speed.Get_Floating_Point(), 1440.f);

	if (Rotation_Angle > 0.f)
	{
		Rotation_Angle -= 720.f;
	}
}