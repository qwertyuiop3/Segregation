struct Prediction_Field_Structure
{
	__int32 Type;

	char* Name;

	__int32 Offset[2];

	unsigned __int16 Size;

	__int16 Flags;

	__int8 Additional_Bytes_1[16];

	__int32 Bytes;

	__int8 Additional_Bytes_2[8];

	float Tolerance;
};

struct Prediction_Copy_Structure
{
	__int8 Additional_Bytes_1[8];

	void* Source;

	__int8 Additional_Bytes_2[11];

	Prediction_Field_Structure* Field;

	__int8 Additional_Bytes_3[32];

	void Construct(void* Destination, void* Source, void* Handler)
	{
		using Construct_Type = void(__thiscall*)(void* Prediction_Copy, __int32 Unknown_Parameter_1, void* Destination, void* Unknown_Parameter_2, void* Source, __int8 Unknown_Parameter_3, __int8 Unknown_Parameter_4, void* Unknown_Parameter_5, void* Unknown_Parameter_6, __int8 Unknown_Parameter_7, void* Handler);

		Construct_Type((unsigned __int32)Client_Module + 1555696)(this, 2, Destination, nullptr, Source, 1, 1, nullptr, nullptr, 1, Handler);
	}
};

Prediction_Copy_Structure Predicton_Copy;

void Predicton_Copy_Compare(char* Class, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4, void* Unknown_Parameter_5, __int8 Within_Tolerance, void* Unknown_Parameter_6)
{
	if (Within_Tolerance == 1)
	{
		Prediction_Field_Structure* Field = Predicton_Copy.Field;

		Byte_Manager::Copy_Bytes(0, (void*)(*(unsigned __int32*)((unsigned __int32)Client_Module + 5015784) + 3548 * (Class[1] == 'P') + Field->Offset[0]), Field->Bytes, (void*)((unsigned __int32)Predicton_Copy.Source + Field->Offset[1]));
	}
}

struct Prediction_Descriptor_Structure
{
	Prediction_Field_Structure* Fields;

	__int32 Size;

	char* Name;

	Prediction_Descriptor_Structure* Parent;

	__int8 Additional_Bytes[6];
};

void* Original_Post_Entity_Packet_Received_Caller;

void Redirected_Post_Entity_Packet_Received()
{
	__int32 Stored_Result_Number = 0;

	void* Local_Player = *(void**)((unsigned __int32)Client_Module + 5015784);

	__int32 Tick_Number = *(__int32*)((unsigned __int32)Local_Player + 4332);

	Traverse_Stored_Results_Label:
	{
		void* Stored_Result = *(void**)((unsigned __int32)Local_Player + 856 + Stored_Result_Number * 4);

		if (Stored_Result == nullptr)
		{
			Continue_Traversing_Stored_Results_Label:
			{
				if (Stored_Result_Number != 90)
				{
					Stored_Result_Number += 1;

					goto Traverse_Stored_Results_Label;
				}
			}
		}
		else
		{
			if (*(__int32*)((unsigned __int32)Stored_Result + 832) == Tick_Number)
			{
				Tick_Number = -(856 + Stored_Result_Number * 4);
			}
			else
			{
				goto Continue_Traversing_Stored_Results_Label;
			}
		}
	}

	if (__builtin_signbitf(Tick_Number) == 1)
	{
		Predicton_Copy.Construct(Local_Player, *(void**)((unsigned __int32)Local_Player + -Tick_Number), (void*)Predicton_Copy_Compare);

		using Transfer_Data_Type = __int32(__thiscall*)(Prediction_Copy_Structure* Prediction_Copy, void* Unknown_Parameter, __int32 Entity_Number, Prediction_Descriptor_Structure* Descriptor);

		Transfer_Data_Type((unsigned __int32)Client_Module + 1561808)(&Predicton_Copy, nullptr, -1, (Prediction_Descriptor_Structure*)((unsigned __int32)Client_Module + 4819316));
	}

	(decltype(&Redirected_Post_Entity_Packet_Received)(Original_Post_Entity_Packet_Received_Caller))();
}