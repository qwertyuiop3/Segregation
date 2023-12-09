Player_Data_Structure Previous_Recent_Player_Data;

void* Original_Copy_Command_Caller;

void __thiscall Redirected_Copy_Command(void* Unknown_Parameter, Command_Structure* Command)
{
	Command->Extra_Simulations = 0;

	void* Local_Player = *(void**)((unsigned __int32)Client_Module + 5015784);

	if (*(__int8*)((unsigned __int32)Local_Player + 147) == 0)
	{
		using Run_Prediction_Type = void(__cdecl*)();

		Run_Prediction_Type((unsigned __int32)Engine_Module + 792144)();

		auto Angle_Vectors = [](float* Angles, float* Forward, float* Right, float* Up) -> void
		{
			using Angle_Vectors_Type = void(__cdecl*)(float* Angles, float* Forward, float* Right, float* Up);

			Angle_Vectors_Type((unsigned __int32)Client_Module + 2568048)(Angles, Forward, Right, Up);
		};

		float Move_Angles[3] =
		{
			Command->Angles[0],

			Command->Angles[1],

			0
		};

		static float Previous_Move_Angle_Y;

		if ((Command->Buttons & 2) == 2)
		{
			Command->Move[0] = 0;

			if (*(__int32*)((unsigned __int32)Local_Player + 596) == -1)
			{
				Command->Buttons &= ~(*(__int32*)((unsigned __int32)Local_Player + 376) & 2);
			}
			else
			{
				Command->Buttons &= ~(*(__int32*)((unsigned __int32)Local_Player + 4120) & 2);
			}

			float Difference = __builtin_remainderf(Move_Angles[1] - Previous_Move_Angle_Y, 360);

			Previous_Move_Angle_Y = Move_Angles[1];

			float* Velocity = (float*)((unsigned __int32)Local_Player + 244);

			if (__builtin_fabsf(Difference) < __builtin_atan2f(30, __builtin_hypotf(Velocity[0], Velocity[1])) * 180 / 3.1415927f)
			{
				float Strafe_Angle = __builtin_remainderf(Move_Angles[1] - __builtin_atan2f(Velocity[1], Velocity[0]) * 180 / 3.1415927f, 360);

				if (__builtin_signbitf(Strafe_Angle) == 0)
				{
					Command->Move[1] = -400;
				}
				else
				{
					Command->Move[1] = 400;
				}

				Move_Angles[1] -= Strafe_Angle;
			}
			else
			{
				if (__builtin_signbitf(Difference) == 0)
				{
					Command->Move[1] = -400;
				}
				else
				{
					Command->Move[1] = 400;
				}
			}
		}
		else
		{
			Previous_Move_Angle_Y = Move_Angles[1];
		}

		float Previous_Move[2] =
		{
			Command->Move[0],

			Command->Move[1]
		};

		float Desired_Move_Forward[3];

		float Desired_Move_Right[3];

		Angle_Vectors(Move_Angles, Desired_Move_Forward, Desired_Move_Right, nullptr);

		Desired_Move_Forward[2] = 0;

		auto Vector_Normalize = [](float* Vector) -> float
		{
			using Vector_Normalize_Type = float(__thiscall*)(float* Vector);

			return Vector_Normalize_Type((unsigned __int32)Client_Module + 2565744)(Vector);
		};

		Vector_Normalize(Desired_Move_Forward);

		Desired_Move_Right[2] = 0;

		Vector_Normalize(Desired_Move_Right);

		float Desired_Move[2] =
		{
			Desired_Move_Forward[0] * Command->Move[0] + Desired_Move_Right[0] * Command->Move[1],

			Desired_Move_Forward[1] * Command->Move[0] + Desired_Move_Right[1] * Command->Move[1]
		};

		auto Correct_Movement = [&]() -> void
		{
			float Move_Forward[3];

			float Move_Right[3];

			Angle_Vectors(Command->Angles, Move_Forward, Move_Right, nullptr);

			Move_Forward[2] = 0;

			Vector_Normalize(Move_Forward);

			Move_Right[2] = 0;

			Vector_Normalize(Move_Right);

			float Divider = Move_Forward[0] * Move_Right[1] - Move_Right[0] * Move_Forward[1];

			float X = std::clamp((Desired_Move[0] * Move_Right[1] - Move_Right[0] * Desired_Move[1]) / Divider, -16383.999f, 16383.999f);

			Command->Move[0] = X;

			Command->Buttons &= ~1560;

			if (__builtin_truncf(X) != 0)
			{
				Command->Buttons |= 8 * ((X < 0) + 1);
			}

			float Y = std::clamp((Move_Forward[0] * Desired_Move[1] - Desired_Move[0] * Move_Forward[1]) / Divider, -16383.999f, 16383.999f);

			Command->Move[1] = Y;

			if (__builtin_truncf(X) != 0)
			{
				Command->Buttons |= 512 * ((Y > 0) + 1);
			}
		};

		Correct_Movement();

		void* Previous_Audio_Device = *(void**)((unsigned __int32)Engine_Module + 4334668);

		*(void**)((unsigned __int32)Engine_Module + 4334668) = nullptr;

		float Local_Player_Previous_Origin[2];

		float* Local_Player_Origin = (float*)((unsigned __int32)Local_Player + 824);

		if (Interface_Alternative.Integer == 0)
		{
			Byte_Manager::Copy_Bytes(0, Local_Player_Previous_Origin, sizeof(Local_Player_Previous_Origin), Local_Player_Origin);
		}

		using Run_Command_Type = void(__thiscall*)(void* Prediction, void* Local_Player, Command_Structure* Command, void* Move_Helper);

		Run_Command_Type((unsigned __int32)Client_Module + 1552000)(*(void**)((unsigned __int32)Engine_Module + 4566764), Local_Player, Command, (void*)((unsigned __int32)Client_Module + 4839036));

		*(void**)((unsigned __int32)Engine_Module + 4334668) = Previous_Audio_Device;

		Command->Move[0] = Previous_Move[0];

		Command->Move[1] = Previous_Move[1];

		static __int8 Send_Packet;

		__int32 Choked_Commands_Count = *(__int32*)((unsigned __int32)Engine_Module + 4702944);

		__int8 Predicted_Send_Packet = 0;

		static float Networked_Origin[2];

		if (Interface_Alternative.Integer == 0)
		{
			__int32 Predicted_Choked_Commands_Count = Choked_Commands_Count + 1;

			if (Choked_Commands_Count < Interface_Minimum_Choked_Commands.Integer)
			{
				Send_Packet = 0;

				if (Predicted_Choked_Commands_Count == Interface_Minimum_Choked_Commands.Integer)
				{
					if (Predicted_Choked_Commands_Count < Interface_Maximum_Choked_Commands.Integer)
					{
						goto Predict_Dynamic_Send_Packet_Label;
					}
					else
					{
						Predicted_Send_Packet = 1;
					}
				}
			}
			else
			{
				if (Choked_Commands_Count < Interface_Maximum_Choked_Commands.Integer)
				{
					if (__builtin_hypotf(Networked_Origin[0] - Local_Player_Previous_Origin[0], Networked_Origin[1] - Local_Player_Previous_Origin[1]) <= 64)
					{
						Send_Packet = 0;

						Predict_Dynamic_Send_Packet_Label:
						{
							if (Predicted_Choked_Commands_Count == Interface_Maximum_Choked_Commands.Integer)
							{
								Predicted_Send_Packet = 1;
							}
							else
							{
								if (__builtin_hypotf(Networked_Origin[0] - Local_Player_Origin[0], Networked_Origin[1] - Local_Player_Origin[1]) > 64)
								{
									Predicted_Send_Packet = 1;
								}
							}
						}

					}
					else
					{
						Send_Packet_Label:
						{
							Byte_Manager::Copy_Bytes(0, Networked_Origin, sizeof(Networked_Origin), Local_Player_Origin);

							Send_Packet = 1;
						}
					}
				}
				else
				{
					goto Send_Packet_Label;
				}
			}
		}
		else
		{
			if (Send_Packet == 2)
			{
				goto Send_Packet_Label;
			}

			if (Choked_Commands_Count < Interface_Minimum_Choked_Commands.Integer)
			{
				Send_Packet = 0;
			}
			else
			{
				if (Choked_Commands_Count < Interface_Maximum_Choked_Commands.Integer)
				{
					if (__builtin_hypotf(Networked_Origin[0] - Local_Player_Origin[0], Networked_Origin[1] - Local_Player_Origin[1]) <= 64)
					{
						Send_Packet = 0;
					}
					else
					{
						goto Send_Packet_Label;
					}
				}
				else
				{
					goto Send_Packet_Label;
				}
			}
		}

		__int32 Entity_Number = 1;

		__int32 Team_Number = *(__int32*)((unsigned __int32)Local_Player + 156);

		using Get_Latency_Type = float(__thiscall*)(void* Network_Channel, __int32 Type);

		void* Network_Channel = *(void**)((unsigned __int32)Engine_Module + 4683720);

		float Total_Latency = Get_Latency_Type((unsigned __int32)Engine_Module + 1871040)(Network_Channel, 0) + Get_Latency_Type((unsigned __int32)Engine_Module + 1871040)(Network_Channel, 1);

		float Interpolation_Time = max(*(float*)((unsigned __int32)Client_Module + 5064356), std::clamp(*(float*)((unsigned __int32)Client_Module + 5064284), *(float*)((unsigned __int32)Engine_Module + 6385172), *(float*)((unsigned __int32)Engine_Module + 6385244)) / std::clamp(*(__int32*)((unsigned __int32)Engine_Module + 6429584), *(__int32*)((unsigned __int32)Engine_Module + 6190472), *(__int32*)((unsigned __int32)Engine_Module + 6190400)));

		float Corrected_Total_Latency = std::clamp(Total_Latency + Interpolation_Time, 0.f, 1.f);

		Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)((unsigned __int32)Client_Module + 4825720);

		struct alignas(16) Target_Structure
		{
			__int8 Priority;

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
				void* Entity = *(void**)((unsigned __int32)Client_Module + 5135076 + ((Entity_Number - 4097) << 4));

				if (Entity != nullptr)
				{
					if (*(__int8*)((unsigned __int32)Entity + 147) == 0)
					{
						if (*(__int32*)((unsigned __int32)Entity + 156) != Team_Number)
						{
							if (*(__int8*)((unsigned __int32)Entity + 382) == 0)
							{
								__int32 Tick_Number = (*(float*)((unsigned __int32)Entity + 108) + Interpolation_Time) / Global_Variables->Interval_Per_Tick + 0.5f;

								float* Entity_Origin = (float*)((unsigned __int32)Entity + 824);

								Target_Structure Target =
								{
									Player_Data->Priority == -2 ? (__int8)0 : Player_Data->Priority,

									Entity,

									Tick_Number,

									__builtin_fabsf(Corrected_Total_Latency - (__int32)(Global_Variables->Tick_Number + (Interface_Alternative.Integer == 0) + Total_Latency / Global_Variables->Interval_Per_Tick + 0.5f - Tick_Number) * Global_Variables->Interval_Per_Tick) <= 0.2f,

									__builtin_powf(Local_Player_Origin[0] - Entity_Origin[0], 2) + __builtin_powf(Local_Player_Origin[1] - Entity_Origin[1], 2) + __builtin_powf(Local_Player_Origin[2] - Entity_Origin[2], 2)
								};

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

		if (Command->Select == 0)
		{
			if (__builtin_fabsf(Global_Variables->Current_Time - Shot_Time) > 0.5f)
			{
				if (Shot_Time == 0)
				{
					Passed_Shot_Time_Check_Label:
					{
						if ((Command->Buttons & 2048) == 0)
						{
							__int8 Send_Packet_Sequence = (Send_Packet == 0) + (Predicted_Send_Packet == 1);

							if (Interface_Alternative.Integer != 0)
							{
								Send_Packet_Sequence = 2;
							}

							if (Send_Packet_Sequence == 2)
							{
								if (*(float*)((unsigned __int32)Local_Player + 3128) <= Global_Variables->Current_Time)
								{
									void* Weapon = *(void**)((unsigned __int32)Client_Module + 5135076 + (((*(unsigned __int32*)((unsigned __int32)Local_Player + 3456) & 4095) - 4097) << 4));

									if (Weapon != nullptr)
									{
										if (*(__int32*)((unsigned __int32)Weapon + 2228) != -1)
										{
											if (*(__int32*)((unsigned __int32)Weapon + 2236) > 0)
											{
												if (*(float*)((unsigned __int32)Weapon + 2168) <= Global_Variables->Current_Time)
												{
													size_t Target_Number = 0;

													using Get_Eye_Position_Type = void(__thiscall*)(void* Player, float* Eye_Position);

													float Eye_Position[3];

													Get_Eye_Position_Type((unsigned __int32)Client_Module + 415008)(Local_Player, Eye_Position);

													using Get_Weapon_Information_Type = void*(__thiscall*)(void* Weapon);

													float Weapon_Range = *(float*)((unsigned __int32)Get_Weapon_Information_Type((unsigned __int32)Client_Module + 403600)(Weapon) + 2188);

													Recent_Player_Data_Number = 0;

													Traverse_Sorted_Target_List_Label:
													{
														if (Target_Number != Sorted_Target_List.size())
														{
															Target_Structure* Target = &Sorted_Target_List.at(Target_Number);

															if (Target->Valid == 1)
															{
																Redirected_Compute_Torso_Rotation((void*)(*(unsigned __int32*)((unsigned __int32)Target->Self + 5112) - 148));

																using Setup_Bones_Type = __int8(__thiscall*)(void* Entity, void* Bones, __int32 Maximum_Bones, __int32 Mask, float Current_Time);

																float Bones[128][3][4];

																if (Setup_Bones_Type((unsigned __int32)Client_Module + 560320)((void*)((unsigned __int32)Target->Self + 4), Bones, 128, 524032, Global_Variables->Current_Time) == 1)
																{
																	auto Trace_Ray = [&](float Direction[3]) -> __int8
																	{
																		using Trace_Ray_Type = void(__thiscall*)(void* Engine, Ray_Structure* Ray, __int32 Mask, Filter_Structure* Filter, Trace_Structure* Trace);

																		using Initialize_Ray_Type = void(__thiscall*)(Ray_Structure* Ray, float* Start, float* End);

																		Ray_Structure Ray;

																		Vector_Normalize(Direction);

																		float End[3]
																		{
																			Eye_Position[0] + Direction[0] * Weapon_Range,

																			Eye_Position[1] + Direction[1] * Weapon_Range,

																			Eye_Position[2] + Direction[2] * Weapon_Range
																		};

																		Initialize_Ray_Type((unsigned __int32)Client_Module + 389504)(&Ray, Eye_Position, End);

																		Filter_Structure Filter;

																		Filter.Table = (void*)((unsigned __int32)Client_Module + 3908280);

																		Filter.Skip = Local_Player;

																		Filter.Group = 0;

																		Filter.Handler = nullptr;

																		Trace_Structure Trace;

																		Trace_Ray_Type((unsigned __int32)Engine_Module + 1658128)((void*)((unsigned __int32)Engine_Module + 3941436), &Ray, 1174421515, &Filter, &Trace);

																		using Clip_Trace_To_Players_Type = void(__cdecl*)(float* Start, float* End, __int32 Mask, Filter_Structure* Filter, Trace_Structure* Trace);

																		End[0] += Direction[0] * 40;

																		End[1] += Direction[1] * 40;

																		End[2] += Direction[2] * 40;

																		Clip_Trace_To_Players_Type((unsigned __int32)Client_Module + 1695232)(Eye_Position, End, 1174421515, &Filter, &Trace);

																		if (Trace.Entity == Target->Self)
																		{
																			if (Interface_Aim_Intersection.Integer == 0)
																			{
																				return Trace.Group == 1;
																			}

																			return 1;
																		}

																		return 0;
																	};

																	using Get_Studio_Header_Type = void* (__thiscall*)(void* Entity);

																	void* Studio_Header = *(void**)Get_Studio_Header_Type(((unsigned __int32)Client_Module + 541120))(Target->Self);

																	void* Hitbox_Set = (void*)((unsigned __int32)Studio_Header + *(__int32*)((unsigned __int32)Studio_Header + 176));

																	float* Hitbox_Minimum = (float*)((unsigned __int32)Hitbox_Set + 836);

																	float* Hitbox_Maximum = (float*)((unsigned __int32)Hitbox_Set + 848);

																	float Hitbox_Center[3]
																	{
																		(Hitbox_Minimum[0] + Hitbox_Maximum[0]) / 2,

																		(Hitbox_Minimum[1] + Hitbox_Maximum[1]) / 2,

																		(Hitbox_Minimum[2] + Hitbox_Maximum[2]) / 2
																	};

																	float Hitbox_Z_Vertices[8]
																	{
																		Bones[14][2][0] * Hitbox_Minimum[0] + Bones[14][2][1] * Hitbox_Minimum[1] + Bones[14][2][2] * Hitbox_Minimum[2],

																		Bones[14][2][0] * Hitbox_Maximum[0] + Bones[14][2][1] * Hitbox_Minimum[1] + Bones[14][2][2] * Hitbox_Minimum[2],

																		Bones[14][2][0] * Hitbox_Minimum[0] + Bones[14][2][1] * Hitbox_Maximum[1] + Bones[14][2][2] * Hitbox_Minimum[2],

																		Bones[14][2][0] * Hitbox_Minimum[0] + Bones[14][2][1] * Hitbox_Minimum[1] + Bones[14][2][2] * Hitbox_Maximum[2],

																		Bones[14][2][0] * Hitbox_Maximum[0] + Bones[14][2][1] * Hitbox_Maximum[1] + Bones[14][2][2] * Hitbox_Minimum[2],

																		Bones[14][2][0] * Hitbox_Maximum[0] + Bones[14][2][1] * Hitbox_Minimum[1] + Bones[14][2][2] * Hitbox_Maximum[2],

																		Bones[14][2][0] * Hitbox_Minimum[0] + Bones[14][2][1] * Hitbox_Maximum[1] + Bones[14][2][2] * Hitbox_Maximum[2],

																		Bones[14][2][0] * Hitbox_Maximum[0] + Bones[14][2][1] * Hitbox_Maximum[1] + Bones[14][2][2] * Hitbox_Maximum[2]
																	};

																	float* Hitbox_Z_Extremes[2];

																	std::tie(Hitbox_Z_Extremes[0], Hitbox_Z_Extremes[1]) = std::minmax_element(Hitbox_Z_Vertices, &Hitbox_Z_Vertices[sizeof(Hitbox_Z_Vertices) / sizeof(Hitbox_Z_Vertices[0])]);

																	float Target_Origin[3] =
																	{
																		Bones[14][0][0] * Hitbox_Center[0] + Bones[14][0][1] * Hitbox_Center[1] + Bones[14][0][2] * Hitbox_Center[2] + Bones[14][0][3],

																		Bones[14][1][0] * Hitbox_Center[0] + Bones[14][1][1] * Hitbox_Center[1] + Bones[14][1][2] * Hitbox_Center[2] + Bones[14][1][3],

																		Hitbox_Z_Extremes[0][0] + (Hitbox_Z_Extremes[1][0] - Hitbox_Z_Extremes[0][0]) * Interface_Aim_Height.Floating_Point + Bones[14][2][3]
																	};

																	float Direction[3] =
																	{
																		Target_Origin[0] - Eye_Position[0],

																		Target_Origin[1] - Eye_Position[1],

																		Target_Origin[2] - Eye_Position[2]
																	};

																	if (Trace_Ray(Direction) == 1)
																	{
																		Command->Tick_Number = Target->Tick_Number;

																		Command->Angles[0] = __builtin_atan2f(-Direction[2], __builtin_hypotf(Direction[0], Direction[1])) * 180 / 3.1415927f;

																		Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180 / 3.1415927f;

																		Command->Buttons |= 1;

																		if (Interface_Bruteforce.Integer == 1)
																		{
																			__int32 Target_Number = *(__int32*)((unsigned __int32)Target->Self + 84);

																			Player_Data_Structure* Player_Data = &Players_Data[Target_Number];

																			if (Player_Data->Priority != -2)
																			{
																				Recent_Player_Data_Number = Target_Number;

																				Byte_Manager::Copy_Bytes(0, &Previous_Recent_Player_Data, sizeof(Previous_Recent_Player_Data), Player_Data);

																				if (Player_Data->Memory_Tolerance == 0)
																				{
																					if (Player_Data->Tolerance == 0)
																					{
																						Player_Data->Shots_Fired = (Player_Data->Shots_Fired + 1) % Bruteforce_Angles_Count;

																						if (Player_Data->Shots_Fired == 0)
																						{
																							Player_Data->Switch_X ^= 1;
																						}

																						Player_Data->Tolerance = Interface_Bruteforce_Tolerance.Integer;
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
														float Rotations[2][3][3];

														unsigned __int8 Calculation_Number = 0;

														float Forward[3];

														float Right[3];

														float Up[3];

														Angle_Vectors(Command->Angles, Forward, Right, Up);

														Command->Command_Number = -242;

														Command->Random_Seed = 165;

														using Random_Seed_Type = void(__cdecl*)(__int32 Seed);

														static void* Random_Seed = (void*)((unsigned __int32)GetModuleHandleW(L"vstdlib.dll") + 47040);

														Random_Seed_Type((unsigned __int32)Random_Seed)((Command->Random_Seed & 255) + 1);

														using Random_Float_Type = float(__cdecl*)(float Minimum, float Maximum);

														static void* Random_Float = (void*)((unsigned __int32)GetModuleHandleW(L"vstdlib.dll") + 46880);

														using Update_Accuracy_Penalty_Type = void(__thiscall**)(void* Weapon);

														(*Update_Accuracy_Penalty_Type(*(unsigned __int32*)Weapon + 1512))(Weapon);

														using Get_Inaccuracy_Type = float(__thiscall**)(void* Weapon);

														using Get_Spread_Type = float(__thiscall**)(void* Weapon);

														float Random[4] =
														{
															Random_Float_Type(Random_Float)(0, 6.283185f),

															Random_Float_Type(Random_Float)(0, (*Get_Inaccuracy_Type(*(unsigned __int32*)Weapon + 1504))(Weapon)),

															Random_Float_Type(Random_Float)(0, 6.283185f),

															Random_Float_Type(Random_Float)(0, (*Get_Spread_Type(*(unsigned __int32*)Weapon + 1508))(Weapon))
														};

														float Spread[2] =
														{
															__builtin_cosf(Random[0]) * Random[1] + __builtin_cosf(Random[2]) * Random[3],

															__builtin_sinf(Random[0]) * Random[1] + __builtin_sinf(Random[2]) * Random[3]
														};

														float Directions[2][3] =
														{
															{
																Forward[0],

																Forward[1],

																Forward[2]
															},

															{
																Forward[0] + Spread[0] * Right[0] + Spread[1] * Up[0],

																Forward[1] + Spread[0] * Right[1] + Spread[1] * Up[1],

																Forward[2] + Spread[0] * Right[2] + Spread[1] * Up[2]
															}
														};

														Calculate_Rotation_Label:
														{
															Rotations[Calculation_Number][0][0] = Directions[Calculation_Number][0];

															Rotations[Calculation_Number][0][1] = Directions[Calculation_Number][1];

															Rotations[Calculation_Number][0][2] = Directions[Calculation_Number][2];

															Vector_Normalize(Rotations[Calculation_Number][0]);

															Rotations[Calculation_Number][1][0] = Directions[Calculation_Number][1] - Directions[Calculation_Number][2];

															Rotations[Calculation_Number][1][1] = Directions[Calculation_Number][2] - Directions[Calculation_Number][0];

															Rotations[Calculation_Number][1][2] = Directions[Calculation_Number][0] - Directions[Calculation_Number][1];

															Vector_Normalize(Rotations[Calculation_Number][1]);

															Rotations[Calculation_Number][2][0] = Directions[Calculation_Number][1] * Rotations[Calculation_Number][1][2] - Directions[Calculation_Number][2] * Rotations[Calculation_Number][1][1];

															Rotations[Calculation_Number][2][1] = Directions[Calculation_Number][2] * Rotations[Calculation_Number][1][0] - Directions[Calculation_Number][0] * Rotations[Calculation_Number][1][2];

															Rotations[Calculation_Number][2][2] = Directions[Calculation_Number][0] * Rotations[Calculation_Number][1][1] - Directions[Calculation_Number][1] * Rotations[Calculation_Number][1][0];

															Vector_Normalize(Rotations[Calculation_Number][2]);

															if (Calculation_Number != 1)
															{
																Calculation_Number = 1;

																goto Calculate_Rotation_Label;
															}
														}

														float Rotation[3][3] =
														{
															{
																Rotations[0][0][0] * Rotations[1][0][0] + Rotations[0][1][0] * Rotations[1][1][0] + Rotations[0][2][0] * Rotations[1][2][0],

																Rotations[0][0][0] * Rotations[1][0][1] + Rotations[0][1][0] * Rotations[1][1][1] + Rotations[0][2][0] * Rotations[1][2][1],

																Rotations[0][0][0] * Rotations[1][0][2] + Rotations[0][1][0] * Rotations[1][1][2] + Rotations[0][2][0] * Rotations[1][2][2]
															},

															{
																Rotations[0][0][1] * Rotations[1][0][0] + Rotations[0][1][1] * Rotations[1][1][0] + Rotations[0][2][1] * Rotations[1][2][0],

																Rotations[0][0][1] * Rotations[1][0][1] + Rotations[0][1][1] * Rotations[1][1][1] + Rotations[0][2][1] * Rotations[1][2][1],

																Rotations[0][0][1] * Rotations[1][0][2] + Rotations[0][1][1] * Rotations[1][1][2] + Rotations[0][2][1] * Rotations[1][2][2]
															},

															{
																Rotations[0][0][2] * Rotations[1][0][0] + Rotations[0][1][2] * Rotations[1][1][0] + Rotations[0][2][2] * Rotations[1][2][0],

																Rotations[0][0][2] * Rotations[1][0][1] + Rotations[0][1][2] * Rotations[1][1][1] + Rotations[0][2][2] * Rotations[1][2][1],

																Rotations[0][0][2] * Rotations[1][0][2] + Rotations[0][1][2] * Rotations[1][1][2] + Rotations[0][2][2] * Rotations[1][2][2]
															}
														};

														float Rotated_Forward[3] =
														{
															Forward[0] * Rotation[0][0] + Forward[1] * Rotation[0][1] + Forward[2] * Rotation[0][2],

															Forward[0] * Rotation[1][0] + Forward[1] * Rotation[1][1] + Forward[2] * Rotation[1][2],

															Forward[0] * Rotation[2][0] + Forward[1] * Rotation[2][1] + Forward[2] * Rotation[2][2]
														};

														float* Recoil = (float*)((unsigned __int32)Local_Player + 3656);

														Command->Angles[0] = 180 - __builtin_atan2f(-Rotated_Forward[2], __builtin_hypotf(Rotated_Forward[0], Rotated_Forward[1])) * 180 / 3.1415927f - Recoil[0] * 2;

														Command->Angles[1] = 180 + __builtin_atan2f(Rotated_Forward[1], Rotated_Forward[0]) * 180 / 3.1415927f - Recoil[1] * 2;

														float Rotated_Up[3] =
														{
															Up[0] * Rotation[0][0] + Up[1] * Rotation[0][1] + Up[2] * Rotation[0][2],

															Up[0] * Rotation[1][0] + Up[1] * Rotation[1][1] + Up[2] * Rotation[1][2],

															Up[0] * Rotation[2][0] + Up[1] * Rotation[2][1] + Up[2] * Rotation[2][2]
														};

														Command->Angles[2] = 180 + __builtin_atan2f(Rotated_Forward[1] * Rotated_Up[0] - Rotated_Forward[0] * Rotated_Up[1], Rotated_Forward[0] * (Rotated_Forward[0] * Rotated_Up[2] - Rotated_Forward[2] * Rotated_Up[0]) - Rotated_Forward[1] * (Rotated_Forward[2] * Rotated_Up[1] - Rotated_Forward[1] * Rotated_Up[2])) * 180 / 3.1415927f - Recoil[2] * 2;

														In_Attack = 1;

														Send_Packet = (Interface_Alternative.Integer != 0) * 2;

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

					Byte_Manager::Copy_Bytes(0, &Players_Data[Recent_Player_Data_Number], sizeof(Previous_Recent_Player_Data), &Previous_Recent_Player_Data);

					goto Passed_Shot_Time_Check_Label;
				}
			}
		}

		Command->Buttons &= ~2048;

		if (In_Attack == 0)
		{
			Command->Buttons &= ~1;

			if (Sorted_Target_List.size() != 0)
			{
				Command->Angles[0] = Interface_Angle_X.Floating_Point;

				float* Target_Origin = (float*)((unsigned __int32)Sorted_Target_List.at(0).Self + 824);

				float Direction[2] =
				{
					Target_Origin[0] - Local_Player_Origin[0],

					Target_Origin[1] - Local_Player_Origin[1]
				};

				if (Send_Packet == 0)
				{
					if ((Command->Command_Number % 2) == 0)
					{
						Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180 / 3.1415927f + Interface_First_Choked_Angle_Y.Floating_Point;
					}
					else
					{
						Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180 / 3.1415927f + Interface_Second_Choked_Angle_Y.Floating_Point;
					}
				}
				else
				{
					Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180 / 3.1415927f + Interface_Angle_Y.Floating_Point;
				}
			}
		}

		Correct_Movement();

		if (Send_Packet == 0)
		{
			using Send_Datagram_Type = __int32(__thiscall*)(void* Network_Channel, void* Unknown_Parameter);

			__int32 Sequence_Number = *(__int32*)((unsigned __int32)Network_Channel + 8) = Send_Datagram_Type((unsigned __int32)Engine_Module + 1880960)(Network_Channel, nullptr);

			Sequences[Sequence_Number % 90] =
			{
				Sequence_Number,

				Sequence_Number - Choked_Commands_Count - 1
			};
		}
		else
		{
			Command->Extra_Simulations = max(0, Choked_Commands_Count - 14);

			Byte_Manager::Copy_Bytes(0, Update_Animation_Angles, sizeof(Update_Animation_Angles), Command->Angles);
		}

		*(__int8*)((unsigned __int32)__builtin_frame_address(0) + 211) = Send_Packet;
	}

	(decltype(&Redirected_Copy_Command)(Original_Copy_Command_Caller))(Unknown_Parameter, Command);
}