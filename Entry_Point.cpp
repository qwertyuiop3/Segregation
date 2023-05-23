#include <Windows.h>

#include <cstdio>

#define Bits_32

#include "Byte_Manager/Byte_Manager.hpp"

#include "Redirection_Manager/Redirection_Manager.hpp"

void* Engine_Module_Location;

#include "Extended_Interface.hpp"

#include "Post_Entity_Packet_Received.hpp"

#pragma comment(lib, "WinMM.Lib")

#include "Sounds.hpp"

#include "Event_Listener.hpp"

#include "Write_Events.hpp"

#include "Shutdown.hpp"

#include "Interpolate.hpp"

#include "Update_Animation.hpp"

#include "Compute_Torso_Rotation.hpp"

#include "Compute_First_Command_To_Execute.hpp"

#include "Store_Prediction_Results.hpp"

#include "Setup_Move.hpp"

#include "Fall_Damage.hpp"

#include <algorithm>

#include "Finish_Move.hpp"

#include "Item_Post_Frame.hpp"

#include "Weapon_Spread.hpp"

#include <vector>

#include "Copy_User_Command.hpp"

#include "Send_Move.hpp"

#include "Draw_Crosshair.hpp"

#include "Precache.hpp"

__int32 __stdcall DllMain(void* This_Module_Location, unsigned __int32 Call_Reason, void* Reserved)
{
	if (Call_Reason == DLL_PROCESS_DETACH)
	{
		__fastfail(EXIT_SUCCESS);
	}
	else
	{
		if (Call_Reason == DLL_PROCESS_ATTACH)
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

			Engine_Module_Location = GetModuleHandleW(L"engine.dll");

			_putws(L"[ + ] Delimit Interface");
			{
				unsigned __int8 Cheat_Flag_Bytes[5] =
				{
					254,

					64,

					48,
		
					144,

					235
				};

				Byte_Manager::Copy_Bytes(1, (void*)((unsigned __int32)Engine_Module_Location + 1359156), sizeof(Cheat_Flag_Bytes), Cheat_Flag_Bytes);

				*(__int8*)((unsigned __int32)Engine_Module_Location + 6384240) = 1;

				Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Engine_Module_Location + 1565004), 1, 235);
			}

			_putws(L"[ + ] Extend Interface");
			{
				Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Engine_Module_Location + 2391305), 2, 144);

				Implement_Extended_Interface();
			}

			/*_putws(L"[ + ] Events");
			{
				Redirection_Manager::Redirect_Function(Original_Post_Entity_Packet_Received_Caller_Location, 0, (void*)605203088, 1, (void*)Redirected_Post_Entity_Packet_Received);

				Byte_Manager::Set_Bytes(1, (void*)537149578, 1, 235);

				void* Event_Listener = (void*)malloc(sizeof(void*));

				void* Event_Listener_Table = malloc(sizeof(void*) * 2);

				*(void**)((unsigned __int32)Event_Listener_Table + 4) = (void*)Event_Processor;

				*(void**)Event_Listener = Event_Listener_Table;

				using Add_Listener_Type = __int8(__thiscall*)(void* Event_Manager, void* Listener, char* Event, void* Unknown_Parameter);

				Add_Listener_Type(537586416)((void*)540812808, Event_Listener, (char*)"player_hurt", nullptr);

				Add_Listener_Type(537586416)((void*)540812808, Event_Listener, (char*)"player_death", nullptr);

				Add_Listener_Type(537586416)((void*)540812808, Event_Listener, (char*)"bullet_impact", nullptr);

				Redirection_Manager::Redirect_Function(Original_Write_Events_Caller_Location, 2, (void*)537582208, 1, (void*)Redirected_Write_Events);

				Redirection_Manager::Redirect_Function(Original_Shutdown_Caller_Location, 0, (void*)537926128, 1, (void*)Redirected_Shutdown);
			}*/

			_putws(L"[ + ] Interpolation");
			{
				Redirection_Manager::Redirect_Function(Original_Interpolate_Caller_Location, 0, (void*)((unsigned __int32)Client_Module_Location + 547872), 1, (void*)Redirected_Interpolate);
			}

			/*_putws(L"[ + ] Animations");
			{
				Redirection_Manager::Redirect_Function(Original_Update_Animation_Caller_Location, 4, (void*)605800256, 1, (void*)Redirected_Update_Animation);

				Byte_Manager::Set_Bytes(1, (void*)605800287, 1, 235);

				Byte_Manager::Set_Bytes(1, (void*)604287917, 2, 144);

				Redirection_Manager::Redirect_Function(Original_Compute_Torso_Rotation_Caller_Location, 1, (void*)604022496, 1, (void*)Redirected_Compute_Torso_Rotation);

				unsigned __int8 Maintain_Sequence_Transitions_Bytes[3] =
				{
					194,

					24,

					0
				};

				Byte_Manager::Copy_Bytes(1, (void*)604206416, sizeof(Maintain_Sequence_Transitions_Bytes), Maintain_Sequence_Transitions_Bytes);
			}*/

			/*_putws(L"[ + ] Prediction");
			{
				Byte_Manager::Set_Bytes(1, (void*)537158868, 5, 144);

				Byte_Manager::Set_Bytes(1, (void*)605209595, 1, 235);

				Redirection_Manager::Redirect_Function(Original_Compute_First_Command_To_Execute_Caller_Location, 2, (void*)605206464, 1, (void*)Redirected_Compute_First_Command_To_Execute);

				Redirection_Manager::Redirect_Function(Original_Store_Prediction_Results_Caller_Location, 0, (void*)605209056, 1, (void*)Redirected_Store_Prediction_Results);

				Redirection_Manager::Redirect_Function(Original_Setup_Move_Caller_Location, 0, (void*)605206752, 1, (void*)Redirected_Setup_Move);

				Redirection_Manager::Redirect_Function(1, (void*)605024544, (void*)Redirected_Fall_Damage);

				Redirection_Manager::Redirect_Function(Original_Finish_Move_Caller_Location, 1, (void*)605207376, 1, (void*)Redirected_Finish_Move);

				Redirection_Manager::Redirect_Function(Original_Item_Post_Frame_Caller_Location, 0, (void*)604081184, 1, (void*)Redirected_Item_Post_Frame);

				Byte_Manager::Set_Bytes(1, (void*)605954536, 9, 144);

				Redirection_Manager::Redirect_Function(Original_Weapon_Spread_Caller_Location, 1, (void*)605949248, 1, (void*)Redirected_Weapon_Spread);
			}*/

			/*_putws(L"[ + ] Input");
			{
				Byte_Manager::Set_Bytes(1, (void*)604993824, 3, 144);

				Redirection_Manager::Redirect_Function(Original_Copy_User_Command_Caller_Location, 0, (void*)604850464, 1, (void*)Redirected_Copy_User_Command);
			}*/

			/*_putws(L"[ + ] Network");
			{
				Redirection_Manager::Redirect_Function(1, (void*)537142224, (void*)Redirected_Send_Move);
			}*/

			_putws(L"[ + ] View Effects");
			{
				Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module_Location + 430022), 52, 144);
			}

			_putws(L"[ + ] Crosshair");
			{
				Redirection_Manager::Redirect_Function(1, (void*)((unsigned __int32)Client_Module_Location + 2156016), (void*)Redirected_Draw_Crosshair);
			}

			_putws(L"[ + ] Materials");
			{
				Redirection_Manager::Redirect_Function(Original_Precache_Caller_Location, 5, (void*)((unsigned __int32)GetModuleHandleW(L"MaterialSystem.dll") + 239552), 1, (void*)Redirected_Precache);

				Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module_Location + 1743076), 1, 0);

				Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module_Location + 1842904), 1, 235);

				unsigned __int8 Smoke_Bytes[3] =
				{
					194,

					8,

					0
				};

				Byte_Manager::Copy_Bytes(1, (void*)((unsigned __int32)Client_Module_Location + 2311408), sizeof(Smoke_Bytes), Smoke_Bytes);

				Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module_Location + 1913184), 1, 195);
			}
		}
	}

	return 1;
}