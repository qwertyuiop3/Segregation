struct Command_Structure
{
	__int32 Command_Number;

	__int32 Tick_Number;

	float Angles[3];

	float Move[3];

	__int32 Buttons;

	__int8 Additional_Bytes_1[9];

	__int32 Random_Seed;

	__int8 Additional_Bytes_2[24];

	__int8 Typing;

	__int8 Additional_Bytes_3[247];
};

Redirection_Manager::Manager_Structure Copy_Command_Manager;

void Copy_Command(void* Unknown_Parameter, Command_Structure* Command, void* Stack)
{
	void* Local_Player = Get_Local_Player();

	if (*(__int8*)((unsigned __int64)Local_Player + 199) == 0)
	{
		__int8 Move_Type = *(__int8*)((unsigned __int64)Local_Player + 500);

		auto Angle_Vectors = [](float* Angles, float* Forward, float* Right, float* Up) -> void
		{
			using Angle_Vectors_Type = void(*)(float* Angles, float* Forward, float* Right, float* Up);

			static void* Angle_Vectors = Byte_Manager::Find_Bytes(16235455, (unsigned __int8*)Client_Module, 13604689161566428982ull);

			Angle_Vectors_Type((unsigned __int64)Angle_Vectors)(Angles, Forward, Right, Up);
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
				Command->Buttons &= ~(*(__int32*)((unsigned __int64)Local_Player + 11420) & 2);
			}

			if ((Command->Buttons & 262144) == 262144)
			{
				Command->Buttons |= 4;

				if (__builtin_signbitf(Velocity[2]) == 1)
				{
					Command->Buttons &= ~4;
				}
			}

			float Difference = __builtin_remainderf(Move_Angles[1] - Previous_Move_Angle_Y, 360.f);

			Previous_Move_Angle_Y = Move_Angles[1];

			if (__builtin_fabsf(Difference) < __builtin_atan2f(30.f, __builtin_hypotf(Velocity[0], Velocity[1])) * 180.f / 3.1415927f)
			{
				float Strafe_Angle = __builtin_remainderf(Move_Angles[1] - __builtin_atan2f(Velocity[1], Velocity[0]) * 180.f / 3.1415927f, 360.f);

				if (__builtin_signbitf(Strafe_Angle) == 0)
				{
					Command->Move[1] = -10000.f;
				}
				else
				{
					Command->Move[1] = 10000.f;
				}

				Move_Angles[1] -= Strafe_Angle;
			}
			else
			{
				if (__builtin_signbitf(Difference) == 0)
				{
					Command->Move[1] = -10000.f;
				}
				else
				{
					Command->Move[1] = 10000.f;
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

			static void* Vector_Normalize = Byte_Manager::Find_Bytes(495, (unsigned __int8*)Client_Module, 18020419034984324545ull);

			return Vector_Normalize_Type((unsigned __int64)Vector_Normalize)(Vector);
		};

		auto Get_Ladder_Move = [&](float* Move, float* Forward, float Forward_Move, float* Right, float Side_Move, float* Ladder_Normal) -> void
		{
			Move[0] = Forward[0] * Forward_Move + Right[0] * Side_Move;

			Move[1] = Forward[1] * Forward_Move + Right[1] * Side_Move;

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

		float* Ladder_Normal = (float*)((unsigned __int64)Local_Player + 11632);

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
			Get_Ladder_Move(Desired_Move, Desired_Move_Forward, std::clamp(Command->Move[0], -200.f, 200.f), Desired_Move_Right, std::clamp(Command->Move[1], -200.f, 200.f), Ladder_Normal);
		}

		auto Correct_Movement = [&](float* Angles, __int32 Move_Type, float* Move, float* Desired_Move, float* Ladder_Normal, __int32* Buttons) -> void
		{
			float Move_Forward[3];

			float Move_Right[3];

			if (Move_Type == 2)
			{
				Angle_Vectors(Angles, Move_Forward, Move_Right, nullptr);

				Move_Forward[2] = 0.f;

				Vector_Normalize(Move_Forward);

				Move_Right[2] = 0.f;

				Vector_Normalize(Move_Right);

				float Divider = Move_Forward[0] * Move_Right[1] - Move_Right[0] * Move_Forward[1];

				Move[0] = std::clamp((Desired_Move[0] * Move_Right[1] - Move_Right[0] * Desired_Move[1]) / Divider, -10000.f, 10000.f);

				Move[1] = std::clamp((Move_Forward[0] * Desired_Move[1] - Desired_Move[0] * Move_Forward[1]) / Divider, -10000.f, 10000.f);
			}
			else
			{
				static float Solutions[9][3] =
				{
					{ -200.f },

					{ 0.f, -200.f },

					{ },

					{ 200.f },

					{ 0.f, 200.f },

					{ -200.f, -200.f },

					{ -200.f, 200.f },

					{ 200.f, -200.f },

					{ 200.f, 200.f }
				};

				__int8 Solution_Number = 0;

				float Least_Deviation = __builtin_inff();

				__int8 Solution;

				Traverse_Solutions_Label:
				{
					float Rotation = 0.f;

					Rotate_Solution_Label:
					{
						float Move[3];

						Angles[2] = Rotation;

						Angle_Vectors(Angles, Move_Forward, Move_Right, nullptr);

						Get_Ladder_Move(Move, Move_Forward, Solutions[Solution_Number][0], Move_Right, Solutions[Solution_Number][1], Ladder_Normal);

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

				Move[0] = Solutions[Solution][0];

				Move[1] = Solutions[Solution][1];

				Angles[2] = Solutions[Solution][2];
			}

			*Buttons &= ~1560;

			if (__builtin_truncf(Move[0]) != 0.f)
			{
				*Buttons |= 8 * (__builtin_signbitf(Move[0]) + 1);
			}

			if (__builtin_truncf(Move[1]) != 0.f)
			{
				*Buttons |= 512 * ((__builtin_signbitf(Move[1]) ^ 1) + 1);
			}
		};

		Correct_Movement(Command->Angles, Move_Type, Command->Move, Desired_Move, Ladder_Normal, &Command->Buttons);

		Command->Typing = 1;

		Bullets_Fired = 0;

		__int32 Previous_Buttons = Command->Buttons;

		Command->Buttons |= 1;

		static void* Prediction = Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(136537483800711, (unsigned __int8*)Client_Module, 5560394368363882641), 3);

		*(__int16*)((unsigned __int64)Prediction + 12) = 1;

		auto Suppress_Events = [](__int8 State) -> void
		{
			static void* Prediction_System_Reference = Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(903, (unsigned __int8*)Client_Module, 16784221226330041059ull), 3);

			void* Prediction_System = *(void**)Prediction_System_Reference;

			Traverse_Events_Label:
			{
				*(__int8*)((unsigned __int64)Prediction_System + 16) = State;

				Prediction_System = *(void**)((unsigned __int64)Prediction_System + 8);

				if (Prediction_System != nullptr)
				{
					goto Traverse_Events_Label;
				}
			}
		};

		Suppress_Events(1);

		float Local_Previous_Origin[3];

		float* Local_Origin = (float*)((unsigned __int64)Local_Player + 1064);

		Byte_Manager::Copy_Bytes(1, Local_Previous_Origin, sizeof(Local_Previous_Origin), Local_Origin);

		static void* Move_Helper = Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(28807, (unsigned __int8*)Client_Module, 2332256697955850039), 3);

		if (Jump_State * ((Command->Buttons & 262144) == 0) * (Interface_Duck_Advantage.Get_Floating_Point() != 0.f) == 4)
		{
			Command->Buttons &= ~1;

			Redirected_Run_Command(Prediction, Local_Player, Command, Move_Helper);

			auto Restore = [&]() -> float
			{
				float Speed = __builtin_hypotf(Velocity[0], Velocity[1]);

				Run_Prediction();

				*(__int16*)((unsigned __int64)Prediction + 12) = 1;

				Suppress_Events(1);

				return Speed;
			};

			if (*(float*)((unsigned __int64)Local_Player + 324) == 64.f)
			{
				float Normal_Speed = Restore();

				Command->Buttons |= 4;

				Redirected_Run_Command(Prediction, Local_Player, Command, Move_Helper);

				Command->Buttons &= ~4;

				float Duck_Speed = Restore();

				Command->Buttons |= 4 * (Normal_Speed < Duck_Speed - Interface_Duck_Advantage.Get_Floating_Point());
			}
			else
			{
				Restore();

				Command->Buttons |= 4;
			}

			Command->Buttons |= 1;

			Previous_Buttons |= Command->Buttons & 4;
		}

		Redirected_Run_Command(Prediction, Local_Player, Command, Move_Helper);

		Suppress_Events(0);

		*(__int8*)((unsigned __int64)Prediction + 12) = 0;

		Command->Buttons = Previous_Buttons;

		Byte_Manager::Copy_Bytes(1, Command->Move, sizeof(Previous_Move), Previous_Move);

		static __int8 Send_Packet;

		__int32 Choked_Commands = Get_Choked_Commands();

		__int8 Predicted_Send_Packet = 0;

		static float Local_Networked_Origin[3];

		if (Interface_Alternative.Get_Integer() == 0)
		{
			__int32 Predicted_Choked_Commands = Choked_Commands + 1;

			if (Choked_Commands < Interface_Minimum_Choked_Commands.Get_Integer())
			{
				Send_Packet = 0;

				if (Predicted_Choked_Commands == Interface_Minimum_Choked_Commands.Get_Integer())
				{
					Predicted_Send_Packet = 1;

					if (Predicted_Choked_Commands < Interface_Maximum_Choked_Commands.Get_Integer())
					{
						Predicted_Send_Packet = __builtin_powf(Local_Networked_Origin[0] - Local_Origin[0], 2.f) + __builtin_powf(Local_Networked_Origin[1] - Local_Origin[1], 2.f) + __builtin_powf(Local_Networked_Origin[2] - Local_Origin[2], 2.f) > 4096.f;
					}
				}
			}
			else
			{
				if (Choked_Commands >= Interface_Maximum_Choked_Commands.Get_Integer())
				{
					goto Send_Packet_Label;
				}

				Send_Packet = __builtin_powf(Local_Networked_Origin[0] - Local_Previous_Origin[0], 2.f) + __builtin_powf(Local_Networked_Origin[1] - Local_Previous_Origin[1], 2.f) + __builtin_powf(Local_Networked_Origin[2] - Local_Previous_Origin[2], 2.f) > 4096.f;

				if (Send_Packet == 0)
				{
					Predicted_Send_Packet = __builtin_powf(Local_Networked_Origin[0] - Local_Origin[0], 2.f) + __builtin_powf(Local_Networked_Origin[1] - Local_Origin[1], 2.f) + __builtin_powf(Local_Networked_Origin[2] - Local_Origin[2], 2.f) > 4096.f;

					if (Predicted_Choked_Commands == Interface_Maximum_Choked_Commands.Get_Integer())
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

		static void* Entity_List = (void*)((unsigned __int64)Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(127111, (unsigned __int8*)Client_Module, 13429843744974553245ull), 3) + 8);

		using Get_Latency_Type = float(**)(void* Network_Channel, __int32 Type);

		void* Network_Channel = Get_Network_Channel();

		float Latency = (*Get_Latency_Type(*(unsigned __int64*)Network_Channel + 72))(Network_Channel, 0);

		using Get_Interpolation_Time_Type = float(*)();

		static void* Get_Interpolation_Time = Byte_Manager::Find_Bytes(489591, (unsigned __int8*)Engine_Module, 7804435399762144143);

		float Interpolation_Time = Get_Interpolation_Time_Type((unsigned __int64)Get_Interpolation_Time)();

		float Corrected_Latency = std::clamp(Latency + Interpolation_Time, 0.f, 1.f);

		Global_Variables_Structure* Global_Variables = Get_Global_Variables();

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
				void* Entity = *(void**)((unsigned __int64)Entity_List + (Entity_Number << 5));

				if (Entity != nullptr)
				{
					if (Entity != Local_Player)
					{
						if (*(__int8*)((unsigned __int64)Entity + 199) == 0)
						{
							if (Interface_Aim_Team.Get_Integer() + (*(__int32*)((unsigned __int64)Entity + 212) != *(__int32*)((unsigned __int64)Local_Player + 212)) != 0)
							{
								if (*(__int8*)((unsigned __int64)Entity + 506) == 0)
								{
									if ((*(__int32*)((unsigned __int64)Entity + 1088) & 32768) == 0)
									{
										if (*(__int32*)((unsigned __int64)Entity + 11508) == -1)
										{
											float Entity_Time = *(float*)((unsigned __int64)Player_Data->Data + 160);

											float* Entity_Origin = (float*)((unsigned __int64)Entity + 1064);

											Target_Structure Target =
											{
												Player_Data->Priority == -2 ? 0 : Player_Data->Priority,

												Entity,

												(__int32)((Entity_Time + Interpolation_Time) / Global_Variables->Interval_Per_Tick + 0.5f),

												__builtin_fabsf(Corrected_Latency - ((Global_Variables->Tick_Number + (Interface_Alternative.Get_Integer() ^ 1)) * Global_Variables->Interval_Per_Tick + Latency - Entity_Time)) <= 0.2f,

												__builtin_powf(Local_Origin[0] - Entity_Origin[0], 2.f) + __builtin_powf(Local_Origin[1] - Entity_Origin[1], 2.f) + __builtin_powf(Local_Origin[2] - Entity_Origin[2], 2.f)
											};

											Sorted_Target_List.push_back(Target);
										}
									}
								}
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

		if (Bullets_Fired == 0)
		{
			using Get_Weapon_Type = void*(__thiscall*)(void* Entity);

			static void* Get_Weapon = Byte_Manager::Find_Bytes(2157215077193497283, (unsigned __int8*)Client_Module, 16457719395962935568ull);

			void* Weapon = Get_Weapon_Type((unsigned __int64)Get_Weapon)(Local_Player);

			if (Weapon != nullptr)
			{
				Command->Buttons |= 8192 * (*(__int32*)((unsigned __int64)Weapon + 7248) == 0);
			}
		}
		else
		{
			if (__builtin_abs(*(__int32*)((unsigned __int64)Local_Player + 11664) - Shot_Tick_Number) * Global_Variables->Interval_Per_Tick > 0.5f)
			{
				if ((Command->Buttons & 2048) == 0)
				{
					__int8 Send_Packet_Sequence = (Send_Packet == 0) + (Predicted_Send_Packet == 1);

					if (Interface_Alternative.Get_Integer() == 1)
					{
						Send_Packet_Sequence = 2;
					}

					if (Send_Packet_Sequence == 2)
					{
						size_t Target_Number = 0;

						using Get_Eye_Position_Type = void(**)(void* Entity, float* Eye_Position);

						float Eye_Position[3];

						(*Get_Eye_Position_Type(*(unsigned __int64*)Local_Player + 1120))(Local_Player, Eye_Position);

						Recent_Player_Data_Number = 0;

						Traverse_Sorted_Target_List_Label:
						{
							if (Target_Number != Sorted_Target_List.size())
							{
								Target_Structure* Target = &Sorted_Target_List.at(Target_Number);

								using Get_Studio_Header_Type = void*(*)(void* Entity);

								static void* Get_Studio_Header = Byte_Manager::Find_Bytes(528343263, (unsigned __int8*)Client_Module, 15539617736627983104ull);

								void* Studio_Header = Get_Studio_Header_Type((unsigned __int64)Get_Studio_Header)(Target->Self);

								void* Hitbox_Set = (void*)(*(unsigned __int64*)Studio_Header + *(__int32*)(*(unsigned __int64*)Studio_Header + 176) + 12 * *(__int32*)((unsigned __int64)Target->Self + 5848));

								auto Find_Hitbox_By_Group = [&](__int32 Group) -> void*
								{
									__int32 Hitbox_Number = 0;

									Traverse_Hitboxes_Label:
									{
										void* Hitbox = nullptr;

										if (Hitbox_Number != *(__int32*)((unsigned __int64)Hitbox_Set + 4))
										{
											Hitbox = (void*)((unsigned __int64)Hitbox_Set + *(__int32*)((unsigned __int64)Hitbox_Set + 8) + Hitbox_Number * 68);

											if (*(__int32*)((unsigned __int64)Hitbox + 4) != Group)
											{
												Hitbox_Number += 1;

												goto Traverse_Hitboxes_Label;
											}
										}

										return Hitbox;
									}
								};

								void* Hitbox = Find_Hitbox_By_Group(Interface_Aim_Group.Get_Integer());

								if (Hitbox != nullptr)
								{
									Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int64)Target->Self + 128)];

									static __int8 Target_Data[14952];

									Byte_Manager::Copy_Bytes(1, Target_Data, sizeof(Target_Data), Target->Self);

									__int8 Animation_State_Data[320];

									void* Animation_State = *(void**)((unsigned __int64)Target->Self + 13928);

									Byte_Manager::Copy_Bytes(1, Animation_State_Data, sizeof(Animation_State_Data), Animation_State);

									struct Trace_Structure
									{
										__int8 Additional_Bytes_1[24];

										float Normal[3];

										__int8 Additional_Bytes_2[19];

										__int8 Solid;

										__int8 Additional_Bytes_3[24];

										__int32 Group;

										__int8 Additional_Bytes_4[4];

										void* Entity;

										__int8 Additional_Bytes_5[4];
									};

									if (Interface_Extrapolation.Get_Integer() == 1)
									{
										if ((Target->Valid ^ 1) + Player_Data->Teleported != 0)
										{
											__int32 Exponent = Player_Data->Tick_Number[1] - Player_Data->Tick_Number[0];

											if (Exponent > 0)
											{
												__int32 Extrapolation_Ticks = (__int32)(max(0, Global_Variables->Tick_Number - Player_Data->Tick_Number[1]) + (Interface_Alternative.Get_Integer() ^ 1) + Latency / Global_Variables->Interval_Per_Tick + 0.5f) / Exponent * Exponent;

												if ((Extrapolation_Ticks - Exponent | (__int32)(1.f / Global_Variables->Interval_Per_Tick + 0.5f) - Extrapolation_Ticks) >= 0)
												{
													Target->Valid = 0;

													__int32 Flags = *(__int32*)((unsigned __int64)Target->Self + 1088);

													float* Target_Origin = (float*)((unsigned __int64)Target->Self + 1064);

													if ((Flags & 1) == 1)
													{
														using Set_Origin_Type = void(*)(void* Entity, float* Origin);

														static void* Set_Origin = Byte_Manager::Find_Bytes(129892351, (unsigned __int8*)Client_Module, 5578744413008397460);

														Target_Origin[2] += 0.03125f;

														Set_Origin_Type((unsigned __int64)Set_Origin + 13)(Target->Self, Target_Origin);
													}

													using Set_Ground_Entity_Type = void(*)(void* Entity, void* Ground_Entity);

													static void* Set_Ground_Entity = Byte_Manager::Find_Bytes(245231, (unsigned __int8*)Client_Module, 6146399131556111791);

													Set_Ground_Entity_Type((unsigned __int64)Set_Ground_Entity)(Target->Self, (Flags & 1) == 1 ? *(void**)Entity_List : nullptr);

													*(__int8*)((unsigned __int64)Target->Self + 10744) = (Flags & 2) == 2;

													Command_Structure Target_Command = { };

													Target_Command.Buttons |= 4 * ((Flags & 2) == 2);

													*(__int32*)((unsigned __int64)Target->Self + 10768) = Target_Command.Buttons;

													*(float*)((unsigned __int64)Target->Self + 11280) = *(float*)((unsigned __int64)Target->Self + 11520);

													if (*(__int8*)((unsigned __int64)Target->Self + 500) == 9)
													{
														float Directions[8][3] =
														{
															{ Target_Origin[0] - 2.f, Target_Origin[1], Target_Origin[2] },

															{ Target_Origin[0], Target_Origin[1] - 2.f, Target_Origin[2] },

															{ Target_Origin[0] + 2.f, Target_Origin[1], Target_Origin[2] },

															{ Target_Origin[0], Target_Origin[1] + 2.f, Target_Origin[2] },

															{ Target_Origin[0] - 2.f, Target_Origin[1] - 2.f, Target_Origin[2] },

															{ Target_Origin[0] + 2.f, Target_Origin[1] - 2.f, Target_Origin[2] },

															{ Target_Origin[0] - 2.f, Target_Origin[1] + 2.f, Target_Origin[2] },

															{ Target_Origin[0] + 2.f, Target_Origin[1] + 2.f, Target_Origin[2] }
														};

														unsigned __int8 Trace_Number = 0;

														Perform_Trace_Label:
														{
															using Perform_Trace_Type = void(**)(void* Movement, float* Start, float* End, __int32 Mask, __int32 Group, Trace_Structure* Trace);

															static void* Movement = Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(31394695, (unsigned __int8*)Client_Module, 17805682010550749776ull), 3);

															*(__int32*)(*(unsigned __int64*)((unsigned __int64)Movement + 16) + 4) = *(__int32*)((unsigned __int64)Target->Self + 240);

															Trace_Structure Trace;

															(*Perform_Trace_Type(*(unsigned __int64*)Movement + 88))(Movement, Target_Origin, Directions[Trace_Number], 33636363, 8, &Trace);

															using On_Ladder_Type = __int8(**)(void* Movement, Trace_Structure* Trace);

															if ((*On_Ladder_Type(*(unsigned __int64*)Movement + 280))(Movement, &Trace) == 0)
															{
																Trace_Number += 1;

																if (Trace_Number != sizeof(Directions) / sizeof(Directions[0]))
																{
																	goto Perform_Trace_Label;
																}
															}

															Byte_Manager::Copy_Bytes(1, (float*)((unsigned __int64)Target->Self + 11632), sizeof(Trace.Normal), Trace.Normal);
														}
													}

													Byte_Manager::Copy_Bytes(1, Target_Command.Angles, sizeof(float[2]), (float*)((unsigned __int64)Target->Self + 13936));

													*(__int16*)((unsigned __int64)Prediction + 12) = 1;

													Suppress_Events(1);

													Extrapolate_Target_Label:
													{
														Correct_Movement(Target_Command.Angles, *(__int8*)((unsigned __int64)Target->Self + 500), Target_Command.Move, (float*)((unsigned __int64)Target->Self + 328), (float*)((unsigned __int64)Target->Self + 11632), &Target_Command.Buttons);

														Redirected_Run_Command(Prediction, Target->Self, &Target_Command, Move_Helper);

														Update_Animation_Time = Global_Variables->Time;

														Update_Animation_Type = 1;

														Redirected_Update_Animation(Target->Self);

														Update_Animation_Type = 0;

														if (Extrapolation_Ticks != 0)
														{
															Extrapolation_Ticks -= 1;

															goto Extrapolate_Target_Label;
														}
													}

													Suppress_Events(0);

													*(__int8*)((unsigned __int64)Prediction + 12) = 0;
												}
											}
										}
									}

									if (Target->Valid == 1)
									{
										*(void**)((unsigned __int64)Player_Data->Data + 5888) = *(void**)((unsigned __int64)Target->Self + 5888);

										*(void**)((unsigned __int64)Player_Data->Data + 6816) = *(void**)((unsigned __int64)Target->Self + 6816);

										Byte_Manager::Copy_Bytes(1, Target->Self, sizeof(Player_Data->Data), Player_Data->Data);

										Byte_Manager::Copy_Bytes(1, Animation_State, sizeof(Player_Data->Animation_State), Player_Data->Animation_State);
									}

									Compute_Torso_Rotation(Animation_State, Studio_Header);

									using Invalidate_Cache_Type = void(*)(void* Entity);

									static void* Invalidate_Cache = Byte_Manager::Find_Bytes(963, (unsigned __int8*)Client_Module, 12891891829448484194ull);

									Invalidate_Cache_Type((unsigned __int64)Invalidate_Cache)(Target->Self);

									using Setup_Bones_Type = __int8(**)(void* Entity, void* Bones, __int32 Maximum_Bones, __int32 Mask, float Time);

									float Bones[128][3][4];

									auto Restore_Target_Data = [&]() -> void
									{
										*(void**)((unsigned __int64)Target_Data + 5888) = *(void**)((unsigned __int64)Target->Self + 5888);

										*(void**)((unsigned __int64)Target_Data + 6816) = *(void**)((unsigned __int64)Target->Self + 6816);

										Byte_Manager::Copy_Bytes(1, Target->Self, sizeof(Target_Data), Target_Data);

										Byte_Manager::Copy_Bytes(1, Animation_State, sizeof(Animation_State_Data), Animation_State_Data);
									};

									if ((*Setup_Bones_Type(*(unsigned __int64*)((unsigned __int64)Target->Self + 8) + 128))((void*)((unsigned __int64)Target->Self + 8), Bones, sizeof(Bones) / sizeof(Bones[0]), 524032, Global_Variables->Time) == 1)
									{
										auto Perform_Trace = [&](float* Direction) -> __int8
										{
											struct alignas(16) Ray_Structure
											{
												__int8 Ray[80];

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

													*(__int8*)((unsigned __int64)Ray + 72) = 1;

													*(__int8*)((unsigned __int64)Ray + 73) = __builtin_powf(Delta[0], 2.f) + __builtin_powf(Delta[1], 2.f) + __builtin_powf(Delta[2], 2.f) != 0.f;
												}
											};

											struct Filter_Structure
											{
												void* Table;

												void* Skip;

												__int8 Additional_Bytes[16];
											};

											using Perform_Trace_Type = void(**)(void* Tracer, Ray_Structure* Ray, __int32 Mask, Filter_Structure* Filter, Trace_Structure* Trace);

											static void* Tracer = Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(34351873927, (unsigned __int8*)Engine_Module, 2998748780310145851), 3);

											Ray_Structure Ray;

											Vector_Normalize(Direction);

											float End[3]
											{
												Eye_Position[0] + Direction[0] * Weapon_Range,

												Eye_Position[1] + Direction[1] * Weapon_Range,

												Eye_Position[2] + Direction[2] * Weapon_Range
											};

											Ray.Initialize(Eye_Position, End);

											static void* Filter_Table = Byte_Manager::Solve_Relative(Byte_Manager::Find_Bytes(1047431, (unsigned __int8*)Client_Module, 8162175928024734831), 3);

											Filter_Structure Filter = { Filter_Table, Local_Player };

											Trace_Structure Trace;

											(*Perform_Trace_Type(*(unsigned __int64*)Tracer + 32))(Tracer, &Ray, 1174421507, &Filter, &Trace);

											if (Trace.Solid == 0)
											{
												using Clip_Trace_Type = void(*)(float* Start, float* End, __int32 Mask, Filter_Structure* Filter, Trace_Structure* Trace);

												static void* Clip_Trace = Byte_Manager::Find_Bytes(2047, (unsigned __int8*)Client_Module, 1493190178319228767);

												Clip_Trace_Type((unsigned __int64)Clip_Trace)(Eye_Position, End, 1174421507, &Filter, &Trace);
											}

											if (Trace.Entity == Target->Self)
											{
												if (Interface_Aim_Intersection.Get_Integer() == 0)
												{
													return Trace.Group == Interface_Aim_Group.Get_Integer();
												}

												return 1;
											}

											return 0;
										};

										float* Hitbox_Minimum = (float*)((unsigned __int64)Hitbox + 8);

										float* Hitbox_Maximum = (float*)((unsigned __int64)Hitbox + 20);

										float Hitbox_Center[3]
										{
											(Hitbox_Minimum[0] + Hitbox_Maximum[0]) / 2.f,

											(Hitbox_Minimum[1] + Hitbox_Maximum[1]) / 2.f,

											(Hitbox_Minimum[2] + Hitbox_Maximum[2]) / 2.f
										};

										__int32 Bone = *(__int32*)Hitbox;

										float Hitbox_Z_Vertices[8]
										{
											Bones[Bone][2][0] * Hitbox_Minimum[0] + Bones[Bone][2][1] * Hitbox_Minimum[1] + Bones[Bone][2][2] * Hitbox_Minimum[2],

											Bones[Bone][2][0] * Hitbox_Maximum[0] + Bones[Bone][2][1] * Hitbox_Minimum[1] + Bones[Bone][2][2] * Hitbox_Minimum[2],

											Bones[Bone][2][0] * Hitbox_Minimum[0] + Bones[Bone][2][1] * Hitbox_Maximum[1] + Bones[Bone][2][2] * Hitbox_Minimum[2],

											Bones[Bone][2][0] * Hitbox_Minimum[0] + Bones[Bone][2][1] * Hitbox_Minimum[1] + Bones[Bone][2][2] * Hitbox_Maximum[2],

											Bones[Bone][2][0] * Hitbox_Maximum[0] + Bones[Bone][2][1] * Hitbox_Maximum[1] + Bones[Bone][2][2] * Hitbox_Minimum[2],

											Bones[Bone][2][0] * Hitbox_Maximum[0] + Bones[Bone][2][1] * Hitbox_Minimum[1] + Bones[Bone][2][2] * Hitbox_Maximum[2],

											Bones[Bone][2][0] * Hitbox_Minimum[0] + Bones[Bone][2][1] * Hitbox_Maximum[1] + Bones[Bone][2][2] * Hitbox_Maximum[2],

											Bones[Bone][2][0] * Hitbox_Maximum[0] + Bones[Bone][2][1] * Hitbox_Maximum[1] + Bones[Bone][2][2] * Hitbox_Maximum[2]
										};

										float* Hitbox_Z_Extremes[2];

										std::tie(Hitbox_Z_Extremes[0], Hitbox_Z_Extremes[1]) = std::minmax_element(Hitbox_Z_Vertices, &Hitbox_Z_Vertices[sizeof(Hitbox_Z_Vertices) / sizeof(Hitbox_Z_Vertices[0])]);

										float Target_Origin[3] =
										{
											Bones[Bone][0][0] * Hitbox_Center[0] + Bones[Bone][0][1] * Hitbox_Center[1] + Bones[Bone][0][2] * Hitbox_Center[2] + Bones[Bone][0][3],

											Bones[Bone][1][0] * Hitbox_Center[0] + Bones[Bone][1][1] * Hitbox_Center[1] + Bones[Bone][1][2] * Hitbox_Center[2] + Bones[Bone][1][3],

											*Hitbox_Z_Extremes[0] + (*Hitbox_Z_Extremes[1] - *Hitbox_Z_Extremes[0]) * Interface_Aim_Height.Get_Floating_Point() + Bones[Bone][2][3]
										};

										float Direction[3] =
										{
											Target_Origin[0] - Eye_Position[0],

											Target_Origin[1] - Eye_Position[1],

											Target_Origin[2] - Eye_Position[2]
										};

										if (Perform_Trace(Direction) == 1)
										{
											if (Target->Valid == 1)
											{
												Command->Tick_Number = Target->Tick_Number;
											}

											struct Message_Structure
											{
												__int8 Message[64];

												void Construct(char* Name, char* Value)
												{
													using Construct_Type = void(*)(void* Message, char* Name, char* Value);

													static void* Construct = Byte_Manager::Find_Bytes(60662450159, (unsigned __int8*)Engine_Module, 6942253986675982385);

													Construct_Type((unsigned __int64)Construct)(this, Name, Value);
												}
											};

											Message_Structure Message;

											char Value[2] = { (char)('0' + Target->Valid) };

											Message.Construct((char*)"cl_lagcompensation", Value);

											using Write_Message_Type = __int8(**)(void* Message, void* Buffer);

											(*Write_Message_Type(*(unsigned __int64*)&Message + 40))(&Message, (void*)((unsigned __int64)Network_Channel + 88));

											Command->Angles[0] = __builtin_atan2f(-Direction[2], __builtin_hypotf(Direction[0], Direction[1])) * 180.f / 3.1415927f;

											Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180.f / 3.1415927f;

											Command->Buttons |= 1;

											if (Interface_Bruteforce.Get_Integer() == 1)
											{
												if (Player_Data->Priority != -2)
												{
													Recent_Player_Data_Number = *(__int32*)((unsigned __int64)Target->Self + 128);

													if (Player_Data->Memory_Tolerance == 0)
													{
														if (Player_Data->Tolerance == 0)
														{
															Player_Data->Shots_Fired = (Player_Data->Shots_Fired + 1) % Bruteforce_Angles_Count;

															Player_Data->Switch_X ^= Player_Data->Shots_Fired == 0;

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

											Restore_Target_Data();

											goto Found_Target_Label;
										}
									}

									Restore_Target_Data();
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
							float Forward[3];

							Angle_Vectors(Command->Angles, Forward, nullptr, nullptr);

							auto Compute_Spread = [&](float* Spread) -> void
							{
								using Random_Seed_Type = void(*)(__int32 Seed);

								static void* Standard_Library_Module = GetModuleHandleW(L"vstdlib.dll");

								static void* Random_Seed = (void*)GetProcAddress((HMODULE)Standard_Library_Module, "RandomSeed");

								Random_Seed_Type((unsigned __int64)Random_Seed)(Command->Random_Seed & 255);

								float Shot_Random[2];

								using Random_Type = float(*)(float Minimum, float Maximum);

								static void* Random = (void*)GetProcAddress((HMODULE)Standard_Library_Module, "RandomFloat");

								static Interface_Structure* Interface_Bias_Maximum = Find_Interface((char*)"ai_shot_bias_max");

								float Shot_Bias = Interface_Bias_Maximum->Get_Floating_Point();

								float Flatness = __builtin_fabsf(Shot_Bias) * 0.5f;

								Compute_Random_Label:
								{
									Shot_Random[0] = Random_Type((unsigned __int64)Random)(-1.f, 1.f) * Flatness + Random_Type((unsigned __int64)Random)(-1.f, 1.f) * (1.f - Flatness);

									Shot_Random[1] = Random_Type((unsigned __int64)Random)(-1.f, 1.f) * Flatness + Random_Type((unsigned __int64)Random)(-1.f, 1.f) * (1.f - Flatness);

									if (__builtin_signbitf(Shot_Bias) == 1)
									{
										Shot_Random[0] = __builtin_copysignf(1.f, Shot_Random[0]) - Shot_Random[0];

										Shot_Random[1] = __builtin_copysignf(1.f, Shot_Random[1]) - Shot_Random[1];
									}

									if (__builtin_powf(Shot_Random[0], 2.f) + __builtin_powf(Shot_Random[1], 2.f) > 1.f)
									{
										goto Compute_Random_Label;
									}
								}

								Spread[0] = 1.f;

								Spread[1] = Shot_Random[0] * Weapon_Spread[0];

								Spread[2] = Shot_Random[1] * Weapon_Spread[1];

								Vector_Normalize(Spread);
							};

							Command->Command_Number = -98069271;

							Command->Random_Seed = 33;

							float Spread[3];

							Compute_Spread(Spread);

							float Length = 1.f - __builtin_powf(Spread[1], 2.f);

							float Rotation[2] =
							{
								max(1e-45f, __builtin_sqrtf(Length - __builtin_powf(Forward[2], 2.f))),

								Forward[2] - (Forward[2] - __builtin_copysignf(__builtin_sqrtf(Length), Forward[2])) * (Rotation[0] == 1e-45f)
							};

							Command->Angles[0] = 180.f - __builtin_atan2f(-Spread[0] * Rotation[1] + Spread[2] * Rotation[0], Spread[0] * Rotation[0] + Spread[2] * Rotation[1]) * 180.f / 3.1415927f - Weapon_Recoil[0];

							Command->Angles[1] = 180.f + __builtin_atan2f(Forward[0] * Spread[1] + Forward[1] * Rotation[0], Forward[0] * Rotation[0] + Forward[1] * -Spread[1]) * 180.f / 3.1415927f - Weapon_Recoil[1];

							In_Attack = 1;

							Send_Packet = Interface_Alternative.Get_Integer() * 2;

							Shot_Tick_Number = *(__int32*)((unsigned __int64)Local_Player + 11664);
						}
					}
				}
			}
		}

		Command->Buttons &= ~2048;

		if (In_Attack == 0)
		{
			Command->Buttons &= ~1;

			if (Sorted_Target_List.size() != 0)
			{
				Command->Angles[0] = Interface_Angle_X.Get_Floating_Point();

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
						Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180.f / 3.1415927f + Interface_First_Choked_Angle_Y.Get_Floating_Point();
					}
					else
					{
						Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180.f / 3.1415927f + Interface_Second_Choked_Angle_Y.Get_Floating_Point();
					}
				}
				else
				{
					Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180.f / 3.1415927f + Interface_Angle_Y.Get_Floating_Point();
				}
			}
		}

		Correct_Movement(Command->Angles, Move_Type, Command->Move, Desired_Move, Ladder_Normal, &Command->Buttons);

		if (Send_Packet == 0)
		{
			__int32 Sequence_Number = *(__int32*)((unsigned __int64)Network_Channel + 12) = Redirected_Send_Datagram(Network_Channel, nullptr);

			Sequences[Sequence_Number % 90] = Get_Last_Command_Number();
		}
		else
		{
			Byte_Manager::Copy_Bytes(1, Update_Animation_Angles, sizeof(Update_Animation_Angles), Command->Angles);
		}

		*(__int8*)((unsigned __int64)Stack + 296) = Send_Packet;
	}

	Copy_Command_Manager.Special_Call(Unknown_Parameter, Command);
}

__attribute__((naked)) void Redirected_Copy_Command()
{
	asm("movq %rsp, %r8");
	asm("jmp %P0" : : "i"(Copy_Command));
}