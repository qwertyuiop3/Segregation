float Shot_Time;

void __stdcall Event_Processor(void* Event)
{
	void* Local_Player = *(void**)((unsigned __int32)Client_Module + 82926756);

	if (Local_Player != nullptr)
	{
		using Get_Name_Type = char*(__thiscall*)(void* Event);

		char* Name = Get_Name_Type((unsigned __int32)Engine_Module + 2043136)(Event);

		using Identifier_To_Number_Type = __int32(__thiscall*)(void* Engine, __int32 Identifier);

		using Get_Integer_Type = __int32(__thiscall*)(void* Event, char* Key, void* Unknown_Parameter);

		__int32 Local_Number = *(__int32*)((unsigned __int32)Local_Player + 100);

		if (Name[0] == 'p')
		{
			__int32 Victim_Number = Identifier_To_Number_Type((unsigned __int32)Engine_Module + 701152)((void*)((unsigned __int32)Engine_Module + 5749856), Get_Integer_Type((unsigned __int32)Engine_Module + 2042640)(Event, (char*)"userid", nullptr));

			__int32 Inflictor_Number = Identifier_To_Number_Type((unsigned __int32)Engine_Module + 701152)((void*)((unsigned __int32)Engine_Module + 5749856), Get_Integer_Type((unsigned __int32)Engine_Module + 2042640)(Event, (char*)"attacker", nullptr));

			if (Victim_Number != Inflictor_Number)
			{
				if (Inflictor_Number != 0)
				{
					if (Victim_Number == Local_Number)
					{
						if (Name[7] == 'd')
						{
							Player_Data_Structure* Player_Data = &Players_Data[Inflictor_Number];

							Player_Data->Memory_Tolerance = 0;

							if (Interface_Commentator.Get_Integer() == 1)
							{
								PlaySoundW((wchar_t*)Sounds_Laugh, nullptr, SND_ASYNC | SND_MEMORY);
							}
						}
					}
					else
					{
						if (Inflictor_Number == Local_Number)
						{
							if (Victim_Number == Recent_Player_Data_Number)
							{
								__int8 Revert = 1;

								Player_Data_Structure* Player_Data = &Players_Data[Victim_Number];

								if (Name[7] == 'h')
								{
									if (Interface_Aim_Intersection.Get_Integer() == 0)
									{
										Revert = Get_Integer_Type((unsigned __int32)Engine_Module + 2042640)(Event, (char*)"hitgroup", nullptr);
									}

									if (Revert == 1)
									{
										if (Player_Data->Memory_Tolerance == 0)
										{
											if (Player_Data->Tolerance == Interface_Bruteforce_Tolerance.Get_Integer())
											{
												Player_Data->Switch_X -= Player_Data->Shots_Fired == 0;

												Player_Data->Shots_Fired = ((Player_Data->Shots_Fired - 1) % Bruteforce_Angles_Count + Bruteforce_Angles_Count) % Bruteforce_Angles_Count;
											}
											else
											{
												Player_Data->Tolerance = Interface_Bruteforce_Tolerance.Get_Integer();
											}
										}
									}
								}
								else
								{
									if (Interface_Bruteforce_Memory_Tolerance.Get_Integer() != 0)
									{
										if (Interface_Aim_Intersection.Get_Integer() == 0)
										{
											Revert = Get_Integer_Type((unsigned __int32)Engine_Module + 2042640)(Event, (char*)"headshot", nullptr);
										}

										if (Revert == 1)
										{
											if (Player_Data->Memory_Tolerance == 0)
											{
												Player_Data->Tolerance = 0;

												Player_Data->Memorized_Y = Bruteforce_Angles[Player_Data->Shots_Fired];
											}

											Player_Data->Memory_Tolerance = Interface_Bruteforce_Memory_Tolerance.Get_Integer();
										}
									}
								}
							}

							if (Name[7] == 'd')
							{
								if (Interface_Commentator.Get_Integer() == 1)
								{
									PlaySoundW((wchar_t*)Sounds_Exclamation, nullptr, SND_ASYNC | SND_MEMORY);
								}
							}
						}
					}
				}
			}
		}
		else
		{
			Shot_Time *= Identifier_To_Number_Type((unsigned __int32)Engine_Module + 701152)((void*)((unsigned __int32)Engine_Module + 5749856), Get_Integer_Type((unsigned __int32)Engine_Module + 2042640)(Event, (char*)"userid", nullptr)) != Local_Number;
		}
	}
}