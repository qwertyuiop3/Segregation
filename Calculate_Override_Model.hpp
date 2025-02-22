Redirection_Manager::Manager_Structure Calculate_Override_Model_Manager;

__int32 Redirected_Calculate_Override_Model(void* Weapon)
{
	if (__builtin_return_address(0) == (void*)((unsigned __int64)Client_Module + 533554))
	{
		return *(__int32*)((unsigned __int64)Weapon + 3068);
	}

	return -1;
}