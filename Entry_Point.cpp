#include <Windows.h>

#include <TlHelp32.h>

#include <cstdio>

#include "Byte_Manager/Byte_Manager.hpp"

#include "Redirection_Manager/Redirection_Manager.hpp"

void* Engine_Module;

#include "Extended_Interface.hpp"

#include <unordered_map>

#include "Post_Network_Data_Received.hpp"

#pragma comment(lib, "WinMM.Lib")

#include "Sounds.hpp"

#include "Event_Processor.hpp"

#include "Write_Events.hpp"

#include "Interpolate.hpp"

#include "Update_Animation.hpp"

#include "Compute_Torso_Rotation.hpp"

#include <algorithm>

#include "Finish_Move.hpp"

#include "Item_Post_Frame.hpp"

#include "Read_Packets.hpp"

#include "Move.hpp"

#include "Send_Move.hpp"

#include "Send_Datagram.hpp"

#include "Packet_Start.hpp"

#include <vector>

#include "Copy_Command.hpp"

#include "Draw_Crosshair.hpp"

#include "Precache.hpp"

#include "Calculate_Override_Model.hpp"

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
			if (GetModuleHandleW(L"cstrike_win64.exe") == nullptr)
			{
				DWORD Identifier;

				if (GetWindowThreadProcessId(FindWindowW(nullptr, L"Counter-Strike Source - Direct3D 9 - 64 Bit"), &Identifier) != 0)
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
				AllocConsole();

				SetConsoleTitleW(L"Segregation");

				_wfreopen(L"CONOUT$", L"w", stdout);

				SetConsoleOutputCP(65001);

				HANDLE Standard_Output_Handle = GetStdHandle(STD_OUTPUT_HANDLE);

				CONSOLE_FONT_INFOEX Console_Font_Information = { sizeof(CONSOLE_FONT_INFOEX), 0, { 0, 12 }, FF_DONTCARE, FW_NORMAL, { L"Terminal" } };

				SetCurrentConsoleFontEx(Standard_Output_Handle, 0, &Console_Font_Information);

				CONSOLE_CURSOR_INFO Console_Cursor_Information = { sizeof(Console_Cursor_Information) };

				SetConsoleTextAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED);

				SetConsoleCursorInfo(Standard_Output_Handle, &Console_Cursor_Information);

				CONSOLE_SCREEN_BUFFER_INFO Console_Screen_Buffer_Information;

				GetConsoleScreenBufferInfo(Standard_Output_Handle, &Console_Screen_Buffer_Information);

				COORD Top_Left = { };

				DWORD Characters_Written;

				FillConsoleOutputAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED, Console_Screen_Buffer_Information.dwSize.X * Console_Screen_Buffer_Information.dwSize.Y, Top_Left, &Characters_Written);

				Engine_Module = GetModuleHandleW(L"engine.dll");

				_putws(L"[ + ] Delimit Interface");
				{
					unsigned __int8 Cheat_Flag_Bytes[5] = { 254, 64, 88, 144, 235 };

					Byte_Manager::Copy_Bytes(0, (void*)((unsigned __int64)Engine_Module + 1295094), sizeof(Cheat_Flag_Bytes), Cheat_Flag_Bytes);

					*(__int8*)((unsigned __int64)Engine_Module + 7531912) = 1;

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Engine_Module + 1535338), 1, 235);
				}

				_putws(L"[ + ] Extend Interface");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Engine_Module + 2635621), 2, 144);

					Implement_Extended_Interface();
				}

				_putws(L"[ + ] Events");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 572015), 1, 0);

					Post_Network_Data_Received_Manager.Redirect_Function(1, (void*)((unsigned __int64)Client_Module + 1599968), (void*)Redirected_Post_Network_Data_Received);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Engine_Module + 591732), 1, 235);

					void* Event_Listener = (void*)__builtin_malloc(sizeof(void*));

					void* Event_Listener_Table = __builtin_malloc(sizeof(void*) * 2);

					*(void**)((unsigned __int64)Event_Listener_Table + 8) = (void*)Event_Processor;

					*(void**)Event_Listener = Event_Listener_Table;

					using Add_Listener_Type = __int8(*)(void* Event_Manager, void* Listener, char* Event, void* Unknown_Parameter);

					Add_Listener_Type((unsigned __int64)Engine_Module + 1649792)((void*)((unsigned __int64)Engine_Module + 4692032), Event_Listener, (char*)"player_hurt", nullptr);

					Add_Listener_Type((unsigned __int64)Engine_Module + 1649792)((void*)((unsigned __int64)Engine_Module + 4692032), Event_Listener, (char*)"player_death", nullptr);

					Add_Listener_Type((unsigned __int64)Engine_Module + 1649792)((void*)((unsigned __int64)Engine_Module + 4692032), Event_Listener, (char*)"bullet_impact", nullptr);

					Write_Events_Manager.Redirect_Function(3, (void*)((unsigned __int64)Engine_Module + 1659120), (void*)Redirected_Write_Events);
				}

				_putws(L"[ + ] Interpolation");
				{
					Interpolate_Manager.Redirect_Function(1, (void*)((unsigned __int64)Client_Module + 488912), (void*)Redirected_Interpolate);
				}

				_putws(L"[ + ] Animations");
				{
					Update_Animation_Manager.Redirect_Function(1, (void*)((unsigned __int64)Client_Module + 2023744), (void*)Redirected_Update_Animation);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 2023793), 1, 235);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 554424), 2, 144);

					Compute_Torso_Rotation_Manager.Redirect_Function(0, (void*)((unsigned __int64)Client_Module + 292704), (void*)Redirected_Compute_Torso_Rotation);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 490384), 1, 195);
				}

				_putws(L"[ + ] Prediction");
				{
					auto Add_Prediction_Fields = [](Prediction_Descriptor_Structure* Descriptor, Prediction_Field_Structure* Fields, __int32 Size) -> void
					{
						Prediction_Descriptor_Structure* Original_Descriptor = (Prediction_Descriptor_Structure*)__builtin_malloc(sizeof(Prediction_Descriptor_Structure));

						Byte_Manager::Copy_Bytes(1, Original_Descriptor, sizeof(Prediction_Descriptor_Structure), Descriptor);

						Descriptor->Fields = Fields;

						Descriptor->Size = Size;

						Descriptor->Parent = Original_Descriptor;
					};

					static Prediction_Field_Structure Player_Fields[2] =
					{
						{ 1, (char*)"m_flVelocityModifier", { 6716 }, 1, 256, { }, nullptr, sizeof(float), { }, 0.005f },

						{ 3, (char*)"m_vecPreviouslyPredictedOrigin", { 6204 }, 1, 0, { }, nullptr, sizeof(float) }
					};

					Add_Prediction_Fields((Prediction_Descriptor_Structure*)((unsigned __int64)Client_Module + 6021096), Player_Fields, sizeof(Player_Fields) / sizeof(Prediction_Field_Structure));

					static Prediction_Field_Structure Weapon_Fields = { 1, (char*)"m_flDecreaseShotsFired", { 3252 }, 1, 0, { }, nullptr, sizeof(float) };

					Add_Prediction_Fields((Prediction_Descriptor_Structure*)((unsigned __int64)Client_Module + 6032264), &Weapon_Fields, sizeof(Weapon_Fields) / sizeof(Prediction_Field_Structure));

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 1606159), 1, 235);

					Finish_Move_Manager.Redirect_Function(4, (void*)((unsigned __int64)Client_Module + 1598256), (void*)Redirected_Finish_Move);

					Item_Post_Frame_Manager.Redirect_Function(2, (void*)((unsigned __int64)Client_Module + 348832), (void*)Redirected_Item_Post_Frame);
				}

				_putws(L"[ + ] Network");
				{
					Read_Packets_Manager.Redirect_Function(0, (void*)((unsigned __int64)Engine_Module + 577904), (void*)Redirected_Read_Packets);

					Move_Manager.Redirect_Function(0, (void*)((unsigned __int64)Engine_Module + 575936), (void*)Redirected_Move);

					unsigned __int8 Send_Move_Bytes[5] = { 233, 190 };

					Byte_Manager::Copy_Bytes(0, (void*)((unsigned __int64)Engine_Module + 576459), sizeof(Send_Move_Bytes), Send_Move_Bytes);

					Send_Move_Manager.Redirect_Function(2, (void*)((unsigned __int64)Engine_Module + 2681920), (void*)Redirected_Send_Move);

					Send_Datagram_Manager.Redirect_Function(2, (void*)((unsigned __int64)Engine_Module + 1907712), (void*)Redirected_Send_Datagram);

					Packet_Start_Manager.Redirect_Function(0, (void*)((unsigned __int64)Engine_Module + 2068368), (void*)Redirected_Packet_Start);
				}

				_putws(L"[ + ] Input");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 1388634), 4, 144);

					Copy_Command_Manager.Redirect_Function(0, (void*)((unsigned __int64)Client_Module + 1213008), (void*)Redirected_Copy_Command);
				}

				_putws(L"[ + ] View Effects");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 345661), 52, 144);
				}

				_putws(L"[ + ] Crosshair");
				{
					Draw_Crosshair_Manager.Redirect_Function((void*)((unsigned __int64)Client_Module + 2314992), (void*)Redirected_Draw_Crosshair);
				}

				_putws(L"[ + ] Materials");
				{
					Precache_Manager.Redirect_Function(0, (void*)((unsigned __int64)GetModuleHandleW(L"materialsystem.dll") + 32592), (void*)Redirected_Precache);

					Calculate_Override_Model_Manager.Redirect_Function((void*)((unsigned __int64)Client_Module + 531760), (void*)Redirected_Calculate_Override_Model);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 1813696), 1, 0);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 1938069), 1, 235);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 2500320), 1, 195);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int64)Client_Module + 2020992), 1, 195);
				}
			}
		}
	}

	return 1;
}