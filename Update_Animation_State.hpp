float Update_Animation_Angles[2];

Redirection_Manager::Manager_Structure Update_Animation_State_Manager;

void Redirected_Update_Animation_State(void* Animation_State, float Yaw, float Pitch)
{
	if (*(void**)((unsigned __int64)Animation_State + 48) == Get_Local_Player())
	{
		Pitch = Update_Animation_Angles[0];

		Yaw = Update_Animation_Angles[1];
	}

	(decltype(&Redirected_Update_Animation_State)(Update_Animation_State_Manager.Caller))(Animation_State, Yaw, Pitch);
}