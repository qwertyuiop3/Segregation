void Redirected_Draw_Crosshair()
{
	static float Rotation_Angle;

	auto Uber_Alles = [&](__int32 Scale, __int32 X, __int32 Radius, __int32 Additional_Angle, __int32 Y) -> void
	{
		using Set_Color_Type = void(__thiscall**)(void* Surface, unsigned __int8 Red, unsigned __int8 Green, unsigned __int8 Blue, unsigned __int8 Alpha);

		void* Surface = *(void**)((unsigned __int32)Client_Module + 83370428);

		(*Set_Color_Type(*(unsigned __int32*)Surface + 60))(Surface, 0, 0, 0, 255);

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
			using Draw_Line_Type = void(__thiscall**)(void* Surface, __int32 From_X, __int32 From_Y, __int32 To_X, __int32 To_Y);

			(*Draw_Line_Type(*(unsigned __int32*)Surface + 76))(Surface, X, Y, X + Points[0], Y - Points[1]);

			(*Draw_Line_Type(*(unsigned __int32*)Surface + 76))(Surface, X + Points[0], Y - Points[1], X + Points[0], Y - Points[2]);

			(*Draw_Line_Type(*(unsigned __int32*)Surface + 76))(Surface, X, Y, X + Points[3], Y - Points[4]);

			(*Draw_Line_Type(*(unsigned __int32*)Surface + 76))(Surface, X + Points[3], Y - Points[4], X + Points[5], Y - Points[4]);

			(*Draw_Line_Type(*(unsigned __int32*)Surface + 76))(Surface, X, Y, X + Points[6], Y - Points[7]);

			(*Draw_Line_Type(*(unsigned __int32*)Surface + 76))(Surface, X + Points[6], Y - Points[7], X + Points[6], Y - Points[8]);

			(*Draw_Line_Type(*(unsigned __int32*)Surface + 76))(Surface, X, Y, X + Points[9], Y - Points[10]);

			(*Draw_Line_Type(*(unsigned __int32*)Surface + 76))(Surface, X + Points[9], Y - Points[10], X + Points[11], Y - Points[10]);
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

		(*Set_Color_Type(*(unsigned __int32*)Surface + 60))(Surface, 255, 0, 0, 255);

		Draw(X, Y);
	};

	float Absolute_Rotation_Angle = __builtin_fabsf(Rotation_Angle);

	__int32 Screen_Width = *(__int32*)((unsigned __int32)Client_Module + 10892112) / 2;

	__int32 Screen_Height = *(__int32*)((unsigned __int32)Client_Module + 10892116) / 2;

	if (Interface_Uber_Alles_Multiplicative.Get_Integer() * (Absolute_Rotation_Angle >= 360.f) == 0)
	{
		Uber_Alles(Interface_Uber_Alles_Scale.Get_Integer(), Screen_Width, 0, 0, Screen_Height);
	}
	else
	{
		__int32 Uber_Alles_Number = 0;

		Draw_Uber_Alles_Label:
		{
			float Distance = Absolute_Rotation_Angle < 720.f - Interface_Uber_Alles_Multiplicative_Interval.Get_Floating_Point() ? min((Absolute_Rotation_Angle - 360.f) / Interface_Uber_Alles_Multiplicative_Interval.Get_Floating_Point(), 1.f) : (720.f - Absolute_Rotation_Angle) / Interface_Uber_Alles_Multiplicative_Interval.Get_Floating_Point();

			Uber_Alles(Interface_Uber_Alles_Scale.Get_Integer() - (Interface_Uber_Alles_Scale.Get_Integer() - Interface_Uber_Alles_Multiplicative_Scale.Get_Integer()) * Distance, Screen_Width, Interface_Uber_Alles_Multiplicative_Radius.Get_Integer() * Distance, Uber_Alles_Number * 360 / Interface_Uber_Alles_Multiplicative.Get_Integer(), Screen_Height);

			Uber_Alles_Number += 1;

			if (Uber_Alles_Number != Interface_Uber_Alles_Multiplicative.Get_Integer())
			{
				goto Draw_Uber_Alles_Label;
			}
		}
	}

	Rotation_Angle = __builtin_remainderf(Rotation_Angle - (*(Global_Variables_Structure**)((unsigned __int32)Client_Module + 10871344))->Frame_Time * Interface_Uber_Alles_Speed.Get_Floating_Point(), 1440.f);

	if (Rotation_Angle > 0.f)
	{
		Rotation_Angle -= 720.f;
	}
}