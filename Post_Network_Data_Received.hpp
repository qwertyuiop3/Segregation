struct Prediction_Copy_Structure
{
	__int32 Operation_Type;

	__int32 Copy_Type;

	void* Destination;

	void* Source;

	__int32 Packed[2];

	__int8 Additional_Bytes_1[8];

	void* Handler;

	__int8 Additional_Bytes_2[28];

	void Construct(void* Destination, void* Source, void* Handler)
	{
		Operation_Type = 3;

		Copy_Type = 2;

		this->Destination = Destination;

		this->Source = Source;

		Packed[0] = 1;

		Packed[1] = 0;

		this->Handler = Handler;
	}
};

Prediction_Copy_Structure Predicton_Copy;

struct Prediction_Field_Structure
{
	__int32 Type;

	char* Name;

	__int32 Offset;

	unsigned __int16 Size;

	__int16 Flags;

	__int8 Additional_Bytes_1[10];

	struct Prediction_Descriptor_Structure* Descriptor;

	__int32 Bytes;

	__int8 Additional_Bytes_2[8];

	float Tolerance;

	__int32 Flat_Offset[2];

	__int8 Additionals_Bytes_3[2];
};

void Predicton_Copy_Compare(void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4, void* Unknown_Parameter_5, void* Unknown_Parameter_6, __int8 Within_Tolerance, void* Unknown_Parameter_7)
{
	Prediction_Field_Structure* Field = *(Prediction_Field_Structure**)((unsigned __int32)__builtin_frame_address(0) + 48);

	if (Within_Tolerance * (Field->Tolerance != 0.f) == 1)
	{
		Byte_Manager::Copy_Bytes(1, (void*)((unsigned __int32)Predicton_Copy.Destination + Field->Flat_Offset[0]), Field->Bytes, (void*)((unsigned __int32)Predicton_Copy.Source + Field->Flat_Offset[1]));
	}
}

struct Prediction_Descriptor_Structure
{
	Prediction_Field_Structure* Fields;

	__int32 Size;

	__int8 Additional_Bytes_1[4];

	Prediction_Descriptor_Structure* Parent;

	__int8 Additional_Bytes_2[8];
};

void* Original_Post_Network_Data_Received_Caller;

void __thiscall Redirected_Post_Network_Data_Received(void* Unknown_Parameter, __int32 Commands_Acknowledged)
{
	void* Local_Player = *(void**)((unsigned __int32)Client_Module + 82926756);

	Commands_Acknowledged = max(0, Commands_Acknowledged);

	void* Result = *(void**)((unsigned __int32)Local_Player + 1140 + (150 - ((Commands_Acknowledged - 1) % 150 + 1) * 150 % -~150) * 4);

	if (Result == *(void**)((unsigned __int32)Local_Player + 1740))
	{
		Result = *(void**)((unsigned __int32)Local_Player + 2344);
	}

	if (Result != nullptr)
	{
		Predicton_Copy.Construct(Local_Player, Result, (void*)Predicton_Copy_Compare);

		using Transfer_Data_Type = __int32(__thiscall*)(Prediction_Copy_Structure* Prediction_Copy, void* Unknown_Parameter, __int32 Entity_Number, Prediction_Descriptor_Structure* Descriptor);

		Transfer_Data_Type((unsigned __int32)Client_Module + 3054144)(&Predicton_Copy, nullptr, -1, (Prediction_Descriptor_Structure*)((unsigned __int32)Client_Module + 11469140));
	}

	(decltype(&Redirected_Post_Network_Data_Received)(Original_Post_Network_Data_Received_Caller))(Unknown_Parameter, Commands_Acknowledged);
}