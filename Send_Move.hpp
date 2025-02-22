Redirection_Manager::Manager_Structure Send_Move_Manager;

void Redirected_Send_Move(void* Unknown_Parameter)
{
	(decltype(&Redirected_Send_Move)(Send_Move_Manager.Caller))(Unknown_Parameter);

	if (__builtin_return_address(0) == (void*)((unsigned __int64)Engine_Module + 576459))
	{
		struct Message_Structure
		{
			__int8 Message[120];

			void Construct(__int8* Data, unsigned __int32 Size)
			{
				Byte_Manager::Set_Bytes(1, Message, sizeof(Message), 0);

				*(void**)Message = (void*)((unsigned __int64)Engine_Module + 3549168);

				*(void**)((unsigned __int64)Message + 88) = Data;

				*(__int32*)((unsigned __int64)Message + 96) = Size;

				*(__int32*)((unsigned __int64)Message + 100) = Size * 8;
			}
		};

		Message_Structure Message;

		__int8 Data[4000];

		Message.Construct(Data, sizeof(Data));

		__int32 Choked_Commands = *(__int32*)((unsigned __int64)Engine_Module + 5497992);

		__int32 Commands_Queue = min(Choked_Commands + 1, 15);

		*(__int32*)((unsigned __int64)&Message + 44) = Commands_Queue;

		__int32 Extra_Commands_Queue = Choked_Commands + 1 - Commands_Queue;

		__int32 Backup_Commands = min(Extra_Commands_Queue, 7);

		*(__int32*)((unsigned __int64)&Message + 40) = Backup_Commands;

		__int32 From_Command_Number = -1;

		__int32 Next_Command_Number = *(__int32*)((unsigned __int64)Engine_Module + 5497988) + Choked_Commands + 2;

		__int32 To_Command_Number = Next_Command_Number - Commands_Queue - Backup_Commands;

		Write_Command_Label:
		{
			using Write_Command_Type = __int8(*)(void* Client, void* Data, __int32 From, __int32 To, void* Unknown_Parameter);

			Write_Command_Type((unsigned __int64)Client_Module + 883920)(*(void**)((unsigned __int64)Engine_Module + 5380264), (void*)((unsigned __int64)&Message + 88), From_Command_Number, To_Command_Number, nullptr);

			From_Command_Number = To_Command_Number;

			To_Command_Number += 1;

			if (To_Command_Number != Next_Command_Number)
			{
				goto Write_Command_Label;
			}
		}

		void* Network_Channel = *(void**)((unsigned __int64)Engine_Module + 5462064);

		*(__int32*)((unsigned __int64)Network_Channel + 12) += Extra_Commands_Queue;

		*(__int32*)((unsigned __int64)Network_Channel + 32) = 0;

		using Send_Message_Type = void(*)(void* Network_Channel, void* Message, void* Unknown_Parameter_1, void* Unknown_Parameter_2);

		Send_Message_Type((unsigned __int64)Engine_Module + 1909952)(Network_Channel, &Message, nullptr, nullptr);
	}
}