#include <Windows.h>

#include <TlHelp32.h>

#include <cstdio>

#define Bits_32

#include "Byte_Manager/Byte_Manager.hpp"

#include "Redirection_Manager/Redirection_Manager.hpp"

void* Engine_Module;

#include "Extended_Interface.hpp"

#include "Post_Entity_Packet_Received.hpp"

#pragma comment(lib, "WinMM.Lib")

#include "Sounds.hpp"

#include "Event_Processor.hpp"

#include "Write_Events.hpp"

#include "Interpolate.hpp"

#include "Update_Animation.hpp"

#include "Compute_Torso_Rotation.hpp"

#include "Compute_First_Command_To_Execute.hpp"

#include "Run_Simulation.hpp"

#include "Setup_Move.hpp"

#include "Player_Move.hpp"

#include <algorithm>

#include "Finish_Move.hpp"

#include "Item_Post_Frame.hpp"

#include "Store_Prediction_Results.hpp"

#include "Read_Packets.hpp"

#include "Move.hpp"

#include "Send_Move.hpp"

#include "Packet_Start.hpp"

#include <vector>

#include "Copy_Command.hpp"

#include "Draw_Crosshair.hpp"

#include "Precache.hpp"

#include "Calculate_Override_Model_Index.hpp"

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
			if (GetModuleHandleW(L"hl2.exe") == nullptr)
			{
				void* Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

				PROCESSENTRY32W Snapshot_Entry;

				Snapshot_Entry.dwSize = sizeof(Snapshot_Entry);

				Traverse_Snapshot_Label:
				{
					if (Process32NextW(Snapshot, &Snapshot_Entry) == 0)
					{
						return 1;
					}

					if (wcscmp(Snapshot_Entry.szExeFile, L"hl2.exe") != 0)
					{
						goto Traverse_Snapshot_Label;
					}
				}

				void* Process = OpenProcess(PROCESS_ALL_ACCESS, 0, Snapshot_Entry.th32ProcessID);

				void* Remote_Path = VirtualAllocEx(Process, nullptr, 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

				wchar_t Local_Path[MAX_PATH];

				GetModuleFileNameW(This_Module, Local_Path, sizeof(Local_Path));

				WriteProcessMemory(Process, Remote_Path, Local_Path, sizeof(Local_Path), nullptr);

				WaitForSingleObject(CreateRemoteThread(Process, nullptr, 0, (LPTHREAD_START_ROUTINE)LoadLibraryW, Remote_Path, 0, nullptr), INFINITE);

				VirtualFreeEx(Process, Remote_Path, 0, MEM_RELEASE);
			}
			else
			{
				Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)LoadLibraryW(L"vaudio_speex.dll") + 6832), 1, 195);

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

				COORD Top_Left =
				{
					0,

					0
				};

				DWORD Characters_Written_Count;

				FillConsoleOutputAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED, Console_Screen_Buffer_Information.dwSize.X * Console_Screen_Buffer_Information.dwSize.Y, Top_Left, &Characters_Written_Count);

				Engine_Module = GetModuleHandleW(L"engine.dll");

				_putws(L"[ + ] Delimit Interface");
				{
					unsigned __int8 Cheat_Flag_Bytes[5] = { 254, 64, 48, 144, 235 };

					Byte_Manager::Copy_Bytes(1, (void*)((unsigned __int32)Engine_Module + 1359156), sizeof(Cheat_Flag_Bytes), Cheat_Flag_Bytes);

					*(__int8*)((unsigned __int32)Engine_Module + 6384240) = 1;

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Engine_Module + 1565004), 1, 235);
				}

				_putws(L"[ + ] Extend Interface");
				{
					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Engine_Module + 2391305), 2, 144);

					Implement_Extended_Interface();
				}

				_putws(L"[ + ] Events");
				{
					Redirection_Manager::Redirect_Function(Original_Post_Entity_Packet_Received_Caller, 0, (void*)((unsigned __int32)Client_Module + 1550256), 1, (void*)Redirected_Post_Entity_Packet_Received);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Engine_Module + 785516), 1, 235);

					void* Event_Listener = (void*)malloc(sizeof(void*));

					void* Event_Listener_Table = malloc(sizeof(void*) * 2);

					*(void**)((unsigned __int32)Event_Listener_Table + 4) = (void*)Event_Processor;

					*(void**)Event_Listener = Event_Listener_Table;

					using Add_Listener_Type = __int8(__thiscall*)(void* Event_Manager, void* Listener, char* Event, void* Unknown_Parameter);

					Add_Listener_Type((unsigned __int32)Engine_Module + 1665088)((void*)((unsigned __int32)Engine_Module + 6512952), Event_Listener, (char*)"player_hurt", nullptr);

					Add_Listener_Type((unsigned __int32)Engine_Module + 1665088)((void*)((unsigned __int32)Engine_Module + 6512952), Event_Listener, (char*)"player_death", nullptr);

					Add_Listener_Type((unsigned __int32)Engine_Module + 1665088)((void*)((unsigned __int32)Engine_Module + 6512952), Event_Listener, (char*)"bullet_impact", nullptr);

					Redirection_Manager::Redirect_Function(Original_Write_Events_Caller, 0, (void*)((unsigned __int32)Engine_Module + 1672192), 1, (void*)Redirected_Write_Events);
				}

				_putws(L"[ + ] Interpolation");
				{
					Redirection_Manager::Redirect_Function(Original_Interpolate_Caller, 0, (void*)((unsigned __int32)Client_Module + 547872), 1, (void*)Redirected_Interpolate);
				}

				_putws(L"[ + ] Animations");
				{
					Redirection_Manager::Redirect_Function(Original_Update_Animation_Caller, 4, (void*)((unsigned __int32)Client_Module + 1915328), 1, (void*)Redirected_Update_Animation);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 1915365), 1, 235);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 601904), 2, 144);

					Redirection_Manager::Redirect_Function(Original_Compute_Torso_Rotation_Caller, 0, (void*)((unsigned __int32)Client_Module + 376048), 1, (void*)Redirected_Compute_Torso_Rotation);

					unsigned __int8 Maintain_Sequence_Transitions_Bytes[3] = { 194, 16, 0 };

					Byte_Manager::Copy_Bytes(1, (void*)((unsigned __int32)Client_Module + 549072), sizeof(Maintain_Sequence_Transitions_Bytes), Maintain_Sequence_Transitions_Bytes);
				}

				_putws(L"[ + ] Prediction");
				{
					static Prediction_Descriptor_Structure Original_Prediction_Descriptor;

					Prediction_Descriptor_Structure* Prediction_Descriptor = (Prediction_Descriptor_Structure*)((unsigned __int32)Client_Module + 4819316);

					Byte_Manager::Copy_Bytes(0, &Original_Prediction_Descriptor, sizeof(Prediction_Descriptor_Structure), Prediction_Descriptor);

					static Prediction_Field_Structure Prediction_Fields = { 1, (char*)"m_flVelocityModifier", { 5176 }, 1, 256, { }, sizeof(float), { }, 0.005f };

					Prediction_Descriptor->Fields = &Prediction_Fields;

					Prediction_Descriptor->Size = sizeof(Prediction_Fields) / sizeof(Prediction_Field_Structure);

					Prediction_Descriptor->Parent = &Original_Prediction_Descriptor;

					Redirection_Manager::Redirect_Function(Original_Compute_First_Command_To_Execute_Caller, 0, (void*)((unsigned __int32)Client_Module + 1548784), 1, (void*)Redirected_Compute_First_Command_To_Execute);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 1548805), 8, 144);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 1555313), 1, 235);

					Redirection_Manager::Redirect_Function(Original_Run_Simulation_Caller, 0, (void*)((unsigned __int32)Client_Module + 1552528), 1, (void*)Redirected_Run_Simulation);

					Redirection_Manager::Redirect_Function(Original_Setup_Move_Caller, 2, (void*)((unsigned __int32)Client_Module + 1553824), 1, (void*)Redirected_Setup_Move);

					Redirection_Manager::Redirect_Function(Original_Player_Move_Caller, 1, (void*)((unsigned __int32)Client_Module + 1945776), 1, (void*)Redirected_Player_Move);

					Redirection_Manager::Redirect_Function(Original_Finish_Move_Caller, 1, (void*)((unsigned __int32)Client_Module + 1549072), 1, (void*)Redirected_Finish_Move);

					Redirection_Manager::Redirect_Function(Original_Item_Post_Frame_Caller, 0, (void*)((unsigned __int32)Client_Module + 432656), 1, (void*)Redirected_Item_Post_Frame);

					Redirection_Manager::Redirect_Function(Original_Store_Prediction_Results_Caller, 4, (void*)((unsigned __int32)Client_Module + 1554880), 1, (void*)Redirected_Store_Prediction_Results);
				}

				_putws(L"[ + ] Network");
				{
					Redirection_Manager::Redirect_Function(Original_Read_Packets_Caller, 0, (void*)((unsigned __int32)Engine_Module + 771728), 1, (void*)Redirected_Read_Packets);

					Redirection_Manager::Redirect_Function(Original_Move_Caller, 0, (void*)((unsigned __int32)Engine_Module + 770528), 1, (void*)Redirected_Move);

					Redirection_Manager::Redirect_Function(1, (void*)((unsigned __int32)Engine_Module + 772928), (void*)Redirected_Send_Move);

					Redirection_Manager::Redirect_Function(Original_Packet_Start_Caller, 0, (void*)((unsigned __int32)Engine_Module + 2030944), 1, (void*)Redirected_Packet_Start);
				}

				_putws(L"[ + ] Input");
				{
					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 1343395), 3, 144);

					Redirection_Manager::Redirect_Function(Original_Copy_Command_Caller, 0, (void*)((unsigned __int32)Client_Module + 1177632), 1, (void*)Redirected_Copy_Command);
				}

				_putws(L"[ + ] View Effects");
				{
					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 430022), 52, 144);
				}

				_putws(L"[ + ] Crosshair");
				{
					Redirection_Manager::Redirect_Function(1, (void*)((unsigned __int32)Client_Module + 2156016), (void*)Redirected_Draw_Crosshair);
				}

				_putws(L"[ + ] Materials");
				{
					Redirection_Manager::Redirect_Function(Original_Precache_Caller, 5, (void*)((unsigned __int32)GetModuleHandleW(L"MaterialSystem.dll") + 239552), 1, (void*)Redirected_Precache);

					Redirection_Manager::Redirect_Function(1, (void*)((unsigned __int32)Client_Module + 582800), (void*)Redirected_Calculate_Override_Model_Index);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 1743076), 1, 0);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 1842904), 1, 235);

					unsigned __int8 Smoke_Bytes[3] = { 194, 8, 0 };

					Byte_Manager::Copy_Bytes(1, (void*)((unsigned __int32)Client_Module + 2311408), sizeof(Smoke_Bytes), Smoke_Bytes);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 1913184), 1, 195);
				}
			}
		}
	}

	return 1;
}