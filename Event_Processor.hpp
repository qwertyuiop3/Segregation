__int32 Recent_Player_Data_Number;

void Event_Processor(void* Unknown_Parameter, void* Event)
{
	void* Local_Player = *(void**)((unsigned __int64)Client_Module + 9394464);

	if (Local_Player != nullptr)
	{
		using Get_Name_Type = char*(*)(void* Event);

		char* Name = Get_Name_Type((unsigned __int64)Engine_Module + 1737440)(Event);
		
		using Get_Integer_Type = __int32(*)(void* Event, char* Key, void* Unknown_Parameter);

		__int32 Victim_Number;

		__int32 Killer_Number;

		if (Name[0] == 'p')
		{
			using Identifier_To_Number_Type = __int32(*)(void* Engine, __int32 Identifier);
			
			Victim_Number = Identifier_To_Number_Type((unsigned __int64)Engine_Module + 491424)((void*)((unsigned __int64)Engine_Module + 4670832), Get_Integer_Type((unsigned __int64)Engine_Module + 1737424)(Event, (char*)"userid", nullptr));

			Killer_Number = Identifier_To_Number_Type((unsigned __int64)Engine_Module + 491424)((void*)((unsigned __int64)Engine_Module + 4670832), Get_Integer_Type((unsigned __int64)Engine_Module + 1737424)(Event, (char*)"attacker", nullptr));
		}
		else
		{
			Victim_Number = Get_Integer_Type((unsigned __int64)Engine_Module + 1737424)(Event, (char*)"entindex_killed", nullptr);
			
			Killer_Number = Get_Integer_Type((unsigned __int64)Engine_Module + 1737424)(Event, (char*)"entindex_attacker", nullptr);
		}
		
		if (Victim_Number != Killer_Number)
		{
			if ((Killer_Number - 1 | (*(Global_Variables_Structure**)((unsigned __int64)Client_Module + 8690824))->Maximum_Clients - Killer_Number) >= 0)
			{
				__int32 Local_Number = *(__int32*)((unsigned __int64)Local_Player + 128);

				if (Victim_Number == Local_Number)
				{
					if (Name[0] == 'e')
					{
						Player_Data_Structure* Player_Data = &Players_Data[Killer_Number];

						Player_Data->Memory_Tolerance = 0;

						if (Interface_Commentator.Get_Integer() == 1)
						{
							PlaySoundW((wchar_t*)Sounds_Laugh, nullptr, SND_ASYNC | SND_MEMORY);
						}
					}
				}
				else
				{
					if (Killer_Number == Local_Number)
					{
						if (Victim_Number == Recent_Player_Data_Number)
						{
							Player_Data_Structure* Player_Data = &Players_Data[Victim_Number];

							if (Name[0] == 'p')
							{
								if (Player_Data->Memory_Tolerance == 0)
								{
									if (Player_Data->Tolerance == Interface_Bruteforce_Tolerance.Get_Integer())
									{
										if (Player_Data->Shots_Fired == 0)
										{
											Player_Data->Switch_X ^= 1;
										}

										Player_Data->Shots_Fired = ((Player_Data->Shots_Fired - 1) % Bruteforce_Angles_Count + Bruteforce_Angles_Count) % Bruteforce_Angles_Count;
									}
									else
									{
										Player_Data->Tolerance = Interface_Bruteforce_Tolerance.Get_Integer();
									}
								}
							}
							else
							{
								if (Interface_Bruteforce_Memory_Tolerance.Get_Integer() != 0)
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

						if (Name[0] == 'e')
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
}