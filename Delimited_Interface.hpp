struct Interface_Structure
{
	__int8 Additional_Bytes_1[72];

	char* String;

	__int8 Additional_Bytes_2[64];
	
	__int32 Get_Integer()
	{
		using Get_Interface_Integer_Type = __int32(**)(Interface_Structure* Interface);
		
		return (*Get_Interface_Integer_Type(*(unsigned __int64*)this + 104))(this);
	}
	
	float Get_Floating_Point()
	{
		using Get_Interface_Floating_Point_Type = float(**)(Interface_Structure* Interface);
		
		return (*Get_Interface_Floating_Point_Type(*(unsigned __int64*)this + 96))(this);
	}

	void Set_Integer(__int32 Integer)
	{
		using Set_Integer_Type = void(**)(Interface_Structure* Interface, __int32 Value);

		(*Set_Integer_Type(*(unsigned __int64*)this + 128))(this, Integer);
	}
};

Interface_Structure* Find_Interface(char* Name)
{
	using Find_Interface_Type = Interface_Structure*(**)(void* Interface, char* Name);

	void* Interface = *(void**)((unsigned __int64)Engine_Module + 12887056);

	return (*Find_Interface_Type(*(unsigned __int64*)Interface + 136))(Interface, Name);
}

void Force_Interface_Value(Interface_Structure* Interface)
{
	Interface = (Interface_Structure*)((unsigned __int64)Interface - 48);

	Interface->Set_Integer(1);
}