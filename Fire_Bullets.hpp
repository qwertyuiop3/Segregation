struct Bullet_Structure
{
	__int8 Additional_Bytes_1[28];

	float Spread[2];

	__int8 Additional_Bytes_2[4];

	float Range;
};

__int8 Bullets_Fired;

float Weapon_Recoil[2];

float Weapon_Spread[2];

float Weapon_Range;

Redirection_Manager::Manager_Structure Fire_Bullets_Manager;

void Redirected_Fire_Bullets(void* Player, Bullet_Structure* Bullet)
{
	Bullets_Fired = 1;

	static void* Fire_Bullets_Return = Byte_Manager::Find_Bytes(31584391, (unsigned __int8*)Client_Module, 4143659588161189767);

	if (__builtin_return_address(0) == Fire_Bullets_Return)
	{
		Byte_Manager::Set_Bytes(1, Weapon_Recoil, sizeof(Weapon_Recoil), 0);
	}
	else
	{
		Byte_Manager::Copy_Bytes(1, Weapon_Recoil, sizeof(Weapon_Recoil), (float*)((unsigned __int64)Player + 10784));
	}

	Byte_Manager::Copy_Bytes(1, Weapon_Spread, sizeof(Weapon_Spread), Bullet->Spread);

	Weapon_Range = Bullet->Range;

	(decltype(&Redirected_Fire_Bullets)(Fire_Bullets_Manager.Caller))(Player, Bullet);
}