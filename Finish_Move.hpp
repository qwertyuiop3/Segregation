Redirection_Manager::Manager_Structure Finish_Move_Manager;

void Redirected_Finish_Move(void* Unknown_Parameter_1, void* Player, void* Unknown_Parameter_2, void* Move_Data)
{
	float X = *(float*)((unsigned __int64)Move_Data + 80);

	if (X > 180.f)
	{
		X -= 360.f;
	}

	*(float*)((unsigned __int64)Move_Data + 80) = std::clamp(X, -90.f, 90.f);

	(decltype(&Redirected_Finish_Move)(Finish_Move_Manager.Caller))(Unknown_Parameter_1, Player, Unknown_Parameter_2, Move_Data);
}