struct Command_Structure
{
	__int8 Additional_Bytes_1[8];

	__int32 Command_Number;

	__int32 Tick_Number;

	float Angles[3];

	float Move[3];

	__int32 Buttons;

	__int8 Additional_Bytes_2[1];

	__int32 Select;

	__int8 Additional_Bytes_3[4];

	__int32 Random_Seed;
};

Player_Data_Structure Previous_Recent_Player_Data;

Redirection_Manager::Manager_Structure Copy_Command_Manager;

void Copy_Command(void* Unknown_Parameter, Command_Structure* Command, void* Stack)
{
	void* Local_Player = *(void**)((unsigned __int64)Client_Module + 6245224);

	if (*(__int8*)((unsigned __int64)Local_Player + 207) == 0)
	{
		__int8 Move_Type = *(__int8*)((unsigned __int64)Local_Player + 500);

		auto Angle_Vectors = [](float* Angles, float* Forward, float* Right, float* Up) -> void
		{
			using Angle_Vectors_Type = void(*)(float* Angles, float* Forward, float* Right, float* Up);

			Angle_Vectors_Type((unsigned __int64)Client_Module + 2812512)(Angles, Forward, Right, Up);
		};

		__int32 Jump_State = (Command->Buttons & 2) + Move_Type;

		float Move_Angles[3] =
		{
			Command->Angles[0],

			Command->Angles[1]
		};

		static float Previous_Move_Angle_Y;

		float* Velocity = (float*)((unsigned __int64)Local_Player + 328);

		if (Jump_State == 4)
		{
			Command->Move[0] = 0.f;

			if (*(__int32*)((unsigned __int64)Local_Player + 764) == -1)
			{
				Command->Buttons &= ~2;
			}
			else
			{
				Command->Buttons &= ~(*(__int32*)((unsigned __int64)Local_Player + 5556) & 2);
			}

			float Difference = __builtin_remainderf(Move_Angles[1] - Previous_Move_Angle_Y, 360.f);

			Previous_Move_Angle_Y = Move_Angles[1];

			if (__builtin_fabsf(Difference) < __builtin_atan2f(30.f, __builtin_hypotf(Velocity[0], Velocity[1])) * 180.f / 3.1415927f)
			{
				float Strafe_Angle = __builtin_remainderf(Move_Angles[1] - __builtin_atan2f(Velocity[1], Velocity[0]) * 180.f / 3.1415927f, 360.f);

				if (__builtin_signbitf(Strafe_Angle) == 0)
				{
					Command->Move[1] = -400.f;
				}
				else
				{
					Command->Move[1] = 400.f;
				}

				Move_Angles[1] -= Strafe_Angle;
			}
			else
			{
				if (__builtin_signbitf(Difference) == 0)
				{
					Command->Move[1] = -400.f;
				}
				else
				{
					Command->Move[1] = 400.f;
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
			using Vector_Normalize_Type = float(*)(float* Vector);

			return Vector_Normalize_Type((unsigned __int64)Client_Module + 2810192)(Vector);
		};

		auto Get_Ladder_Move = [&](float* Move, float* Forward, float Forward_Move, float* Right, float Side_Move) -> void
		{
			Move[0] = Forward[0] * Forward_Move + Right[0] * Side_Move;

			Move[1] = Forward[1] * Forward_Move + Right[1] * Side_Move;

			float* Ladder_Normal = (float*)((unsigned __int64)Local_Player + 5776);

			float Normal_Move = Move[0] * Ladder_Normal[0] + Move[1] * Ladder_Normal[1];

			Move[0] -= Ladder_Normal[0] * Normal_Move;

			Move[1] -= Ladder_Normal[1] * Normal_Move;

			float Cross[3] =
			{
				-Ladder_Normal[1],

				Ladder_Normal[0]
			};

			Vector_Normalize(Cross);

			Move[2] = (Forward[2] * Forward_Move + Right[2] * Side_Move) - (Ladder_Normal[0] * Cross[1] - Ladder_Normal[1] * Cross[0]) * Normal_Move;
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
			Get_Ladder_Move(Desired_Move, Desired_Move_Forward, std::clamp(Command->Move[0], -1.f, 1.f), Desired_Move_Right, std::clamp(Command->Move[1], -1.f, 1.f));
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

				Command->Move[0] = std::clamp((Desired_Move[0] * Move_Right[1] - Move_Right[0] * Desired_Move[1]) / Divider, -1000.f, 1000.f);

				Command->Move[1] = std::clamp((Move_Forward[0] * Desired_Move[1] - Desired_Move[0] * Move_Forward[1]) / Divider, -1000.f, 1000.f);
			}
			else
			{
				static float Solutions[9][2] =
				{
					{ -1.f },

					{ 0.f, -1.f },

					{ },

					{ 1.f },

					{ 0.f, 1.f },

					{ -1.f, -1.f },

					{ -1.f, 1.f },

					{ 1.f, -1.f },

					{ 1.f, 1.f }
				};

				__int8 Solution_Number = 0;

				float Least_Deviation = __builtin_inff();

				__int8 Solution;

				Traverse_Solutions_Label:
				{
					float Move[3];

					Get_Ladder_Move(Move, Move_Forward, Solutions[Solution_Number][0], Move_Right, Solutions[Solution_Number][1]);

					float Deviation = __builtin_powf(Move[0] - Desired_Move[0], 2.f) + __builtin_powf(Move[1] - Desired_Move[1], 2.f) + __builtin_powf(Move[2] - Desired_Move[2], 2.f);

					if (Deviation < Least_Deviation)
					{
						Least_Deviation = Deviation;

						Solution = Solution_Number;
					}

					Solution_Number += 1;

					if (Solution_Number != sizeof(Solutions) / sizeof(Solutions[0]))
					{
						goto Traverse_Solutions_Label;
					}
				}

				Command->Move[0] = Solutions[Solution][0];

				Command->Move[1] = Solutions[Solution][1];
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

		void* Previous_Audio_Device = *(void**)((unsigned __int64)Engine_Module + 5141912);

		*(void**)((unsigned __int64)Engine_Module + 5141912) = nullptr;

		float Local_Previous_Origin[2];

		float* Local_Origin = (float*)((unsigned __int64)Local_Player + 1064);

		Byte_Manager::Copy_Bytes(1, Local_Previous_Origin, sizeof(Local_Previous_Origin), Local_Origin);

		auto Predict = [&](__int8 Duck) -> void
		{
			Command->Buttons |= 4 * Duck;

			using Set_Host_Type = void(*)(void* Move_Helper, void* Player);

			Set_Host_Type((unsigned __int64)Client_Module + 1439184)((void*)((unsigned __int64)Client_Module + 5984240), Local_Player);

			using Run_Command_Type = void(*)(void* Prediction, void* Player, Command_Structure* Command, void* Move_Helper);

			Run_Command_Type((unsigned __int64)Client_Module + 1602624)((void*)((unsigned __int64)Client_Module + 6889744), Local_Player, Command, (void*)((unsigned __int64)Client_Module + 5984240));

			Set_Host_Type((unsigned __int64)Client_Module + 1439184)((void*)((unsigned __int64)Client_Module + 5984240), nullptr);
		};

		if (Jump_State * (Interface_Duck_Advantage.Floating_Point != 0.f) == 4)
		{
			Predict(0);

			auto Restore = [&]() -> float
			{
				Command->Buttons &= ~4;

				float Speed = __builtin_hypotf(Velocity[0], Velocity[1]);

				using Run_Prediction_Type = void(*)();

				Run_Prediction_Type((unsigned __int64)Engine_Module + 599696)();

				return Speed;
			};

			if (*(float*)((unsigned __int64)Local_Player + 324) == 64.f)
			{
				float Normal_Speed = Restore();

				Predict(1);

				float Duck_Speed = Restore();

				Command->Buttons |= 4 * (Normal_Speed < Duck_Speed - Interface_Duck_Advantage.Floating_Point);
			}
			else
			{
				Restore();

				Command->Buttons |= 4;
			}
		}

		Predict(0);

		*(void**)((unsigned __int64)Engine_Module + 5141912) = Previous_Audio_Device;

		Byte_Manager::Copy_Bytes(1, Command->Move, sizeof(Previous_Move), Previous_Move);

		static __int8 Send_Packet;

		__int32 Choked_Commands = *(__int32*)((unsigned __int64)Engine_Module + 5497992);

		__int8 Predicted_Send_Packet = 0;

		static float Local_Networked_Origin[2];

		if (Interface_Alternative.Integer == 0)
		{
			__int32 Predicted_Choked_Commands = Choked_Commands + 1;

			if (Choked_Commands < Interface_Minimum_Choked_Commands.Integer)
			{
				Send_Packet = 0;

				if (Predicted_Choked_Commands == Interface_Minimum_Choked_Commands.Integer)
				{
					Predicted_Send_Packet = 1;

					if (Predicted_Choked_Commands < Interface_Maximum_Choked_Commands.Integer)
					{
						Predicted_Send_Packet = __builtin_hypotf(Local_Networked_Origin[0] - Local_Origin[0], Local_Networked_Origin[1] - Local_Origin[1]) > 64.f;
					}
				}
			}
			else
			{
				if (Choked_Commands >= Interface_Maximum_Choked_Commands.Integer)
				{
					goto Send_Packet_Label;
				}

				Send_Packet = __builtin_hypotf(Local_Networked_Origin[0] - Local_Previous_Origin[0], Local_Networked_Origin[1] - Local_Previous_Origin[1]) > 64.f;

				if (Send_Packet == 0)
				{
					Predicted_Send_Packet = __builtin_hypotf(Local_Networked_Origin[0] - Local_Origin[0], Local_Networked_Origin[1] - Local_Origin[1]) > 64.f;

					if (Predicted_Choked_Commands == Interface_Maximum_Choked_Commands.Integer)
					{
						Predicted_Send_Packet = 1;
					}
				}
				else
				{
					Send_Packet_Label:
					{
						Byte_Manager::Copy_Bytes(1, Local_Networked_Origin, sizeof(Local_Networked_Origin), Local_Origin);

						Send_Packet = 1;
					}
				}
			}
		}
		else
		{
			if (Send_Packet == 2)
			{
				goto Send_Packet_Label;
			}

			if (Choked_Commands >= Interface_Minimum_Choked_Commands.Integer)
			{
				if (Choked_Commands >= Interface_Maximum_Choked_Commands.Integer)
				{
					goto Send_Packet_Label;
				}

				if (__builtin_hypotf(Local_Networked_Origin[0] - Local_Origin[0], Local_Networked_Origin[1] - Local_Origin[1]) > 64.f)
				{
					goto Send_Packet_Label;
				}
			}

			Send_Packet = 0;
		}

		__int32 Entity_Number = 1;

		using Get_Latency_Type = float(*)(void* Network_Channel, __int32 Type);

		void* Network_Channel = *(void**)((unsigned __int64)Engine_Module + 5462064);

		float Latency = Get_Latency_Type((unsigned __int64)Engine_Module + 1895920)(Network_Channel, 0);

		using Get_Interpolation_Time_Type = float(*)();

		float Interpolation_Time = Get_Interpolation_Time_Type((unsigned __int64)Engine_Module + 666592)();

		float Corrected_Latency = std::clamp(Latency + Interpolation_Time, 0.f, 1.f);

		Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)((unsigned __int64)Client_Module + 5956224);

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
				void* Entity = *(void**)((unsigned __int64)Client_Module + 6592712 + ((Entity_Number - 8193) << 5));

				if (Entity != nullptr)
				{
					if (*(__int8*)((unsigned __int64)Entity + 207) == 0)
					{
						if (*(__int32*)((unsigned __int64)Entity + 216) != *(__int32*)((unsigned __int64)Local_Player + 216))
						{
							if (*(__int8*)((unsigned __int64)Entity + 506) == 0)
							{
								float Entity_Time = *(float*)((unsigned __int64)Entity + 168);

								float* Entity_Origin = (float*)((unsigned __int64)Entity + 1928);

								Target_Structure Target =
								{
									Player_Data->Priority == -2 ? 0 : Player_Data->Priority,

									Entity,

									(__int32)((Entity_Time + Interpolation_Time) / Global_Variables->Interval_Per_Tick + 0.5f),

									__builtin_fabsf(Corrected_Latency - (__int32)(Global_Variables->Tick_Number + (Interface_Alternative.Integer ^ 1) + (Latency - Entity_Time) / Global_Variables->Interval_Per_Tick + 0.5f) * Global_Variables->Interval_Per_Tick) <= 0.2f,

									__builtin_powf(Local_Origin[0] - Entity_Origin[0], 2.f) + __builtin_powf(Local_Origin[1] - Entity_Origin[1], 2.f) + __builtin_powf(Local_Origin[2] - Entity_Origin[2], 2.f)
								};

								if (Interface_Target_On_Simulation.Integer != 0)
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

		auto Target_List_Sort = [](Target_Structure& X, Target_Structure& Y) -> __int8
		{
			if (X.Priority == Y.Priority)
			{
				return X.Distance < Y.Distance;
			}

			return X.Priority > Y.Priority;
		};

		std::sort(Sorted_Target_List.begin(), Sorted_Target_List.end(), Target_List_Sort);

		__int8 In_Attack = 0;

		if (Command->Select == 0)
		{
			if (__builtin_fabsf(Global_Variables->Time - Shot_Time) > 0.5f)
			{
				if (Shot_Time == 0.f)
				{
					Passed_Shot_Time_Check_Label:
					{
						if ((Command->Buttons & 2048) == 0)
						{
							__int8 Send_Packet_Sequence = (Send_Packet == 0) + (Predicted_Send_Packet == 1);

							if (Interface_Alternative.Integer == 1)
							{
								Send_Packet_Sequence = 2;
							}

							if (Send_Packet_Sequence == 2)
							{
								if (*(float*)((unsigned __int64)Local_Player + 4184) <= Global_Variables->Time)
								{
									using Get_Weapon_Type = void*(*)(void* Entity);

									void* Weapon = Get_Weapon_Type((unsigned __int64)Client_Module + 305296)(Local_Player);

									if (Weapon != nullptr)
									{
										if (*(__int32*)((unsigned __int64)Weapon + 3112) != -1)
										{
											if (*(__int32*)((unsigned __int64)Weapon + 3120) > 0)
											{
												if (*(float*)((unsigned __int64)Weapon + 3048) <= Global_Variables->Time)
												{
													size_t Target_Number = 0;

													using Get_Eye_Position_Type = void(*)(void* Entity, float* Eye_Position);

													float Eye_Position[3];

													Get_Eye_Position_Type((unsigned __int64)Client_Module + 327360)(Local_Player, Eye_Position);

													using Get_Weapon_Information_Type = void*(*)(void* Weapon);

													float Weapon_Range = *(float*)((unsigned __int64)Get_Weapon_Information_Type((unsigned __int64)Client_Module + 317184)(Weapon) + 2236);

													Recent_Player_Data_Number = 0;

													Traverse_Sorted_Target_List_Label:
													{
														if (Target_Number != Sorted_Target_List.size())
														{
															Target_Structure* Target = &Sorted_Target_List.at(Target_Number);

															if (Target->Valid == 1)
															{
																Redirected_Compute_Torso_Rotation((void*)(*(unsigned __int64*)((unsigned __int64)Target->Self + 6648) - 192));

																using Setup_Bones_Type = __int8(*)(void* Entity, void* Bones, __int32 Maximum_Bones, __int32 Mask, float Time);

																float Bones[128][3][4];

																if (Setup_Bones_Type((unsigned __int64)Client_Module + 504992)((void*)((unsigned __int64)Target->Self + 8), Bones, sizeof(Bones) / sizeof(Bones[0]), 524032, Global_Variables->Time) == 1)
																{
																	auto Perform_Trace = [&](float* Direction) -> __int8
																	{
																		struct alignas(16) Ray_Structure
																		{
																			__int8 Ray[65];

																			void Initialize(float* Start, float* End)
																			{
																				Byte_Manager::Set_Bytes(1, Ray, sizeof(Ray), 0);

																				Byte_Manager::Copy_Bytes(1, (float*)Ray, sizeof(float[3]), Start);

																				float Delta[3] =
																				{
																					End[0] - Start[0],

																					End[1] - Start[1],

																					End[2] - Start[2]
																				};

																				Byte_Manager::Copy_Bytes(1, (float*)((unsigned __int64)Ray + 16), sizeof(Delta), Delta);

																				*(__int8*)((unsigned __int64)Ray + 64) = 1;

																				*(__int8*)((unsigned __int64)Ray + 65) = __builtin_powf(Delta[0], 2.f) + __builtin_powf(Delta[1], 2.f) + __builtin_powf(Delta[2], 2.f) != 0.f;
																			}
																		};

																		struct Filter_Structure
																		{
																			void* Table;

																			void* Skip;

																			__int8 Additional_Bytes[16];
																		};

																		struct Trace_Structure
																		{
																			__int8 Additional_Bytes_1[80];

																			__int32 Group;

																			__int8 Additional_Bytes_2[4];

																			void* Entity;

																			__int8 Additional_Bytes_3[4];
																		};

																		using Perform_Trace_Type = void(*)(void* Tracer, Ray_Structure* Ray, __int32 Mask, Filter_Structure* Filter, Trace_Structure* Trace);

																		Ray_Structure Ray;

																		Vector_Normalize(Direction);

																		float End[3]
																		{
																			Eye_Position[0] + Direction[0] * Weapon_Range,

																			Eye_Position[1] + Direction[1] * Weapon_Range,

																			Eye_Position[2] + Direction[2] * Weapon_Range
																		};

																		Ray.Initialize(Eye_Position, End);

																		Filter_Structure Filter = { (void*)((unsigned __int64)Client_Module + 4589368), Local_Player };

																		Trace_Structure Trace;

																		Perform_Trace_Type((unsigned __int64)Engine_Module + 1632208)((void*)((unsigned __int64)Engine_Module + 4691696), &Ray, 1174421515, &Filter, &Trace);

																		using Clip_Trace_Type = void(*)(float* Start, float* End, __int32 Mask, Filter_Structure* Filter, Trace_Structure* Trace);

																		End[0] += Direction[0] * 40.f;

																		End[1] += Direction[1] * 40.f;

																		End[2] += Direction[2] * 40.f;

																		Clip_Trace_Type((unsigned __int64)Client_Module + 1756976)(Eye_Position, End, 1174421515, &Filter, &Trace);

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

																	using Get_Studio_Header_Type = void*(*)(void* Entity);

																	void* Studio_Header = *(void**)Get_Studio_Header_Type((unsigned __int64)Client_Module + 479648)(Target->Self);

																	void* Hitbox_Set = (void*)((unsigned __int64)Studio_Header + *(__int32*)((unsigned __int64)Studio_Header + 176));

																	float* Hitbox_Minimum = (float*)((unsigned __int64)Hitbox_Set + 836);

																	float* Hitbox_Maximum = (float*)((unsigned __int64)Hitbox_Set + 848);

																	float Hitbox_Center[3]
																	{
																		(Hitbox_Minimum[0] + Hitbox_Maximum[0]) / 2.f,

																		(Hitbox_Minimum[1] + Hitbox_Maximum[1]) / 2.f,

																		(Hitbox_Minimum[2] + Hitbox_Maximum[2]) / 2.f
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

																		*Hitbox_Z_Extremes[0] + (*Hitbox_Z_Extremes[1] - *Hitbox_Z_Extremes[0]) * Interface_Aim_Height.Floating_Point + Bones[14][2][3]
																	};

																	float Direction[3] =
																	{
																		Target_Origin[0] - Eye_Position[0],

																		Target_Origin[1] - Eye_Position[1],

																		Target_Origin[2] - Eye_Position[2]
																	};

																	if (Perform_Trace(Direction) == 1)
																	{
																		Command->Tick_Number = Target->Tick_Number;

																		Command->Angles[0] = __builtin_atan2f(-Direction[2], __builtin_hypotf(Direction[0], Direction[1])) * 180.f / 3.1415927f;

																		Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180.f / 3.1415927f;

																		Command->Buttons |= 1;

																		if (Interface_Bruteforce.Integer == 1)
																		{
																			__int32 Target_Number = *(__int32*)((unsigned __int64)Target->Self + 136);

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

																						Player_Data->Switch_X ^= Player_Data->Shots_Fired == 0;

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

														__int8 Calculation_Number = 0;

														float Forward[3];

														float Right[3];

														float Up[3];

														Angle_Vectors(Command->Angles, Forward, Right, Up);

														Command->Command_Number = -242;

														Command->Random_Seed = 165;

														using Random_Seed_Type = void(*)(__int32 Seed);

														static void* Standard_Library_Module = GetModuleHandleW(L"vstdlib.dll");

														Random_Seed_Type((unsigned __int64)Standard_Library_Module + 64640)((Command->Random_Seed & 255) + 1);

														using Random_Type = float(*)(float Minimum, float Maximum);

														using Update_Accuracy_Penalty_Type = void(**)(void* Weapon);

														(*Update_Accuracy_Penalty_Type(*(unsigned __int64*)Weapon + 3072))(Weapon);

														using Get_Inaccuracy_Type = float(**)(void* Weapon);

														using Get_Spread_Type = float(**)(void* Weapon);

														float Random[4] =
														{
															Random_Type((unsigned __int64)Standard_Library_Module + 64512)(0.f, 6.283185f),

															Random_Type((unsigned __int64)Standard_Library_Module + 64512)(0.f, (*Get_Inaccuracy_Type(*(unsigned __int64*)Weapon + 3056))(Weapon)),

															Random_Type((unsigned __int64)Standard_Library_Module + 64512)(0.f, 6.283185f),

															Random_Type((unsigned __int64)Standard_Library_Module + 64512)(0.f, (*Get_Spread_Type(*(unsigned __int64*)Weapon + 3064))(Weapon))
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

														float* Recoil = (float*)((unsigned __int64)Local_Player + 4732);

														Command->Angles[0] = 180.f - __builtin_atan2f(-Rotated_Forward[2], __builtin_hypotf(Rotated_Forward[0], Rotated_Forward[1])) * 180.f / 3.1415927f - Recoil[0] * 2.f;

														Command->Angles[1] = 180.f + __builtin_atan2f(Rotated_Forward[1], Rotated_Forward[0]) * 180.f / 3.1415927f - Recoil[1] * 2.f;

														float Rotated_Up[3] =
														{
															Up[0] * Rotation[0][0] + Up[1] * Rotation[0][1] + Up[2] * Rotation[0][2],

															Up[0] * Rotation[1][0] + Up[1] * Rotation[1][1] + Up[2] * Rotation[1][2],

															Up[0] * Rotation[2][0] + Up[1] * Rotation[2][1] + Up[2] * Rotation[2][2]
														};

														Command->Angles[2] = 180.f + __builtin_atan2f(Rotated_Forward[1] * Rotated_Up[0] - Rotated_Forward[0] * Rotated_Up[1], Rotated_Forward[0] * (Rotated_Forward[0] * Rotated_Up[2] - Rotated_Forward[2] * Rotated_Up[0]) - Rotated_Forward[1] * (Rotated_Forward[2] * Rotated_Up[1] - Rotated_Forward[1] * Rotated_Up[2])) * 180.f / 3.1415927f - Recoil[2] * 2.f;

														In_Attack = 1;

														Send_Packet = Interface_Alternative.Integer * 2;

														Shot_Time = Global_Variables->Time;
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
					Shot_Time = 0.f;

					if (Recent_Player_Data_Number == 0)
					{
						goto Passed_Shot_Time_Check_Label;
					}

					Player_Data_Structure* Player_Data = &Players_Data[Recent_Player_Data_Number];

					Previous_Recent_Player_Data.Priority = Player_Data->Priority;

					Previous_Recent_Player_Data.Simulated = Player_Data->Simulated;

					Byte_Manager::Copy_Bytes(1, Player_Data, sizeof(Previous_Recent_Player_Data), &Previous_Recent_Player_Data);

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

				float* Target_Origin = (float*)((unsigned __int64)Sorted_Target_List.at(0).Self + 1064);

				float Direction[2] =
				{
					Target_Origin[0] - Local_Origin[0],

					Target_Origin[1] - Local_Origin[1]
				};

				if (Send_Packet == 0)
				{
					if ((Command->Command_Number % 2) == 0)
					{
						Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180.f / 3.1415927f + Interface_First_Choked_Angle_Y.Floating_Point;
					}
					else
					{
						Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180.f / 3.1415927f + Interface_Second_Choked_Angle_Y.Floating_Point;
					}
				}
				else
				{
					Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180.f / 3.1415927f + Interface_Angle_Y.Floating_Point;
				}
			}
		}

		Correct_Movement();

		if (Send_Packet == 0)
		{
			__int32 Sequence_Number = *(__int32*)((unsigned __int64)Network_Channel + 12) = Redirected_Send_Datagram(Network_Channel, nullptr);

			Sequences[Sequence_Number % 90] = *(__int32*)((unsigned __int64)Engine_Module + 5497988);
		}
		else
		{
			Byte_Manager::Copy_Bytes(1, Update_Animation_Angles, sizeof(Update_Animation_Angles), Command->Angles);
		}

		*(__int8*)((unsigned __int64)Stack + 312) = Send_Packet;
	}

	Copy_Command_Manager.Special_Call(Unknown_Parameter, Command);
}

__attribute__((naked)) void Redirected_Copy_Command()
{
	asm("movq %rsp, %r8");
	asm("jmp %P0" : : "i"(Copy_Command));
}