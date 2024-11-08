Interface_Structure Interface_Commentator;

Interface_Structure Interface_Get_Priorities;

#include "Priority.hpp"

Interface_Structure Interface_Set_Priority;

Interface_Structure Interface_Bruteforce_Memory_Tolerance;

Interface_Structure Interface_Bruteforce_Tolerance;

#include "Bruteforce.hpp"

Interface_Structure Interface_Bruteforce;

Interface_Structure Interface_Bruteforce_Angles;

Interface_Structure Interface_Alternative;

Interface_Structure Interface_Minimum_Choked_Commands;

Interface_Structure Interface_Maximum_Choked_Commands;

Interface_Structure Interface_Aim_Intersection;

Interface_Structure Interface_Aim_Height;

Interface_Structure Interface_Aim_Hitgroup;

Interface_Structure Interface_Angle_X;

Interface_Structure Interface_Extrapolation;

Interface_Structure Interface_First_Choked_Angle_Y;

Interface_Structure Interface_Second_Choked_Angle_Y;

Interface_Structure Interface_Angle_Y;

Interface_Structure Interface_Team_Check;

Interface_Structure Interface_Uber_Alles_Scale;

Interface_Structure Interface_Uber_Alles_Speed;

void Implement_Extended_Interface()
{
	auto Create_Console_Interface = [](Interface_Structure* Interface, char* Name, char* Value, void* Handler) -> void
	{
		if (Value == nullptr)
		{
			using Create_Console_Command_Type = void(*)(Interface_Structure* Interface, char* Name, void* Handler, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3);

			Create_Console_Command_Type((unsigned __int64)Client_Module + 5172400)(Interface, Name, Handler, nullptr, nullptr, nullptr);
		}
		else
		{
			using Create_Console_Variable_Type = void(*)(Interface_Structure* Interface, char* Name, char* Value, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Handler);

			Create_Console_Variable_Type((unsigned __int64)Engine_Module + 2698480)(Interface, Name, Value, nullptr, nullptr, Handler);
		}

		wprintf(L"[ + ] %hs -> %p\n", Name, Interface);
	};

	#define Pointer_Name(Interface) &Interface, (char*)#Interface + 10

	Create_Console_Interface(Pointer_Name(Interface_Commentator), (char*)"1", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Get_Priorities), nullptr, (void*)Get_Priorities);

	Create_Console_Interface(Pointer_Name(Interface_Set_Priority), (char*)"1 0", (void*)Set_Priority);

	Create_Console_Interface(Pointer_Name(Interface_Bruteforce_Memory_Tolerance), (char*)"0", (void*)Bruteforce_Reset_Memory_Tolerance);

	Create_Console_Interface(Pointer_Name(Interface_Bruteforce_Tolerance), (char*)"0", (void*)Bruteforce_Reset_Tolerance);

	Create_Console_Interface(Pointer_Name(Interface_Bruteforce), (char*)"1", (void*)Bruteforce_Reset);

	Create_Console_Interface(Pointer_Name(Interface_Bruteforce_Angles), (char*)"0, -30, 30, -60, 60, -90, 90, -120, 120, -150, 150, -179, 179", (void*)Bruteforce_Set_Angles);

	Bruteforce_Set_Angles((Interface_Structure*)((unsigned __int64)&Interface_Bruteforce_Angles + 48));

	Create_Console_Interface(Pointer_Name(Interface_Alternative), (char*)"1", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Minimum_Choked_Commands), (char*)"2", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Maximum_Choked_Commands), (char*)"21", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Aim_Intersection), (char*)"0", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Aim_Height), (char*)"0.9", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Aim_Hitgroup), (char*)"1", nullptr);
	
	Create_Console_Interface(Pointer_Name(Interface_Extrapolation), (char*)"1", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Angle_X), (char*)"180", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_First_Choked_Angle_Y), (char*)"-130", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Second_Choked_Angle_Y), (char*)"-130", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Angle_Y), (char*)"80", nullptr);
	
	Create_Console_Interface(Pointer_Name(Interface_Team_Check), (char*)"1", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Uber_Alles_Scale), (char*)"16", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Uber_Alles_Speed), (char*)"192", nullptr);
}