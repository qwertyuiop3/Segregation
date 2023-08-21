#include <Windows.h>

#include <cstdio>

#define Bits_32

#include "Byte_Manager/Byte_Manager.hpp"

#include "Redirection_Manager/Redirection_Manager.hpp"

#include "Extended_Interface.hpp"

#include "Post_Entity_Packet_Received.hpp"

#pragma comment(lib, "WinMM.Lib")

#include "Sounds.hpp"

#include "Event_Listener.hpp"

#include <vector>

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

#include "Copy_User_Command.hpp"

#include "Send_Move.hpp"

#include "Packet_Start.hpp"

#include "Draw_Crosshair.hpp"

#include "Precache.hpp"

__int8 __thiscall performpred(void* Prediction, __int8 Unknown_Parameter, void* Player, __int32 Acknowledged_Command_Number, __int32 Outgoing_Command_Number)
{
	*(__int8*)((unsigned __int32)Prediction + 8) = 1;

	using Compute_First_Command_To_Execute_Type = __int32(__thiscall*)(void* Prediction, __int8 Unknown_Parameter, __int32 Acknowledged_Command_Number, __int32 Outgoing_Command_Number);

	__int32 Current_Command_Number = Compute_First_Command_To_Execute_Type(605206464)(Prediction, 1, Acknowledged_Command_Number, Outgoing_Command_Number);

	__int32 Final_Command_Number = Outgoing_Command_Number + 1;

	static Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)607726732;

	using Get_User_Command_Type = User_Command_Structure*(__thiscall*)(void* Unknown_Parameter, __int32 Command_Number);

	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	static std::vector<User_Command_Structure*> cmds;
	cmds.clear();
	for (int i = Current_Command_Number + Acknowledged_Command_Number; i < Final_Command_Number; i++)
	{
		cmds.push_back(Get_User_Command_Type(604993792)(*(void**)607769608, i));
	}
	if (cmds.size())//temporary
	{
		__int32 first_tick = cmds.at(0)->Tick_Number;
		__int32 lastvalidd = first_tick;
		for (int i = 0; i < cmds.size(); i++)
		{
			for (int j = 0; j < 90; j++)
			{
				if (validticks[first_tick % 90][j] == cmds.at(i)->Tick_Number)
				{
					lastvalidd = cmds.at(i)->Tick_Number;
					goto skip_delete;
				}
			}
			if (abs(cmds.at(i)->Tick_Number - lastvalidd) > 24)
			{
				cmds.erase(cmds.begin() + i);
				--i;
			}
			else
			{
				lastvalidd = cmds.at(i)->Tick_Number;
			}
			skip_delete:{}
		}
	}
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	Predict_Label:
	{
		__int32 Current_Acknowledged_Command_Number = Current_Command_Number + Acknowledged_Command_Number;

		if (Current_Acknowledged_Command_Number != Final_Command_Number)
		{
			if (Current_Command_Number != 90)
			{
				User_Command_Structure* User_Command = Get_User_Command_Type(604993792)(*(void**)607769608, Current_Acknowledged_Command_Number);

				if (std::find(cmds.begin(), cmds.end(), User_Command) != cmds.end())
				{
					using Run_Simulation_Type = void(__thiscall*)(void* Prediction, __int32 Command_Number, float Current_Time, User_Command_Structure* User_Command, void* Player);

					float Current_Time = *(__int32*)((unsigned __int32)Player + 3592) * Global_Variables->Interval_Per_Tick;

					if (*(__int8*)((unsigned __int32)User_Command + 60) == 0)
					{
						*(__int8*)((unsigned __int32)Prediction + 9) = 1;
					}
					else
					{
						*(__int8*)((unsigned __int32)Prediction + 9) = 0;
					}

					Run_Simulation_Type(605206096)(Prediction, Current_Acknowledged_Command_Number, Current_Time, User_Command, Player);

					*(__int8*)((unsigned __int32)User_Command + 60) = 1;

					Global_Variables->Current_Time = Current_Time;

					Global_Variables->Frame_Time = Global_Variables->Interval_Per_Tick;

					using Store_Results_Type = void(__thiscall*)(void* Prediction, __int32 Number);

					Store_Results_Type(605209056)(Prediction, Current_Command_Number - 1);

					*(__int32*)((unsigned __int32)Prediction + 16) = Current_Command_Number;
				}
				else
				{
					using Store_Results_Type = void(__thiscall*)(void* Prediction, __int32 Number);

					Store_Results_Type(605209056)(Prediction, Current_Command_Number - 1);
				}

				Current_Command_Number += 1;

				goto Predict_Label;
			}
		}

		*(__int32*)((unsigned __int32)Player + 3596) = *(__int32*)((unsigned __int32)Player + 3592);
	}

	*(__int8*)((unsigned __int32)Prediction + 8) = 0;

	return 1;
}

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
			Redirection_Manager::Redirect_Function(1, (void*)0x2412C250, (void*)performpred);

			Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)LoadLibraryW(L"vaudio_speex.dll") + 9360), 1, 195);

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

			_putws(L"[ + ] Delimit Interface");
			{
				unsigned __int8 Cheat_Flag_Bytes[4] =
				{
					254,

					65,

					44,

					195
				};

				Byte_Manager::Copy_Bytes(1, (void*)538391351, sizeof(Cheat_Flag_Bytes), Cheat_Flag_Bytes);

				*(__int8*)542242676 = 1;

				Byte_Manager::Set_Bytes(1, (void*)537349277, 1, 235);
			}

			_putws(L"[ + ] Extend Interface");
			{
				Implement_Extended_Interface();
			}

			_putws(L"[ + ] Events");
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
			}

			_putws(L"[ + ] Interpolation");
			{
				Redirection_Manager::Redirect_Function(Original_Interpolate_Caller_Location, 0, (void*)604201536, 1, (void*)Redirected_Interpolate);
			}

			_putws(L"[ + ] Animations");
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
			}

			_putws(L"[ + ] Prediction");
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
			}

			_putws(L"[ + ] Input");
			{
				Byte_Manager::Set_Bytes(1, (void*)604993824, 3, 144);

				Redirection_Manager::Redirect_Function(Original_Copy_User_Command_Caller_Location, 0, (void*)604850464, 1, (void*)Redirected_Copy_User_Command);
			}

			_putws(L"[ + ] Network");
			{
				Redirection_Manager::Redirect_Function(1, (void*)537142224, (void*)Redirected_Send_Move);

				Redirection_Manager::Redirect_Function(Original_Packet_Start_Caller_Location, 2, (void*)538164112, 1, (void*)Redirected_Packet_Start);
			}

			_putws(L"[ + ] View Effects");
			{
				Byte_Manager::Set_Bytes(1, (void*)604082898, 34, 144);
			}

			_putws(L"[ + ] Crosshair");
			{
				Redirection_Manager::Redirect_Function(1, (void*)605951488, (void*)Redirected_Draw_Crosshair);
			}

			_putws(L"[ + ] Materials");
			{
				Redirection_Manager::Redirect_Function(Original_Precache_Caller_Location, 5, (void*)((unsigned __int32)GetModuleHandleW(L"MaterialSystem.dll") + 21984), 1, (void*)Redirected_Precache);

				Byte_Manager::Set_Bytes(1, (void*)605462216, 2, 144);

				Byte_Manager::Set_Bytes(1, (void*)605515289, 1, 235);

				unsigned __int8 Smoke_Bytes[3] =
				{
					194,

					8,

					0
				};

				Byte_Manager::Copy_Bytes(1, (void*)605610608, sizeof(Smoke_Bytes), Smoke_Bytes);

				Byte_Manager::Set_Bytes(1, (void*)605809168, 1, 195);
			}
		}
	}

	return 1;
}