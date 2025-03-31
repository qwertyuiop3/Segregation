struct Command_Structure
{
	__int8 Additional_Bytes_1[8];

	__int32 Tick_Number;

	float Angles[3];

	__int8 Additional_Bytes_2[12];

	float Move[3];

	__int32 Buttons;
};

Player_Data_Structure Previous_Recent_Player_Data;

void* Original_Copy_Command_Caller;

void __thiscall Redirected_Copy_Command(void* Unknown_Parameter, Command_Structure* Command)
{
	Update_Animation_Type = 1;

	using Update_Animations_Type = void(__cdecl*)();

	Update_Animations_Type((unsigned __int32)Client_Module + 1715328)();

	Update_Animation_Type = 0;

	void* Local_Player = *(void**)((unsigned __int32)Client_Module + 82926756);

	if (*(__int8*)((unsigned __int32)Local_Player + 603) == 0)
	{
		Command->Buttons |= 4194304;

		__int8 Move_Type = *(__int8*)((unsigned __int32)Local_Player + 600);

		if (*(void**)((unsigned __int32)Local_Player + 332) != INVALID_HANDLE_VALUE)
		{
			Command->Buttons &= ~(4 * Interface_High_Jump.Get_Integer());
		}

		auto Angle_Vectors = [](float* Angles, float* Forward, float* Right, float* Up) -> void
		{
			using Angle_Vectors_Type = __attribute__((regparm(3))) void(*)(void* Unknown_Parameter, float* Forward, float* Angles, float* Right, float* Up);

			Angle_Vectors_Type((unsigned __int32)Client_Module + 6691376)(nullptr, Forward, Angles, Right, Up);
		};

		float Move_Angles[3] =
		{
			Command->Angles[0],

			Command->Angles[1]
		};

		static float Previous_Move_Angle_Y;

		if ((Command->Buttons & 2) + Move_Type == 4)
		{
			Command->Move[0] = 0;

			if (*(void**)((unsigned __int32)Local_Player + 332) == INVALID_HANDLE_VALUE)
			{
				Command->Buttons &= ~2;
			}
			else
			{
				Command->Buttons &= ~(*(__int32*)((unsigned __int32)Local_Player + 12776) & 2);
			}

			float Difference = __builtin_remainderf(Move_Angles[1] - Previous_Move_Angle_Y, 360.f);

			Previous_Move_Angle_Y = Move_Angles[1];

			float* Velocity = (float*)((unsigned __int32)Local_Player + 272);

			if (__builtin_fabsf(Difference) < __builtin_atan2f(30.f, __builtin_hypotf(Velocity[0], Velocity[1])) * 180.f / 3.1415927f)
			{
				float Strafe_Angle = __builtin_remainderf(Move_Angles[1] - __builtin_atan2f(Velocity[1], Velocity[0]) * 180.f / 3.1415927f, 360.f);

				if (__builtin_signbitf(Strafe_Angle) == 0)
				{
					Command->Move[1] = -450.f;
				}
				else
				{
					Command->Move[1] = 450.f;
				}

				Move_Angles[1] -= Strafe_Angle;
			}
			else
			{
				if (__builtin_signbitf(Difference) == 0)
				{
					Command->Move[1] = -450.f;
				}
				else
				{
					Command->Move[1] = 450.f;
				}
			}
		}
		else
		{
			Previous_Move_Angle_Y = Move_Angles[1];
		}

		float Previous_Move[2];

		Byte_Manager::Copy_Bytes(1, Previous_Move, sizeof(Previous_Move), Command->Move);

		float Desired_Move[3];

		float Desired_Move_Forward[3];

		float Desired_Move_Right[3];

		Angle_Vectors(Move_Angles, Desired_Move_Forward, Desired_Move_Right, nullptr);

		auto Vector_Normalize = [](float* Vector) -> float
		{
			using Vector_Normalize_Type = float(__vectorcall*)(float* Vector);

			return Vector_Normalize_Type((unsigned __int32)Client_Module + 6688448)(Vector);
		};

		auto Get_Ladder_Move = [&](float* Move, float* Forward, float Forward_Move, float* Right, float Side_Move) -> void
		{
			Move[0] = Forward[0] * Forward_Move + Right[0] * Side_Move;

			Move[1] = Forward[1] * Forward_Move + Right[1] * Side_Move;

			float* Ladder_Normal = (float*)((unsigned __int32)Local_Player + 12820);

			float Normal = Move[0] * Ladder_Normal[0] + Move[1] * Ladder_Normal[1];

			Move[0] -= Ladder_Normal[0] * Normal;

			Move[1] -= Ladder_Normal[1] * Normal;

			Move[2] = (Forward[2] * Forward_Move + Right[2] * Side_Move) - (__builtin_powf(Ladder_Normal[0], 2.f) + __builtin_powf(Ladder_Normal[1], 2.f)) * Normal - Ladder_Normal[2] * Normal;
		};

		if (Move_Type == 2)
		{
			Desired_Move_Forward[2] = 0.f;

			Vector_Normalize(Desired_Move_Forward);

			Desired_Move_Right[2] = 0.f;

			Vector_Normalize(Desired_Move_Right);

			Desired_Move[0] = Desired_Move_Forward[0] * Command->Move[0] + Desired_Move_Right[0] * Command->Move[1];

			Desired_Move[1] = Desired_Move_Forward[1] * Command->Move[0] + Desired_Move_Right[1] * Command->Move[1];
		}
		else
		{
			Get_Ladder_Move(Desired_Move, Desired_Move_Forward, Command->Move[0], Desired_Move_Right, Command->Move[1]);
		}

		auto Correct_Movement = [&]() -> void
		{
			float Move_Forward[3];

			float Move_Right[3];

			Angle_Vectors(Command->Angles, Move_Forward, Move_Right, nullptr);

			if (Move_Type == 2)
			{
				Move_Forward[2] = 0.f;

				Vector_Normalize(Move_Forward);

				Move_Right[2] = 0.f;

				Vector_Normalize(Move_Right);

				float Divider = Move_Forward[0] * Move_Right[1] - Move_Right[0] * Move_Forward[1];

				Command->Move[0] = std::clamp((Desired_Move[0] * Move_Right[1] - Move_Right[0] * Desired_Move[1]) / Divider, -16383.999f, 16383.999f);

				Command->Move[1] = std::clamp((Move_Forward[0] * Desired_Move[1] - Desired_Move[0] * Move_Forward[1]) / Divider, -16383.999f, 16383.999f);
			}
			else
			{
				__int8 Solution_Number = 0;

				static float Solutions[9][3] =
				{
					{ -450.f },

					{ 0.f, -450.f },

					{ },

					{ 450.f },

					{ 0.f, 450.f },

					{ -450.f, -450.f },

					{ -450.f, 450.f },

					{ 450.f, -450.f },

					{ 450.f, 450.f }
				};

				float Least_Deviation = __builtin_inff();

				__int8 Solution;

				Traverse_Solutions_Label:
				{
					float Rotation = 0.f;

					Rotate_Solution_Label:
					{
						float Move[3];

						Command->Angles[2] = Rotation;

						Angle_Vectors(Command->Angles, Move_Forward, Move_Right, nullptr);

						Get_Ladder_Move(Move, Move_Forward, Solutions[Solution_Number][0], Move_Right, Solutions[Solution_Number][1]);

						float Deviation = __builtin_powf(Move[0] - Desired_Move[0], 2.f) + __builtin_powf(Move[1] - Desired_Move[1], 2.f) + __builtin_powf(Move[2] - Desired_Move[2], 2.f);

						if (Deviation < Least_Deviation)
						{
							Least_Deviation = Deviation;

							Solutions[Solution_Number][2] = Rotation;

							Solution = Solution_Number;
						}

						Rotation += 1.f;

						if (Rotation != 180.f)
						{
							goto Rotate_Solution_Label;
						}
					}

					Solution_Number += 1;

					if (Solution_Number != sizeof(Solutions) / sizeof(Solutions[0]))
					{
						goto Traverse_Solutions_Label;
					}
				}

				Command->Move[0] = Solutions[Solution][0];

				Command->Move[1] = Solutions[Solution][1];

				Command->Angles[2] = Solutions[Solution][2];
			}

			Command->Buttons &= ~1560;

			if (__builtin_truncf(Command->Move[0]) != 0.f)
			{
				Command->Buttons |= 8 * (__builtin_signbitf(Command->Move[0]) + 1);
			}

			if (__builtin_truncf(Command->Move[1]) != 0.f)
			{
				Command->Buttons |= 512 * ((__builtin_signbitf(Command->Move[1]) ^ 1) + 1);
			}
		};

		Correct_Movement();

		void* Previous_Audio_Device = *(void**)((unsigned __int32)Engine_Module + 8406032);

		*(void**)((unsigned __int32)Engine_Module + 8406032) = nullptr;

		using Set_Host_Type = void(__thiscall*)(void* Move_Helper, void* Player);

		Set_Host_Type((unsigned __int32)Client_Module + 2894464)((void*)((unsigned __int32)Client_Module + 11177912), Local_Player);

		using Run_Command_Type = void(__thiscall*)(void* Prediction, void* Player, Command_Structure* Command, void* Move_Helper);

		Run_Command_Type((unsigned __int32)Client_Module + 3037136)((void*)((unsigned __int32)Client_Module + 82620920), Local_Player, Command, (void*)((unsigned __int32)Client_Module + 11177912));

		Set_Host_Type((unsigned __int32)Client_Module + 2894464)((void*)((unsigned __int32)Client_Module + 11177912), nullptr);

		*(void**)((unsigned __int32)Engine_Module + 8406032) = Previous_Audio_Device;

		Byte_Manager::Copy_Bytes(1, Command->Move, sizeof(Previous_Move), Previous_Move);

		static __int8 Send_Packet;

		__int8 Animation_Ground = *(__int8*)(*(unsigned __int32*)((unsigned __int32)Local_Player + 14452) + 264);

		void* Client = *(void**)((unsigned __int32)Engine_Module + 5757076);

		__int32 Choked_Commands = *(__int32*)((unsigned __int32)Client + 19632);

		Update_Animation_Type = (Choked_Commands == 0) * 2;

		Redirected_Update_Animation(Local_Player);

		Update_Animation_Type = 0;

		float* Local_Origin = (float*)((unsigned __int32)Local_Player + 308);

		if (0)
		{
			Send_Packet_Label:
			{
				Byte_Manager::Copy_Bytes(1, Local_Networked_Origin, sizeof(Local_Networked_Origin), Local_Origin);

				Send_Packet = 1;
			}
		}
		else
		{
			if (Send_Packet == 2)
			{
				goto Send_Packet_Label;
			}

			if (Choked_Commands >= Interface_Minimum_Choked_Commands.Get_Integer())
			{
				if (Choked_Commands >= Interface_Maximum_Choked_Commands.Get_Integer())
				{
					goto Send_Packet_Label;
				}

				if (__builtin_powf(Local_Networked_Origin[0] - Local_Origin[0], 2.f) + __builtin_powf(Local_Networked_Origin[1] - Local_Origin[1], 2.f) + __builtin_powf(Local_Networked_Origin[2] - Local_Origin[2], 2.f) > 4096.f)
				{
					goto Send_Packet_Label;
				}
			}

			Send_Packet = 0;
		}

		__int32 Entity_Number = 1;

		using Get_Latency_Type = float(__thiscall*)(void* Network_Channel, __int32 Type);

		void* Network_Channel = *(void**)((unsigned __int32)Client + 156);

		float Latency = Get_Latency_Type((unsigned __int32)Engine_Module + 2299408)(Network_Channel, 0);

		using Get_Interpolation_Time_Type = float(__vectorcall*)();

		float Interpolation_Time = Get_Interpolation_Time_Type((unsigned __int32)Engine_Module + 918912)();

		float Corrected_Latency = std::clamp(Latency + Interpolation_Time, 0.f, 1.f);

		Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)((unsigned __int32)Client_Module + 10871344);

		struct Target_Structure
		{
			__int32 Priority;

			void* Self;

			__int32 Tick_Number;

			__int8 Valid;

			float Distance;
		};

		static std::vector<Target_Structure> Sorted_Target_List;

		Sorted_Target_List.clear();

		Traverse_Entity_List_Label:
		{
			Player_Data_Structure* Player_Data = &Players_Data[Entity_Number];

			if (Player_Data->Priority != -1)
			{
				void* Entity = *(void**)((unsigned __int32)Client_Module + 78250580 + ((Entity_Number - 8193) << 4));

				if (Entity != nullptr)
				{
					if (*(__int8*)((unsigned __int32)Entity + 603) == 0)
					{
						if (*(__int32*)((unsigned __int32)Entity + 240) != *(__int32*)((unsigned __int32)Local_Player + 240))
						{
							if (*(__int8*)((unsigned __int32)Entity + 233) == 0)
							{
								float Entity_Time = *(float*)((unsigned __int32)Entity + 612);

								float* Entity_Origin = (float*)((unsigned __int32)Entity + 308);

								Target_Structure Target =
								{
									Player_Data->Priority == -2 ? 0 : Player_Data->Priority,

									Entity,

									(__int32)((Entity_Time + Interpolation_Time) / Global_Variables->Interval_Per_Tick + 0.5f),

									__builtin_fabsf(Corrected_Latency - ((Global_Variables->Tick_Number + (Interface_Alternative.Get_Integer() ^ 1)) * Global_Variables->Interval_Per_Tick + Latency - Entity_Time)) <= 0.2f,

									__builtin_powf(Local_Origin[0] - Entity_Origin[0], 2.f) + __builtin_powf(Local_Origin[1] - Entity_Origin[1], 2.f) + __builtin_powf(Local_Origin[2] - Entity_Origin[2], 2.f)
								};

								if (Interface_Target_On_Simulation.Get_Integer() != 0)
								{
									Target.Valid *= Player_Data->Simulated;
								}

								Sorted_Target_List.push_back(Target);
							}
						}
					}
				}
			}

			if (Entity_Number != Global_Variables->Maximum_Clients)
			{
				Entity_Number += 1;

				goto Traverse_Entity_List_Label;
			}
		}

		auto Target_List_Sort_Prepare = [](Target_Structure& X, Target_Structure& Y) -> __int8
		{
			return X.Priority < Y.Priority;
		};

		std::sort(Sorted_Target_List.begin(), Sorted_Target_List.end(), Target_List_Sort_Prepare);

		auto Target_List_Sort_Finish = [](Target_Structure& X, Target_Structure& Y) -> __int8
		{
			if (X.Priority > Y.Priority)
			{
				return 1;
			}

			return X.Distance < Y.Distance;
		};

		std::sort(Sorted_Target_List.begin(), Sorted_Target_List.end(), Target_List_Sort_Finish);

		__int8 In_Attack = 0;

		if (__builtin_fabsf(Global_Variables->Current_Time - Shot_Time) > 0.5f)
		{
			if (Shot_Time == 0)
			{
				Passed_Shot_Time_Check_Label:
				{
					if ((Command->Buttons & 2048) == 0)
					{
						if (Send_Packet * (Interface_Alternative.Get_Integer() ^ 1) == (Choked_Commands == 0) * 3)
						{
							if (*(float*)((unsigned __int32)Local_Player + 11616) <= Global_Variables->Current_Time)
							{
								using Get_Weapon_Type = void*(__thiscall*)(void* Entity);

								void* Weapon = Get_Weapon_Type((unsigned __int32)Client_Module + 1513024)(Local_Player);

								if (Weapon != nullptr)
								{
									using Get_Weapon_Information_Type = void*(__thiscall*)(void* Weapon);

									void* Weapon_Information = Get_Weapon_Information_Type((unsigned __int32)Client_Module + 5306512)(Weapon);

									if (*(__int32*)((unsigned __int32)Weapon + 12796) * (*(__int32*)((unsigned __int32)Weapon_Information + 20) != 1) * (*(__int32*)((unsigned __int32)Weapon_Information + 20) != 8) > 0)
									{
										if (*(__int32*)((unsigned __int32)Weapon + 12804) > 0)
										{
											if (*(float*)((unsigned __int32)Weapon + 12760) <= Global_Variables->Current_Time)
											{
												size_t Target_Number = 0;

												float Weapon_Range = *(float*)((unsigned __int32)Weapon_Information + 260);

												Recent_Player_Data_Number = 0;

												Traverse_Sorted_Target_List_Label:
												{
													if (Target_Number != Sorted_Target_List.size())
													{
														Target_Structure* Target = &Sorted_Target_List.at(Target_Number);

														if (Target->Valid == 1)
														{
															Redirected_Compute_Torso_Rotation(*(void**)((unsigned __int32)Target->Self + 14452));

															*(__int32*)((unsigned __int32)Target->Self + 9856) = *(__int32*)((unsigned __int32)Client_Module + 83358788) - 1;

															*(__int32*)((unsigned __int32)Target->Self + 10516) = -8388609;

															float Bones[256][3][4];

															if (Redirected_Setup_Bones((void*)((unsigned __int32)Target->Self + 4), Bones, sizeof(Bones) / sizeof(Bones[0]), 1048320, Global_Variables->Current_Time) == 1)
															{
																auto Perform_Trace = [&](float* Eye_Position, float Direction[3]) -> __int8
																{
																	struct alignas(16) Ray_Structure
																	{
																		__int8 Additional_Bytes[65];
																	};

																	struct Filter_Structure
																	{
																		void* Table;

																		void* Skip;

																		__int8 Additional_Bytes[8];
																	};

																	struct Trace_Structure
																	{
																		__int8 Additional_Bytes_1[68];

																		__int32 Group;

																		__int8 Additional_Bytes_2[4];

																		void* Entity;

																		__int8 Additional_Bytes_3[4];
																	};

																	using Perform_Trace_Type = void(__thiscall*)(void* Tracer, Ray_Structure* Ray, __int32 Mask, Filter_Structure* Filter, Trace_Structure* Trace);

																	using Initialize_Ray_Type = void(__thiscall*)(Ray_Structure* Ray, float* Start, float* End);

																	Ray_Structure Ray;

																	Vector_Normalize(Direction);

																	float End[3]
																	{
																		Eye_Position[0] + Direction[0] * Weapon_Range,

																		Eye_Position[1] + Direction[1] * Weapon_Range,

																		Eye_Position[2] + Direction[2] * Weapon_Range
																	};

																	Initialize_Ray_Type((unsigned __int32)Client_Module + 1519376)(&Ray, Eye_Position, End);

																	Filter_Structure Filter = { (void*)((unsigned __int32)Client_Module + 9400096), Local_Player };

																	Trace_Structure Trace;

																	Perform_Trace_Type((unsigned __int32)Engine_Module + 2031072)((void*)((unsigned __int32)Engine_Module + 5799956), &Ray, 1174421515, &Filter, &Trace);
																	
																	using Clip_Trace_Type = __attribute__((regparm(3))) void(*)(void* Unknown_Parameter_1, float* End, float* Start, __int32 Mask, Filter_Structure* Filter, Trace_Structure* Trace, void* Unknown_Parameter_2);

																	End[0] += Direction[0] * 40.f;

																	End[1] += Direction[1] * 40.f;

																	End[2] += Direction[2] * 40.f;

																	Clip_Trace_Type((unsigned __int32)Client_Module + 3237600)(nullptr, End, Eye_Position, 1174421515, &Filter, &Trace, nullptr);

																	if (Trace.Entity == Target->Self)
																	{
																		if (Interface_Aim_Intersection.Get_Integer() == 0)
																		{
																			return Trace.Group == 1;
																		}

																		return 1;
																	}

																	return 0;
																};

																using Get_Studio_Header_Type = void*(__thiscall*)(void* Entity);

																void* Studio_Header = *(void**)Get_Studio_Header_Type((unsigned __int32)Client_Module + 1466768)(Target->Self);

																void* Hitbox_Set = (void*)((unsigned __int32)Studio_Header + *(__int32*)((unsigned __int32)Studio_Header + 176));

																float* Hitbox_Minimum = (float*)((unsigned __int32)Hitbox_Set + 20);

																float* Hitbox_Maximum = (float*)((unsigned __int32)Hitbox_Set + 32);

																float Hitbox_Center[3]
																{
																	(Hitbox_Minimum[0] + Hitbox_Maximum[0]) / 2.f,

																	(Hitbox_Minimum[1] + Hitbox_Maximum[1]) / 2.f,

																	(Hitbox_Minimum[2] + Hitbox_Maximum[2]) / 2.f
																};

																float Hitbox_Z_Vertices[8]
																{
																	Bones[8][2][0] * Hitbox_Minimum[0] + Bones[8][2][1] * Hitbox_Minimum[1] + Bones[8][2][2] * Hitbox_Minimum[2],

																	Bones[8][2][0] * Hitbox_Maximum[0] + Bones[8][2][1] * Hitbox_Minimum[1] + Bones[8][2][2] * Hitbox_Minimum[2],

																	Bones[8][2][0] * Hitbox_Minimum[0] + Bones[8][2][1] * Hitbox_Maximum[1] + Bones[8][2][2] * Hitbox_Minimum[2],

																	Bones[8][2][0] * Hitbox_Minimum[0] + Bones[8][2][1] * Hitbox_Minimum[1] + Bones[8][2][2] * Hitbox_Maximum[2],

																	Bones[8][2][0] * Hitbox_Maximum[0] + Bones[8][2][1] * Hitbox_Maximum[1] + Bones[8][2][2] * Hitbox_Minimum[2],

																	Bones[8][2][0] * Hitbox_Maximum[0] + Bones[8][2][1] * Hitbox_Minimum[1] + Bones[8][2][2] * Hitbox_Maximum[2],

																	Bones[8][2][0] * Hitbox_Minimum[0] + Bones[8][2][1] * Hitbox_Maximum[1] + Bones[8][2][2] * Hitbox_Maximum[2],

																	Bones[8][2][0] * Hitbox_Maximum[0] + Bones[8][2][1] * Hitbox_Maximum[1] + Bones[8][2][2] * Hitbox_Maximum[2]
																};

																float* Hitbox_Z_Extremes[2];

																std::tie(Hitbox_Z_Extremes[0], Hitbox_Z_Extremes[1]) = std::minmax_element(Hitbox_Z_Vertices, &Hitbox_Z_Vertices[sizeof(Hitbox_Z_Vertices) / sizeof(Hitbox_Z_Vertices[0])]);

																float Radius = *(float*)((unsigned __int32)Hitbox_Set + 60);

																*Hitbox_Z_Extremes[0] -= Radius;

																*Hitbox_Z_Extremes[1] += Radius;

																float Target_Origin[3] =
																{
																	Bones[8][0][0] * Hitbox_Center[0] + Bones[8][0][1] * Hitbox_Center[1] + Bones[8][0][2] * Hitbox_Center[2] + Bones[8][0][3],

																	Bones[8][1][0] * Hitbox_Center[0] + Bones[8][1][1] * Hitbox_Center[1] + Bones[8][1][2] * Hitbox_Center[2] + Bones[8][1][3]
																};

																*(__int32*)((unsigned __int32)Local_Player + 9856) = *(__int32*)((unsigned __int32)Client_Module + 83358788) - 1;

																float Previous_Incline = *(float*)((unsigned __int32)Local_Player + 10132);

																*(float*)((unsigned __int32)Local_Player + 10132) = Local_Origin[2] + *(float*)((unsigned __int32)Local_Player + 268) >= *Hitbox_Z_Extremes[0] + (*Hitbox_Z_Extremes[1] - *Hitbox_Z_Extremes[0]) * 0.5f + Bones[8][2][3];

																*(__int32*)((unsigned __int32)Local_Player + 10516) = -8388609;

																using Get_Eye_Position_Type = void(__thiscall*)(void* Entity, float* Eye_Position);

																float Eye_Position[3];

																Get_Eye_Position_Type((unsigned __int32)Client_Module + 3820128)(Local_Player, Eye_Position);

																*(float*)((unsigned __int32)Local_Player + 10132) = Previous_Incline;

																__int8 Aim_Height_Number = 0;

																Traverse_Aim_Heights_Label:
																{
																	float Aim_Height = Aim_Heights[Aim_Height_Number];

																	Target_Origin[2] = *Hitbox_Z_Extremes[0] + (*Hitbox_Z_Extremes[1] - *Hitbox_Z_Extremes[0]) * Aim_Height + Bones[8][2][3];

																	float Direction[3] =
																	{
																		Target_Origin[0] - Eye_Position[0],

																		Target_Origin[1] - Eye_Position[1],

																		Target_Origin[2] - Eye_Position[2]
																	};

																	if (Perform_Trace(Eye_Position, Direction) == 1)
																	{
																		Command->Tick_Number = Target->Tick_Number;

																		Command->Angles[0] = __builtin_atan2f(-Direction[2], __builtin_hypotf(Direction[0], Direction[1])) * 180.f / 3.1415927f;

																		Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180.f / 3.1415927f;

																		Command->Buttons |= 1;

																		if (Interface_Bruteforce.Get_Integer() == 1)
																		{
																			__int32 Target_Number = *(__int32*)((unsigned __int32)Target->Self + 100);

																			Player_Data_Structure* Player_Data = &Players_Data[Target_Number];

																			if (Player_Data->Priority != -2)
																			{
																				Recent_Player_Data_Number = Target_Number;

																				Byte_Manager::Copy_Bytes(1, &Previous_Recent_Player_Data, sizeof(Previous_Recent_Player_Data), Player_Data);

																				if (Player_Data->Memory_Tolerance == 0)
																				{
																					if (Player_Data->Tolerance == 0)
																					{
																						Player_Data->Shots_Fired = (Player_Data->Shots_Fired + 1) % Bruteforce_Angles_Count;

																						Player_Data->Switch_X += (Player_Data->Shots_Fired == 0);

																						Player_Data->Tolerance = Interface_Bruteforce_Tolerance.Get_Integer();
																					}
																					else
																					{
																						Player_Data->Tolerance -= 1;
																					}
																				}
																				else
																				{
																					Player_Data->Memory_Tolerance -= 1;
																				}
																			}
																		}

																		goto Found_Target_Label;
																	}

																	Aim_Height_Number += 1;

																	if (Aim_Height_Number != Aim_Heights_Count)
																	{
																		goto Traverse_Aim_Heights_Label;
																	}
																}
															}
														}

														Target_Number += 1;

														goto Traverse_Sorted_Target_List_Label;

														Found_Target_Label:
														{

														}
													}
												}

												if ((Command->Buttons & 1) == 1)
												{
													Command->Angles[0] = -Command->Angles[0] + 180.f;

													Command->Angles[1] += 180.f;

													In_Attack = 1;

													Send_Packet = Interface_Alternative.Get_Integer() * 2;

													Shot_Time = Global_Variables->Current_Time;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			else
			{
				Shot_Time = 0;

				if (Recent_Player_Data_Number == 0)
				{
					goto Passed_Shot_Time_Check_Label;
				}

				Player_Data_Structure* Player_Data = &Players_Data[Recent_Player_Data_Number];

				Previous_Recent_Player_Data.Priority = Player_Data->Priority;

				Previous_Recent_Player_Data.Simulated = Player_Data->Simulated;

				Previous_Recent_Player_Data.Networked_Angle = Player_Data->Networked_Angle;

				Previous_Recent_Player_Data.Animation_Angle = Player_Data->Animation_Angle;

				Byte_Manager::Copy_Bytes(1, Player_Data, sizeof(Previous_Recent_Player_Data), &Previous_Recent_Player_Data);

				goto Passed_Shot_Time_Check_Label;
			}
		}

		Command->Buttons &= ~2048;

		if (In_Attack == 0)
		{
			Command->Buttons &= ~1;

			if (Sorted_Target_List.size() != 0)
			{
				Command->Angles[0] = Interface_Angle_X.Get_Floating_Point();

				float* Target_Origin = (float*)((unsigned __int32)Sorted_Target_List.at(0).Self + 308);

				float Direction[2] =
				{
					Target_Origin[0] - Local_Origin[0],

					Target_Origin[1] - Local_Origin[1]
				};

				if (Animation_Ground == 0)
				{
					if (Choked_Commands == 0)
					{
						Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180.f / 3.1415927f + Interface_Animated_Angle_Y.Get_Floating_Point();
					}
					else
					{
						Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180.f / 3.1415927f + Interface_Angle_Y.Get_Floating_Point();
					}
				}
				else
				{
					if ((Command->Buttons & 2) == 2)
					{
						if (Interface_Body_Update.Get_Integer() == 1)
						{
							Send_Packet = -(Choked_Commands <= Interface_Maximum_Choked_Commands.Get_Integer());
						}

						Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180.f / 3.1415927f + Interface_Body_Angle_Y.Get_Floating_Point();
					}
					else
					{
						Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180.f / 3.1415927f;
					}
				}
			}
		}

		Correct_Movement();

		if (Send_Packet <= 0)
		{
			__int32 Sequence_Number = *(__int32*)((unsigned __int32)Network_Channel + 24) = Redirected_Send_Datagram(Network_Channel, nullptr);

			Sequences[Sequence_Number % 150] = *(__int32*)((unsigned __int32)Client + 19628);
		}
		else
		{
			Update_Animation_Delta[1] = Choked_Commands + 1;

			Byte_Manager::Copy_Bytes(1, Update_Animation_Angles, sizeof(Update_Animation_Angles), Command->Angles);
		}

		*(__int8*)((unsigned __int32)__builtin_frame_address(0) + 20) = max(0, Send_Packet);

		if (In_Attack * (Interface_Alternative.Get_Integer() ^ 1) + (Send_Packet == -1) == 1)
		{
			Send_Packet = 2;
		}
	}
	else
	{
		*(__int8*)((unsigned __int32)__builtin_frame_address(0) + 20) = 1;
	}

	(decltype(&Redirected_Copy_Command)(Original_Copy_Command_Caller))(Unknown_Parameter, Command);
}