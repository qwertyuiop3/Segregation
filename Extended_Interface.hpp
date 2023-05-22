struct Interface_Structure
{
	__int8 Additional_Bytes_1[36];

	char* String;

	__int8 Additional_Bytes_2[4];

	float Floating_Point;

	__int32 Integer;

	__int8 Additional_Bytes_3[20];
};

Interface_Structure Interface_Commentator;

void* Client_Module_Location;

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

Interface_Structure Interface_Angle_X;

Interface_Structure Interface_First_Choked_Angle_Y;

Interface_Structure Interface_Second_Choked_Angle_Y;

Interface_Structure Interface_Angle_Y;

Interface_Structure Interface_Uber_Alles_Scale;

Interface_Structure Interface_Uber_Alles_Speed;

void Implement_Extended_Interface()
{
	auto Create_Console_Variable = [](Interface_Structure* Variable, char* Name, char* Value, void* Handler)
	{
		using Create_Console_Variable_Type = void(__thiscall*)(Interface_Structure* Variable, char* Name, char* Value, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Handler);

		Create_Console_Variable_Type((unsigned __int32)Engine_Module_Location + 2390080)(Variable, Name, Value, nullptr, nullptr, Handler);

		wprintf(L"[ + ] %hs -> %p\n", Name, Variable);
	};

	Create_Console_Variable(&Interface_Commentator, (char*)"Commentator", (char*)"1", nullptr);

	Client_Module_Location = GetModuleHandleW(L"client.dll");

	using Create_Console_Command_Type = void(__thiscall*)(Interface_Structure* Variable, char* Name, void* Handler, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3);

	Create_Console_Command_Type((unsigned __int32)Client_Module_Location + 2852496)(&Interface_Get_Priorities, (char*)"Get_Priorities", (void*)Get_Priorities, nullptr, nullptr, nullptr);

	wprintf(L"[ + ] Get_Priorities %p\n", &Interface_Get_Priorities);

	Create_Console_Variable(&Interface_Set_Priority, (char*)"Set_Priority", (char*)"1 0", (void*)Set_Priority);

	Create_Console_Variable(&Interface_Bruteforce_Memory_Tolerance, (char*)"Bruteforce_Memory_Tolerance", (char*)"0", (void*)Bruteforce_Reset_Memory_Tolerance);

	Create_Console_Variable(&Interface_Bruteforce_Tolerance, (char*)"Bruteforce_Tolerance", (char*)"0", (void*)Bruteforce_Reset_Tolerance);

	Create_Console_Variable(&Interface_Bruteforce, (char*)"Bruteforce", (char*)"1", (void*)Bruteforce_Reset);

	Create_Console_Variable(&Interface_Bruteforce_Angles, (char*)"Bruteforce_Angles", (char*)"0, -45, 45, -90, 90", (void*)Bruteforce_Set_Angles);

	Bruteforce_Set_Angles(&Interface_Bruteforce_Angles);

	Create_Console_Variable(&Interface_Alternative, (char*)"Alternative", (char*)"1", nullptr);

	Create_Console_Variable(&Interface_Minimum_Choked_Commands, (char*)"Minimum_Choked_Commands", (char*)"2", nullptr);

	Create_Console_Variable(&Interface_Maximum_Choked_Commands, (char*)"Maximum_Choked_Commands", (char*)"21", nullptr);

	Create_Console_Variable(&Interface_Aim_Intersection, (char*)"Aim_Intersection", (char*)"0", nullptr);

	Create_Console_Variable(&Interface_Aim_Height, (char*)"Aim_Height", (char*)"0.9", nullptr);

	Create_Console_Variable(&Interface_Angle_X, (char*)"Angle_X", (char*)"180", nullptr);

	Create_Console_Variable(&Interface_First_Choked_Angle_Y, (char*)"First_Choked_Angle_Y", (char*)"46", nullptr);

	Create_Console_Variable(&Interface_Second_Choked_Angle_Y, (char*)"Second_Choked_Angle_Y", (char*)"136", nullptr);

	Create_Console_Variable(&Interface_Angle_Y, (char*)"Angle_Y", (char*)"-135", nullptr);

	Create_Console_Variable(&Interface_Uber_Alles_Scale, (char*)"Uber_Alles_Scale", (char*)"16", nullptr);

	Create_Console_Variable(&Interface_Uber_Alles_Speed, (char*)"Uber_Alles_Speed", (char*)"192", nullptr);
}