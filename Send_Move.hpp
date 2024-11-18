Redirection_Manager::Manager_Structure Send_Move_Manager;

__int32 Get_Choked_Commands()
{
	static void* Choked_Commands = Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(3523, (unsigned __int8*)Engine_Module, 12979630919169177513ull), 2);

	return *(__int32*)Choked_Commands;
}

__int32 Get_Last_Command_Number()
{
	static void* Last_Command_Number = Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(14403, (unsigned __int8*)Engine_Module, 5131075775616746518), 2);

	return *(__int32*)Last_Command_Number;
}

void* Get_Network_Channel()
{
	using Get_Network_Channel_Type = void*(**)(void* Engine);

	void* Engine = Get_Engine();

	return (*Get_Network_Channel_Type(*(unsigned __int64*)Engine + 576))(Engine);
}

void Redirected_Send_Move(void* Unknown_Parameter)
{
	(decltype(&Redirected_Send_Move)(Send_Move_Manager.Caller))(Unknown_Parameter);

	static void* Send_Move_Return = (void*)((unsigned __int64)Byte_Manager::Find_Bytes(239, (unsigned __int8*)Engine_Module, 16801912347244827565ull) + 19);

	if (__builtin_return_address(0) == Send_Move_Return)
	{
		struct Message_Structure
		{
			__int8 Message[136];

			void Construct(__int8* Data, unsigned __int32 Size)
			{
				Byte_Manager::Set_Bytes(1, Message, sizeof(Message), 0);

				static void* Table = Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(69596422721415, (unsigned __int8*)Engine_Module, 3827992606784973200), 3);

				*(void**)Message = Table;

				*(void**)((unsigned __int64)Message + 104) = Data;

				*(__int32*)((unsigned __int64)Message + 112) = Size;

				*(__int32*)((unsigned __int64)Message + 116) = Size * 8;
			}
		};

		Message_Structure Message;

		__int8 Data[4000];

		Message.Construct(Data, sizeof(Data));

		__int32 Choked_Commands = Get_Choked_Commands();

		__int32 Commands_Queue = min(Choked_Commands + 1, 15);

		*(__int32*)((unsigned __int64)&Message + 36) = Commands_Queue;

		__int32 Extra_Commands_Queue = Choked_Commands + 1 - Commands_Queue;

		__int32 Backup_Commands = min(Extra_Commands_Queue, 7);

		*(__int32*)((unsigned __int64)&Message + 32) = Backup_Commands;

		__int32 From_Command_Number = -1;

		__int32 Next_Command_Number = Get_Last_Command_Number() + Choked_Commands + 2;

		__int32 To_Command_Number = Next_Command_Number - Commands_Queue - Backup_Commands;

		Write_Command_Label:
		{
			using Write_Command_Type = __int8(**)(void* Client, void* Data, __int32 From, __int32 To, void* Unknown_Parameter);

			static void* Client = *(void**)Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(3700615, (unsigned __int8*)Engine_Module, 9962792283015153587ull), 3);

			(*Write_Command_Type(*(unsigned __int64*)Client + 184))(Client, (void*)((unsigned __int64)&Message + 104), From_Command_Number, To_Command_Number, nullptr);

			From_Command_Number = To_Command_Number;

			To_Command_Number += 1;

			if (To_Command_Number != Next_Command_Number)
			{
				goto Write_Command_Label;
			}
		}

		void* Network_Channel = Get_Network_Channel();

		*(__int32*)((unsigned __int64)Network_Channel + 12) += Extra_Commands_Queue;

		*(__int32*)((unsigned __int64)Network_Channel + 32) = 0;

		using Send_Message_Type = __int8(**)(void* Network_Channel, void* Message, void* Unknown_Parameter_1, void* Unknown_Parameter_2);

		(*Send_Message_Type(*(unsigned __int64*)Network_Channel + 320))(Network_Channel, &Message, nullptr, nullptr);
	}
}