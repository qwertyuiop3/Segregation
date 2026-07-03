void* Get_Local_Player()
{
	static void* Local_Player = Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(2081671, (unsigned __int8*)Client_Module, 6192131677276294978), 3);

	return *(void**)Local_Player;
}

struct Prediction_Field_Structure
{
	__int32 Type;

	__int8 Additional_Bytes_1[40];

	struct Prediction_Descriptor_Structure* Descriptor;

	__int32 Bytes;

	__int8 Additional_Bytes_2[20];

	__int32 Flat_Offset[2];

	__int8 Additional_Bytes_3[2];
};

struct Prediction_Descriptor_Structure
{
	Prediction_Field_Structure* Fields;

	__int32 Size;

	__int8 Additional_Bytes_1[12];

	Prediction_Descriptor_Structure* Parent;
};

struct Prediction_Copy_Structure
{
	__int8 Additional_Bytes_1[16];

	void* Source;

	__int8 Additional_Bytes_2[16];

	Prediction_Field_Structure* Field;

	__int8 Additional_Bytes_3[8];

	Prediction_Descriptor_Structure* Descriptor;

	__int8 Additional_Bytes_4[40];

	void Construct(void* Destination, void* Source, void* Handler)
	{
		using Construct_Type = void(*)(void* Prediction_Copy, __int32 Type, void* Destination, __int8 Destination_Packed, void* Source, __int8 Source_Packed, __int8 Count_Errors, void* Unknown_Parameter_1, void* Unknown_Parameter_2, __int8 Report_Errors, void* Handler);

		static void* Construct = Byte_Manager::Find_Bytes(7919, (unsigned __int8*)Client_Module, 2076044217017777087);

		Construct_Type((unsigned __int64)Construct)(this, 2, Destination, 0, Source, 1, 1, nullptr, nullptr, 1, Handler);
	}
};

Prediction_Copy_Structure Predicton_Copy;

__int32 Compute_Flat_Offset(__int32* Offset, Prediction_Descriptor_Structure* Descriptor, void* Search_Field, __int32 Base_Offset)
{
	if (*Offset == 0)
	{
		if (Descriptor->Parent != nullptr)
		{
			Compute_Flat_Offset(Offset, Descriptor->Parent, Search_Field, Base_Offset);
		}

		__int32 Field_Number = 0;

		Traverse_Fields_Label:
		{
			Prediction_Field_Structure* Field = &Descriptor->Fields[Field_Number];

			if (Field == Search_Field)
			{
				*Offset = Base_Offset + Field->Flat_Offset[0];
			}
			else
			{
				if (Field->Type == 10)
				{
					Compute_Flat_Offset(Offset, Field->Descriptor, Search_Field, Base_Offset + Field->Flat_Offset[0]);
				}

				if (Field_Number != Descriptor->Size)
				{
					Field_Number += 1;

					goto Traverse_Fields_Label;
				}
			}
		}
	}

	return *Offset;
}

void Predicton_Copy_Compare(void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4, void* Unknown_Parameter_5, void* Unknown_Parameter_6, __int8 Within_Tolerance, void* Unknown_Parameter_7)
{
	if (Within_Tolerance == 1)
	{
		Prediction_Field_Structure* Field = Predicton_Copy.Field;

		static std::unordered_map<void*, __int32> Flat_Offsets;

		Byte_Manager::Copy_Bytes(1, (void*)((unsigned __int64)Get_Local_Player() + Compute_Flat_Offset(&Flat_Offsets[Field], Predicton_Copy.Descriptor, Field, 0)), Field->Bytes, (void*)((unsigned __int64)Predicton_Copy.Source + Field->Flat_Offset[1]));
	}
}

Redirection_Manager::Manager_Structure Post_Network_Data_Received_Manager;

void Redirected_Post_Network_Data_Received(void* Unknown_Parameter, __int32 Commands_Acknowledged)
{
	void* Local_Player = Get_Local_Player();

	Commands_Acknowledged = max(0, Commands_Acknowledged);

	void* Prediction_Frame = *(void**)((unsigned __int64)Local_Player + 1112 + (90 - ((Commands_Acknowledged - 1) % 90 + 1) * 90 % -~90) * 8);

	if (Prediction_Frame != nullptr)
	{
		Predicton_Copy.Construct(Local_Player, Prediction_Frame, (void*)Predicton_Copy_Compare);

		using Transfer_Data_Type = __int32(*)(Prediction_Copy_Structure* Prediction_Copy, void* Unknown_Parameter, __int32 Entity_Number, Prediction_Descriptor_Structure* Descriptor);

		static void* Transfer_Data = Byte_Manager::Find_Bytes(3653103, (unsigned __int8*)Client_Module, 742330376693593246);

		static Prediction_Descriptor_Structure* Descriptor = (Prediction_Descriptor_Structure*)Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(502267783, (unsigned __int8*)Client_Module, 8622645398228305451), 3);

		Transfer_Data_Type((unsigned __int64)Transfer_Data)(&Predicton_Copy, nullptr, -1, Descriptor);
	}

	Post_Network_Data_Received_Manager.Special_Call(Unknown_Parameter, Commands_Acknowledged);
}