void Redirected_Draw_Crosshair()
{
	*(__int8*)((unsigned __int32)Client_Module_Location + 5190296) = 0;

	static float Rotation_Angle;

	auto Uber_Alles = [&](unsigned __int8 Red, __int32 X, __int32 Y)
	{
		using Set_Color_Type = void(__thiscall**)(void* Surface, unsigned __int8 Red, unsigned __int8 Green, unsigned __int8 Blue, unsigned __int8 Alpha);

		void* Surface = *(void**)((unsigned __int32)Client_Module_Location + 5530696);

		(*Set_Color_Type(*(unsigned __int32*)Surface + 44))(Surface, Red, 0, 0, 255);

		float Uber_Alles = Interface_Uber_Alles_Scale.Integer;

		__int32 Points[12]
		{
			(__int32)(Uber_Alles * __builtin_sinf((Rotation_Angle - 90) * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_cosf((Rotation_Angle - 90) * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_cosf((Rotation_Angle - 90) * 3.1415927f / 180 + 1)),

			(__int32)(Uber_Alles * __builtin_sinf(Rotation_Angle * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_cosf(Rotation_Angle * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_sinf(Rotation_Angle * 3.1415927f / 180 + 1)),

			(__int32)(Uber_Alles * __builtin_sinf((Rotation_Angle + 90) * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_cosf((Rotation_Angle + 90) * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_cosf((Rotation_Angle + 90) * 3.1415927f / 180 + 1)),

			(__int32)(Uber_Alles * __builtin_sinf((Rotation_Angle + 180) * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_cosf((Rotation_Angle + 180) * 3.1415927f / 180)),

			(__int32)(Uber_Alles * __builtin_sinf((Rotation_Angle + 180) * 3.1415927f / 180 + 1))
		};

		using Draw_Line_Type = void(__thiscall**)(void* Surface, __int32 From_X, __int32 From_Y, __int32 To_X, __int32 To_Y);

		(*Draw_Line_Type(*(unsigned __int32*)Surface + 60))(Surface, X, Y, X + Points[0], Y - Points[1]);

		(*Draw_Line_Type(*(unsigned __int32*)Surface + 60))(Surface, X + Points[0], Y - Points[1], X + Points[0], Y - Points[2]);

		(*Draw_Line_Type(*(unsigned __int32*)Surface + 60))(Surface, X, Y, X + Points[3], Y - Points[4]);

		(*Draw_Line_Type(*(unsigned __int32*)Surface + 60))(Surface, X + Points[3], Y - Points[4], X + Points[5], Y - Points[4]);

		(*Draw_Line_Type(*(unsigned __int32*)Surface + 60))(Surface, X, Y, X + Points[6], Y - Points[7]);

		(*Draw_Line_Type(*(unsigned __int32*)Surface + 60))(Surface, X + Points[6], Y - Points[7], X + Points[6], Y - Points[8]);

		(*Draw_Line_Type(*(unsigned __int32*)Surface + 60))(Surface, X, Y, X + Points[9], Y - Points[10]);

		(*Draw_Line_Type(*(unsigned __int32*)Surface + 60))(Surface, X + Points[9], Y - Points[10], X + Points[11], Y - Points[10]);
	};

	using Get_Screen_Size_Type = __int32(__cdecl*)();

	__int32 Screen_Width = Get_Screen_Size_Type((unsigned __int32)Client_Module_Location + 878608)() / 2;

	__int32 Screen_Height = Get_Screen_Size_Type((unsigned __int32)Client_Module_Location + 878576)() / 2;

	Uber_Alles(0, Screen_Width - 1, Screen_Height);

	Uber_Alles(0, Screen_Width, Screen_Height - 1);

	Uber_Alles(0, Screen_Width + 1, Screen_Height);

	Uber_Alles(0, Screen_Width, Screen_Height + 1);

	Uber_Alles(0, Screen_Width - 1, Screen_Height - 1);

	Uber_Alles(0, Screen_Width + 1, Screen_Height - 1);

	Uber_Alles(0, Screen_Width - 1, Screen_Height + 1);

	Uber_Alles(0, Screen_Width + 1, Screen_Height + 1);

	Uber_Alles(255, Screen_Width, Screen_Height);

	Rotation_Angle = __builtin_remainderf(Rotation_Angle - (*(Global_Variables_Structure**)((unsigned __int32)Client_Module_Location + 4825720))->Frame_Time * Interface_Uber_Alles_Speed.Integer, 180);
}