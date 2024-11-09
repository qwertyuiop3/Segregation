#include <Windows.h>

#include <cstdio>

#include "Byte_Manager/Byte_Manager.hpp"

#include "Redirection_Manager/Redirection_Manager.hpp"

void* Engine_Module;

void* Client_Module;

#include "Delimited_Interface.hpp"

#include "Extended_Interface.hpp"

#include <unordered_map>

#include "Post_Network_Data_Received.hpp"

#pragma comment(lib, "WinMM.Lib")

#include "Sounds.hpp"

#include "Event_Processor.hpp"

#include "Entity_Time_Received.hpp"

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
				DWORD Identifier;

				if (GetWindowThreadProcessId(FindWindowW(nullptr, L"Garry's Mod (x64)"), &Identifier) != 0)
				{
					void* Process = OpenProcess(PROCESS_ALL_ACCESS, 0, Identifier);

					void* Remote_Path = VirtualAllocEx(Process, nullptr, 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

					wchar_t Local_Path[MAX_PATH];

					GetModuleFileNameW(This_Module, Local_Path, sizeof(Local_Path));

					WriteProcessMemory(Process, Remote_Path, Local_Path, sizeof(Local_Path), nullptr);

					WaitForSingleObject(CreateRemoteThread(Process, nullptr, 0, (LPTHREAD_START_ROUTINE)LoadLibraryW, Remote_Path, 0, nullptr), INFINITE);

					VirtualFreeEx(Process, Remote_Path, 0, MEM_RELEASE);
				}
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

				DWORD Characters_Written;

				FillConsoleOutputAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED, Console_Screen_Buffer_Information.dwSize.X * Console_Screen_Buffer_Information.dwSize.Y, Top_Left, &Characters_Written);

				Engine_Module = GetModuleHandleW(L"engine.dll");

				Client_Module = GetModuleHandleW(L"client.dll");

				_putws(L"[ + ] Delimit Interface");
				{
					using Install_Interface_Handler_Type = void(*)(Interface_Structure* Interface, void* Handler, __int8 Invoke);

					void* Install_Interface_Handler = Byte_Manager::Find_Bytes(15855, (unsigned __int8*)Engine_Module, 9489070461722959066ull);

					Install_Interface_Handler_Type((unsigned __int64)Install_Interface_Handler)(Find_Interface((char*)"sv_cheats"), (void*)Force_Interface_Value, 1);

					Install_Interface_Handler_Type((unsigned __int64)Install_Interface_Handler)(Find_Interface((char*)"sv_allowcslua"), (void*)Force_Interface_Value, 1);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Byte_Manager::Find_Bytes(4832327113591360991, (unsigned __int8*)Engine_Module, 8537831801160118899) - 9), 1, 235);
				}

				_putws(L"[ + ] Extend Interface");
				{
					Implement_Extended_Interface();
				}

				_putws(L"[ + ] Events");
				{
					Byte_Manager::Set_Bytes(0, Byte_Manager::Find_Bytes(16777185, (unsigned __int8*)Client_Module, 12126569767325379908ull), 1, 195);

					Post_Network_Data_Received_Manager.Redirect_Function(0, Byte_Manager::Find_Bytes(6575677951, (unsigned __int8*)Client_Module, 18094813591132311429ull), (void*)Redirected_Post_Network_Data_Received);

					Byte_Manager::Set_Bytes(0, Byte_Manager::Find_Bytes(246301, (unsigned __int8*)Engine_Module, 10737773099336612120ull), 1, 235);

					void* Event_Listener = (void*)malloc(sizeof(void*));

					void* Event_Listener_Table = malloc(sizeof(void*) * 2);

					*(void**)((unsigned __int64)Event_Listener_Table + 8) = (void*)Event_Processor;

					*(void**)Event_Listener = Event_Listener_Table;

					using Add_Listener_Type = __int8(*)(void* Event_Manager, void* Listener, char* Event, void* Unknown_Parameter);

					void* Add_Listener = Byte_Manager::Find_Bytes(253935, (unsigned __int8*)Engine_Module, 8835901034313384778);

					void* Event_Manager = Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(31623, (unsigned __int8*)Engine_Module, 11190410533011393613ull), 3);

					Add_Listener_Type((unsigned __int64)Add_Listener)(Event_Manager, Event_Listener, (char*)"player_hurt", nullptr);

					Add_Listener_Type((unsigned __int64)Add_Listener)(Event_Manager, Event_Listener, (char*)"entity_killed", nullptr);

					void* Entity_Time_Received_Reference = (void*)((unsigned __int64)Byte_Manager::Solve_Relative((void*)((unsigned __int64)Byte_Manager::Find_Bytes(2168606945952456417, (unsigned __int8*)Client_Module, 16499196670633112084ull) - 7), 3) + 48);
					
					Original_Entity_Time_Received = *(void**)Entity_Time_Received_Reference;
					
					*(void**)Entity_Time_Received_Reference = (void*)Entity_Time_Received;

					*(void**)((unsigned __int64)Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(7918423844548743, (unsigned __int8*)Client_Module, 15881718154251215618ull), 3) + 48) = (void*)Player_Tick_Received;

					Write_Events_Manager.Redirect_Function(3, Byte_Manager::Find_Bytes(245231, (unsigned __int8*)Engine_Module, 14568127874725401427ull), (void*)Redirected_Write_Events);

					Shutdown_Manager.Redirect_Function(1, Byte_Manager::Find_Bytes(3567, (unsigned __int8*)Engine_Module, 15346061040490566347ull), (void*)Redirected_Shutdown);

					Post_Data_Update_Manager.Redirect_Function(0, Byte_Manager::Find_Bytes(2129702994911, (unsigned __int8*)Client_Module, 8519043785474729670), (void*)Redirected_Post_Data_Update);
				}

				_putws(L"[ + ] Interpolation");
				{
					Interpolate_Manager.Redirect_Function(1, Byte_Manager::Find_Bytes(1983, (unsigned __int8*)Client_Module, 15847880666414787410ull), (void*)Redirected_Interpolate);
				}

				_putws(L"[ + ] Animations");
				{
					Byte_Manager::Set_Bytes(0, Byte_Manager::Find_Bytes(4448707, (unsigned __int8*)Client_Module, 2780369489983663503), 6, 144);

					Update_Animation_Manager.Redirect_Function(2, Byte_Manager::Find_Bytes(11169853674457055, (unsigned __int8*)Client_Module, 13933784727300876964ull), (void*)Redirected_Update_Animation);

					Update_Animation_State_Manager.Redirect_Function(1, Byte_Manager::Find_Bytes(16653807, (unsigned __int8*)Client_Module, 11528163788009019714ull), (void*)Redirected_Update_Animation_State);

					Compute_Torso_Rotation_Manager.Redirect_Function(0, Byte_Manager::Find_Bytes(66567663, (unsigned __int8*)Client_Module, 5523300960910562887), (void*)Redirected_Compute_Torso_Rotation);

					Byte_Manager::Set_Bytes(0, Byte_Manager::Find_Bytes(2031, (unsigned __int8*)Client_Module, 12095624162194331321ull), 1, 195);

					Restart_Gesture_Manager.Redirect_Function(0, Byte_Manager::Find_Bytes(4079, (unsigned __int8*)Client_Module, 10267512153074347694ull), (void*)Redirected_Restart_Gesture);
				}

				_putws(L"[ + ] Prediction");
				{
					Byte_Manager::Set_Bytes(0, Byte_Manager::Find_Bytes(3611, (unsigned __int8*)Client_Module, 11831879960585716136ull), 9, 144);

					Byte_Manager::Set_Bytes(0, Byte_Manager::Find_Bytes(33348587037, (unsigned __int8*)Client_Module, 15603247578755587463ull), 1, 235);

					Run_Simulation_Manager.Redirect_Function(1, Byte_Manager::Find_Bytes(32488943, (unsigned __int8*)Client_Module, 6802517354955400393), (void*)Redirected_Run_Simulation);

					Setup_Move_Manager.Redirect_Function(0, Byte_Manager::Find_Bytes(255, (unsigned __int8*)Client_Module, 14902868146442072631ull), (void*)Redirected_Setup_Move);

					Finish_Move_Manager.Redirect_Function(4, Byte_Manager::Find_Bytes(502775279, (unsigned __int8*)Client_Module, 1688265399167102076), (void*)Redirected_Finish_Move);

					Fire_Bullets_Manager.Redirect_Function(2, Byte_Manager::Find_Bytes(231359, (unsigned __int8*)Client_Module, 4027704381885905114), (void*)Redirected_Fire_Bullets);
				}

				_putws(L"[ + ] Network");
				{
					Read_Packets_Manager.Redirect_Function(0, (void*)((unsigned __int64)Byte_Manager::Find_Bytes(1207984527359656951, (unsigned __int8*)Engine_Module, 791890331715239353) - 6), (void*)Redirected_Read_Packets);

					Move_Manager.Redirect_Function(0, Byte_Manager::Find_Bytes(266406015, (unsigned __int8*)Engine_Module, 3194732367554632559), (void*)Redirected_Move);

					unsigned __int8 Send_Move_Bytes[5] = { 233, 220 };

					Byte_Manager::Copy_Bytes(0, Byte_Manager::Find_Bytes(895, (unsigned __int8*)Engine_Module, 14445930051567068677ull), sizeof(Send_Move_Bytes), Send_Move_Bytes);

					Send_Move_Manager.Redirect_Function(2, Byte_Manager::Find_Bytes(3599, (unsigned __int8*)Engine_Module, 14280183856799702616ull), (void*)Redirected_Send_Move);

					Packet_Start_Manager.Redirect_Function(0, Byte_Manager::Find_Bytes(502260163, (unsigned __int8*)Engine_Module, 1280923722067716817), (void*)Redirected_Packet_Start);
				}

				_putws(L"[ + ] Input");
				{
					Byte_Manager::Set_Bytes(0, Byte_Manager::Find_Bytes(31, (unsigned __int8*)Client_Module, 7935025703931082227), 4, 144);

					Copy_Command_Manager.Redirect_Function(0, Byte_Manager::Find_Bytes(28911, (unsigned __int8*)Client_Module, 1688862236286034043), (void*)Redirected_Copy_Command);
				}

				_putws(L"[ + ] View Effects");
				{
					Byte_Manager::Set_Bytes(0, Byte_Manager::Find_Bytes(255, (unsigned __int8*)Client_Module, 15837355970143546918ull), 52, 144);

					Run_Command_Manager.Redirect_Function(4, Byte_Manager::Find_Bytes(16642457071, (unsigned __int8*)Client_Module, 4919264149733177098), (void*)Redirected_Run_Command);
				}

				_putws(L"[ + ] Crosshair");
				{
					Draw_Crosshair_Manager.Redirect_Function(Byte_Manager::Find_Bytes(31, (unsigned __int8*)Client_Module, 15200820684421834831ull), (void*)Redirected_Draw_Crosshair);
				}

				_putws(L"[ + ] Materials");
				{
					Precache_Manager.Redirect_Function(0, (void*)((unsigned __int64)GetModuleHandleW(L"materialsystem.dll") + 64576), (void*)Redirected_Precache);

					Byte_Manager::Set_Bytes(0, Byte_Manager::Find_Bytes(445, (unsigned __int8*)Client_Module, 16324833799701554475ull), 1, 116);

					Byte_Manager::Set_Bytes(0, Byte_Manager::Find_Bytes(4333495, (unsigned __int8*)Client_Module, 2994719452162294487), 4, 144);
				}
			}
		}
	}

	return 1;
}