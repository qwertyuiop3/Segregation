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
};

void Force_Interface_Value(Interface_Structure* Interface)
{
	Interface = (Interface_Structure*)((unsigned __int64)Interface - 48);

	using Set_Interface_Integer_Type = void(**)(Interface_Structure* Interface, __int32 Integer);

	(*Set_Interface_Integer_Type(*(unsigned __int64*)Interface + 128))(Interface, 1);
}