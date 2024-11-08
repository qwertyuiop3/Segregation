#include <Windows.h>

#include <cstdio>

#define ZYDIS_STATIC_BUILD

#include "safetyhook/safetyhook.hpp"

#include "Byte_Manager/Byte_Manager.hpp"

void* Engine_Module;

void* Client_Module;

#include "Delimited_Interface.hpp"

#include "Extended_Interface.hpp"

#include <unordered_map>

#include "Post_Network_Data_Received.hpp"

#pragma comment(lib, "WinMM.Lib")

#include "Sounds.hpp"

#include "Event_Processor.hpp"

#include "Player_Tick_Received.hpp"

#include "Write_Events.hpp"

#include "Shutdown.hpp"

#include "Post_Data_Update.hpp"

#include "Interpolate.hpp"

#include "Update_Animation.hpp"

#include "Update_Animation_State.hpp"

#include "Compute_Torso_Rotation.hpp"

#include "Restart_Gesture.hpp"

#include "Run_Simulation.hpp"

#include "Setup_Move.hpp"

#include <algorithm>

#include "Finish_Move.hpp"

#include "Fire_Bullets.hpp"

#include "Read_Packets.hpp"

#include "Move.hpp"

#include "Send_Move.hpp"

#include "Packet_Start.hpp"

#include "Run_Command.hpp"

#include <vector>

#include "Copy_Command.hpp"

#include "Draw_Crosshair.hpp"

#include "Precache.hpp"

__int32 __stdcall DllMain(HMODULE This_Module, unsigned __int32 Call_Reason, void* Reserved)
{
	if (Call_Reason == DLL_PROCESS_DETACH)
	{
		__fastfail(EXIT_SUCCESS);
	}
	else
	{
		if (Call_Reason == DLL_PROCESS_ATTACH)
		{
			if (GetModuleHandleW(L"gmod.exe") == nullptr)
			{
				HWND Window_Handle = FindWindowW(nullptr, L"Garry's Mod (x64)");
				
				if (Window_Handle == nullptr)
				{
					return 1;
				}
				
				DWORD Process_Id;
				
				GetWindowThreadProcessId(Window_Handle, &Process_Id);
				
				void* Process = OpenProcess(PROCESS_ALL_ACCESS, 0, Process_Id);

				void* Remote_Path = VirtualAllocEx(Process, nullptr, 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

				wchar_t Local_Path[MAX_PATH];

				GetModuleFileNameW(This_Module, Local_Path, sizeof(Local_Path));

				WriteProcessMemory(Process, Remote_Path, Local_Path, sizeof(Local_Path), nullptr);

				WaitForSingleObject(CreateRemoteThread(Process, nullptr, 0, (LPTHREAD_START_ROUTINE)LoadLibraryW, Remote_Path, 0, nullptr), INFINITE);

				VirtualFreeEx(Process, Remote_Path, 0, MEM_RELEASE);
			}
			else
			{
				Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)LoadLibraryW(L"vaudio_speex.dll") + 4816), 1, 195);

				AllocConsole();

				SetConsoleTitleW(L"Segregation");

				_wfreopen(L"CONOUT$", L"w", stdout);

				SetConsoleOutputCP(65001);

				HANDLE Standard_Output_Handle = GetStdHandle(STD_OUTPUT_HANDLE);

				CONSOLE_FONT_INFOEX Console_Font_Information;

				Console_Font_Information.cbSize = sizeof(CONSOLE_FONT_INFOEX);

				Console_Font_Information.nFont = 0;

				Console_Font_Information.dwFontSize.X = 0;

				Console_Font_Information.dwFontSize.Y = 12;

				Console_Font_Information.FontFamily = FF_DONTCARE;

				Console_Font_Information.FontWeight = FW_NORMAL;

				wcscpy(Console_Font_Information.FaceName, L"Terminal");

				SetCurrentConsoleFontEx(Standard_Output_Handle, 0, &Console_Font_Information);

				CONSOLE_CURSOR_INFO Console_Cursor_Information;

				Console_Cursor_Information.bVisible = 0;

				Console_Cursor_Information.dwSize = sizeof(Console_Cursor_Information);

				SetConsoleTextAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED);

				SetConsoleCursorInfo(Standard_Output_Handle, &Console_Cursor_Information);

				CONSOLE_SCREEN_BUFFER_INFO Console_Screen_Buffer_Information;

				GetConsoleScreenBufferInfo(Standard_Output_Handle, &Console_Screen_Buffer_Information);

				COORD Top_Left = { };

				DWORD Characters_Written_Count;

				FillConsoleOutputAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED, Console_Screen_Buffer_Information.dwSize.X * Console_Screen_Buffer_Information.dwSize.Y, Top_Left, &Characters_Written_Count);

				Engine_Module = GetModuleHandleW(L"engine.dll");

				Client_Module = GetModuleHandleW(L"client.dll");

				_putws(L"[ + ] Delimit Interface");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 507684), 161, 144);
					
					void* Interface_Manager = *(void**)((unsigned __int64)Engine_Module + 12887056);

					using Find_Interface_Type = Interface_Structure*(**)(void* Interface_Manager, char* Name);

					using Install_Interface_Handler_Type = void(*)(Interface_Structure* Interface, void* Handler, __int8 Invoke);

					Install_Interface_Handler_Type((unsigned __int64)Engine_Module + 2701696)((*Find_Interface_Type(*(unsigned __int64*)Interface_Manager + 136))(Interface_Manager, (char*)"sv_cheats"), (void*)Force_Interface_Value, 1);

					Install_Interface_Handler_Type((unsigned __int64)Engine_Module + 2701696)((*Find_Interface_Type(*(unsigned __int64*)Interface_Manager + 136))(Interface_Manager, (char*)"sv_allowcslua"), (void*)Force_Interface_Value, 1);
					
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Engine_Module + 1576396), 1, 235);
				}

				_putws(L"[ + ] Extend Interface");
				{
					Implement_Extended_Interface();
				}

				_putws(L"[ + ] Events");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 1747518), 1, 195);

					Original_Post_Network_Data_Received_Caller = safetyhook::create_inline((void*)((unsigned __int64)Client_Module + 2756688), (void*)Redirected_Post_Network_Data_Received);
					
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Engine_Module + 625578), 1, 235);

					void* Event_Listener = (void*)malloc(sizeof(void*));

					void* Event_Listener_Table = malloc(sizeof(void*) * 2);

					*(void**)((unsigned __int64)Event_Listener_Table + 8) = (void*)Event_Processor;

					*(void**)Event_Listener = Event_Listener_Table;

					using Add_Listener_Type = __int8(*)(void* Event_Manager, void* Listener, char* Event, void* Unknown_Parameter);

					Add_Listener_Type((unsigned __int64)Engine_Module + 1735056)((void*)((unsigned __int64)Engine_Module + 5022640), Event_Listener, (char*)"player_hurt", nullptr);

					Add_Listener_Type((unsigned __int64)Engine_Module + 1735056)((void*)((unsigned __int64)Engine_Module + 5022640), Event_Listener, (char*)"entity_killed", nullptr);

					*(void**)((unsigned __int64)Client_Module + 9400320) = (void*)Player_Tick_Received;

					Original_Write_Events_Caller = safetyhook::create_inline((void*)((unsigned __int64)Engine_Module + 1745280), (void*)Redirected_Write_Events);
					
					Original_Shutdown_Caller = safetyhook::create_inline((void*)((unsigned __int64)Engine_Module + 1968192), (void*)Redirected_Shutdown);
					
					Original_Post_Data_Update_Caller = safetyhook::create_inline((void*)((unsigned __int64)Client_Module + 469664), (void*)Redirected_Post_Data_Update);
				}

				_putws(L"[ + ] Interpolation");
				{
					Original_Interpolate_Caller = safetyhook::create_inline((void*)((unsigned __int64)Client_Module + 1657280), (void*)Redirected_Interpolate);
				}

				_putws(L"[ + ] Animations");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 3430210), 6, 144);

					Original_Update_Animation_Caller = safetyhook::create_inline((void*)((unsigned __int64)Client_Module + 472512), (void*)Redirected_Update_Animation);

					Original_Update_Animation_State_Caller = safetyhook::create_inline((void*)((unsigned __int64)Client_Module + 3429968), (void*)Redirected_Update_Animation_State);

					Original_Compute_Torso_Rotation_Caller = safetyhook::create_inline((void*)((unsigned __int64)Client_Module + 3500896), (void*)Redirected_Compute_Torso_Rotation);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 1658944), 1, 195);
					
					Original_Restart_Gesture_Caller = safetyhook::create_inline((void*)((unsigned __int64)Client_Module + 3509696), (void*)Redirected_Restart_Gesture);
				}

				_putws(L"[ + ] Prediction");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 2754277), 9, 144);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 2762351), 1, 235);

					Original_Run_Simulation_Caller = safetyhook::create_inline((void*)((unsigned __int64)Client_Module + 2759888), (void*)Redirected_Run_Simulation);

					Original_Setup_Move_Caller = safetyhook::create_inline((void*)((unsigned __int64)Client_Module + 2761472), (void*)Redirected_Setup_Move);
					
					Original_Finish_Move_Caller = safetyhook::create_inline((void*)((unsigned __int64)Client_Module + 2754736), (void*)Redirected_Finish_Move);
					
					Original_Fire_Bullets_Caller = safetyhook::create_inline((void*)((unsigned __int64)Client_Module + 467472), (void*)Redirected_Fire_Bullets);
				}

				_putws(L"[ + ] Network");
				{
					Original_Read_Packets_Caller = safetyhook::create_inline((void*)((unsigned __int64)Engine_Module + 611440), (void*)Redirected_Read_Packets);
					
					Original_Move_Caller = safetyhook::create_inline((void*)((unsigned __int64)Engine_Module + 609776), (void*)Redirected_Move);
					
					unsigned __int8 Send_Move_Bytes[5] = { 233, 220 };

					Byte_Manager::Copy_Bytes(0, (void*)((unsigned __int64)Engine_Module + 610213), sizeof(Send_Move_Bytes), Send_Move_Bytes);
					
					Original_Send_Move_Caller = safetyhook::create_inline((void*)((unsigned __int64)Engine_Module + 2739664), (void*)Redirected_Send_Move);
					
					Original_Packet_Start_Caller = safetyhook::create_inline((void*)((unsigned __int64)Engine_Module + 2106672), (void*)Redirected_Packet_Start);
				}

				_putws(L"[ + ] Input");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 2533352), 4, 144);
					
					Original_Copy_Command_Caller = safetyhook::create_inline( (void*)((unsigned __int64)Client_Module + 2382624), (void*)Redirected_Copy_Command);
				}

				_putws(L"[ + ] View Effects");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 1490901), 52, 144);

					Original_Run_Command_Caller = safetyhook::create_inline((void*)((unsigned __int64)Client_Module + 2758768), (void*)Redirected_Run_Command);
				}

				_putws(L"[ + ] Crosshair");
				{
					Original_Draw_Crosshair_Caller = safetyhook::create_inline((void*)((unsigned __int64)Client_Module + 2461088), (void*)Redirected_Draw_Crosshair);
				}

				_putws(L"[ + ] Materials");
				{
					Original_Precache_Caller = safetyhook::create_inline((void*)((unsigned __int64)GetModuleHandleW(L"materialsystem.dll") + 64576), (void*)Redirected_Precache);
					
					unsigned __int8 Skybox_Bytes[3] = { 50, 219, 144 };

					Byte_Manager::Copy_Bytes(0, (void*)((unsigned __int64)Client_Module + 3125399), sizeof(Skybox_Bytes), Skybox_Bytes);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 3116654), 4, 144);
				}
			}
		}
	}

	return 1;
}