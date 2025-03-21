struct Interface_Structure
{
	__int8 Additional_Bytes_1[36];

	char* String;

	__int8 Additional_Bytes_2[48];

	float Get_Floating_Point()
	{
		using Get_Floating_Point_Type = float(__thiscall**)(Interface_Structure* Interface);

		return (*Get_Floating_Point_Type(*(unsigned __int32*)this + 48))(this);
	};

	__int32 Get_Integer()
	{
		using Get_Integer_Type = __int32(__thiscall**)(Interface_Structure* Interface);

		return (*Get_Integer_Type(*(unsigned __int32*)this + 52))(this);
	};
};

Interface_Structure Interface_Commentator;

void* Client_Module;

Interface_Structure Interface_Get_Priorities;

#include "Priority.hpp"

Interface_Structure Interface_Set_Priority;

Interface_Structure Interface_Bruteforce_Memory_Tolerance;

Interface_Structure Interface_Bruteforce_Tolerance;

#include "Bruteforce.hpp"

Interface_Structure Interface_Bruteforce;

Interface_Structure Interface_Bruteforce_Angles;

Interface_Structure Interface_Bruteforce_Relative;

Interface_Structure Interface_Bruteforce_Perpendicular;

Interface_Structure Interface_Target_On_Simulation;

Interface_Structure Interface_High_Jump;

Interface_Structure Interface_Alternative;

Interface_Structure Interface_Minimum_Choked_Commands;

Interface_Structure Interface_Maximum_Choked_Commands;

Interface_Structure Interface_Aim_Intersection;

Interface_Structure Interface_Aim_Height;

Interface_Structure Interface_Aim_Height_Step;

Interface_Structure Interface_Angle_X;

Interface_Structure Interface_Animated_Angle_Y;

Interface_Structure Interface_Angle_Y;

Interface_Structure Interface_Body_Update;

Interface_Structure Interface_Body_Angle_Y;

Interface_Structure Interface_Uber_Alles_Scale;

Interface_Structure Interface_Uber_Alles_Speed;

void Implement_Extended_Interface()
{
	Client_Module = GetModuleHandleW(L"client.dll");

	auto Create_Interface = [](Interface_Structure* Interface, char* Name, char* Value, void* Handler)
	{
		if (Value == nullptr)
		{
			using Create_Command_Type = void(__thiscall*)(Interface_Structure* Interface);

			*(void**)Interface = (void*)((unsigned __int32)Client_Module + 10287356);

			*(char**)((unsigned __int32)Interface + 12) = Name;

			*(void**)((unsigned __int32)Interface + 24) = Handler;

			Create_Command_Type((unsigned __int32)Client_Module + 7197248)(Interface);
		}
		else
		{
			using Create_Variable_Type = void(__thiscall*)(Interface_Structure* Interface, char* Name, char* Value, __int32 Flags, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4, void* Unknown_Parameter_5, void* Handler);

			*(void**)Interface = (void*)((unsigned __int32)Client_Module + 10287428);

			*(void**)((unsigned __int32)Interface + 24) = (void*)((unsigned __int32)Client_Module + 10287196);

			Create_Variable_Type((unsigned __int32)Engine_Module + 2954528)(Interface, Name, Value, 524288, nullptr, nullptr, nullptr, nullptr, nullptr, Handler);
		}

		wprintf(L"[ + ] %hs -> %p\n", Name, Interface);
	};

	#define Pointer_Name(Interface) &Interface, (char*)#Interface + 10

	Create_Interface(Pointer_Name(Interface_Commentator), (char*)"1", nullptr);

	Create_Interface(Pointer_Name(Interface_Get_Priorities), nullptr, (void*)Get_Priorities);

	Create_Interface(Pointer_Name(Interface_Set_Priority), (char*)"1 0", (void*)Set_Priority);

	Create_Interface(Pointer_Name(Interface_Bruteforce_Memory_Tolerance), (char*)"0", (void*)Bruteforce_Reset_Memory_Tolerance);

	Create_Interface(Pointer_Name(Interface_Bruteforce_Tolerance), (char*)"0", (void*)Bruteforce_Reset_Tolerance);

	Create_Interface(Pointer_Name(Interface_Bruteforce), (char*)"1", (void*)Bruteforce_Reset);

	Create_Interface(Pointer_Name(Interface_Bruteforce_Angles), (char*)"0, -60, 60", (void*)Bruteforce_Set_Angles);

	Create_Interface(Pointer_Name(Interface_Bruteforce_Relative), (char*)"0", nullptr);

	Create_Interface(Pointer_Name(Interface_Bruteforce_Perpendicular), (char*)"2", nullptr);

	Bruteforce_Set_Angles((Interface_Structure*)((unsigned __int32)&Interface_Bruteforce_Angles + 24));

	Create_Interface(Pointer_Name(Interface_Target_On_Simulation), (char*)"0", nullptr);

	Create_Interface(Pointer_Name(Interface_High_Jump), (char*)"1", nullptr);

	Create_Interface(Pointer_Name(Interface_Alternative), (char*)"0", nullptr);

	Create_Interface(Pointer_Name(Interface_Minimum_Choked_Commands), (char*)"2", nullptr);

	Create_Interface(Pointer_Name(Interface_Maximum_Choked_Commands), (char*)"14", nullptr);

	Create_Interface(Pointer_Name(Interface_Aim_Intersection), (char*)"0", nullptr);

	Create_Interface(Pointer_Name(Interface_Aim_Height), (char*)"0.95", nullptr);

	Create_Interface(Pointer_Name(Interface_Aim_Height_Step), (char*)"0.05", nullptr);

	Create_Interface(Pointer_Name(Interface_Angle_X), (char*)"540", nullptr);

	Create_Interface(Pointer_Name(Interface_Animated_Angle_Y), (char*)"135", nullptr);

	Create_Interface(Pointer_Name(Interface_Angle_Y), (char*)"-45", nullptr);

	Create_Interface(Pointer_Name(Interface_Body_Update), (char*)"1", nullptr);

	Create_Interface(Pointer_Name(Interface_Body_Angle_Y), (char*)"180", nullptr);

	Create_Interface(Pointer_Name(Interface_Uber_Alles_Scale), (char*)"16", nullptr);

	Create_Interface(Pointer_Name(Interface_Uber_Alles_Speed), (char*)"192", nullptr);
}