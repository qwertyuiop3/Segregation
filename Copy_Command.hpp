Player_Data_Structure Previous_Recent_Player_Data;

SafetyHookInline Original_Copy_Command_Caller{};

void Copy_Command(void* Unknown_Parameter, Command_Structure* Command, void* Frame_Address)
{
	Command->Extra_Simulations = 0;

	void* Local_Player = *(void**)((unsigned __int64)Client_Module + 9394464);

	if (*(__int8*)((unsigned __int64)Local_Player + 199) == 0)
	{
		using Run_Prediction_Type = void(*)();

		Run_Prediction_Type((unsigned __int64)Engine_Module + 634048)();

		auto Angle_Vectors = [](float* Angles, float* Forward, float* Right, float* Up) -> void
		{
			using Angle_Vectors_Type = void(*)(float* Angles, float* Forward, float* Right, float* Up);

			Angle_Vectors_Type((unsigned __int64)Client_Module + 4252608)(Angles, Forward, Right, Up);
		};

		float Move_Angles[3] =
		{
			Command->Angles[0],

			Command->Angles[1]
		};

		static float Previous_Move_Angle_Y;

		if ((Command->Buttons & 2) + *(__int8*)((unsigned __int64)Local_Player + 500) == 4)
		{
			Command->Move[0] = 0;

			if (*(__int32*)((unsigned __int64)Local_Player + 764) == -1)
			{
				Command->Buttons &= ~2;
			}
			else
			{
				Command->Buttons &= ~(*(__int32*)((unsigned __int64)Local_Player + 11364) & 2);
			}

			float Difference = __builtin_remainderf(Move_Angles[1] - Previous_Move_Angle_Y, 360.f);

			Previous_Move_Angle_Y = Move_Angles[1];

			float* Velocity = (float*)((unsigned __int64)Local_Player + 328);

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

		float Desired_Move_Forward[3];

		float Desired_Move_Right[3];

		Angle_Vectors(Move_Angles, Desired_Move_Forward, Desired_Move_Right, nullptr);

		Desired_Move_Forward[2] = 0.f;

		auto Vector_Normalize = [](float* Vector) -> float
		{
			using Vector_Normalize_Type = float(*)(float* Vector);

			return Vector_Normalize_Type((unsigned __int64)Client_Module + 4275520)(Vector);
		};

		Vector_Normalize(Desired_Move_Forward);

		Desired_Move_Right[2] = 0.f;

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

			Move_Forward[2] = 0.f;

			Vector_Normalize(Move_Forward);

			Move_Right[2] = 0.f;

			Vector_Normalize(Move_Right);

			float Divider = Move_Forward[0] * Move_Right[1] - Move_Right[0] * Move_Forward[1];

			float X = std::clamp((Desired_Move[0] * Move_Right[1] - Move_Right[0] * Desired_Move[1]) / Divider, -16383.999f, 16383.999f);

			Command->Move[0] = X;

			Command->Buttons &= ~1560;

			if (__builtin_truncf(X) != 0.f)
			{
				Command->Buttons |= 8 * ((X < 0.f) + 1);
			}

			float Y = std::clamp((Move_Forward[0] * Desired_Move[1] - Desired_Move[0] * Move_Forward[1]) / Divider, -16383.999f, 16383.999f);

			Command->Move[1] = Y;

			if (__builtin_truncf(Y) != 0.f)
			{
				Command->Buttons |= 512 * ((Y > 0.f) + 1);
			}
		};

		Correct_Movement();

		Command->Typing = 1;

		Bullets_Fired = 0;

		__int32 Previous_Buttons = Command->Buttons;

		Command->Buttons |= 1;
		
		void* Prediction = (void*)((unsigned __int64)Client_Module + 9083280);

		*(__int8*)((unsigned __int64)Prediction + 12) = 1;

		*(__int8*)((unsigned __int64)Prediction + 13) = 0;

		auto Suppress_Events = [](__int8 State) -> void
		{
			void* Prediction_System = *(void**)((unsigned __int64)Client_Module + 10394840);

			Traverse_Prediction_Systems_Label:
			{
				if (Prediction_System != nullptr)
				{
					*(__int8*)((unsigned __int64)Prediction_System + 16) = State;

					Prediction_System = *(void**)((unsigned __int64)Prediction_System + 8);

					goto Traverse_Prediction_Systems_Label;
				}
			}
		};

		Suppress_Events(1);

		float Local_Previous_Origin[3];

		float* Local_Origin = (float*)((unsigned __int64)Local_Player + 1064);

		if (Interface_Alternative.Get_Integer() == 0)
		{
			Byte_Manager::Copy_Bytes(1, Local_Previous_Origin, sizeof(Local_Previous_Origin), Local_Origin);
		}

		Redirected_Run_Command(Prediction, Local_Player, Command, (void*)((unsigned __int64)Client_Module + 8720768));

		Suppress_Events(0);

		*(__int8*)((unsigned __int64)Prediction + 12) = 0;

		Command->Buttons = Previous_Buttons;

		Byte_Manager::Copy_Bytes(1, Command->Move, sizeof(Previous_Move), Previous_Move);

		static __int8 Send_Packet;

		__int32 Choked_Commands_Count = *(__int32*)((unsigned __int64)Engine_Module + 6124736);

		__int8 Predicted_Send_Packet = 0;

		static float Local_Networked_Origin[3];

		if (Interface_Alternative.Get_Integer() == 0)
		{
			__int32 Predicted_Choked_Commands_Count = Choked_Commands_Count + 1;

			if (Choked_Commands_Count < Interface_Minimum_Choked_Commands.Get_Integer())
			{
				Send_Packet = 0;

				if (Predicted_Choked_Commands_Count == Interface_Minimum_Choked_Commands.Get_Integer())
				{
					if (Predicted_Choked_Commands_Count < Interface_Maximum_Choked_Commands.Get_Integer())
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
				if (Choked_Commands_Count < Interface_Maximum_Choked_Commands.Get_Integer())
				{
					if (__builtin_powf(Local_Networked_Origin[0] - Local_Previous_Origin[0], 2.f) + __builtin_powf(Local_Networked_Origin[1] - Local_Previous_Origin[1], 2.f) + __builtin_powf(Local_Networked_Origin[2] - Local_Previous_Origin[2], 2.f) <= 4096.f)
					{
						Send_Packet = 0;

						Predict_Dynamic_Send_Packet_Label:
						{
							if (Predicted_Choked_Commands_Count == Interface_Maximum_Choked_Commands.Get_Integer())
							{
								Predicted_Send_Packet = 1;
							}
							else
							{
								if (__builtin_powf(Local_Networked_Origin[0] - Local_Origin[0], 2.f) + __builtin_powf(Local_Networked_Origin[1] - Local_Origin[1], 2.f) + __builtin_powf(Local_Networked_Origin[2] - Local_Origin[2], 2.f) > 4096.f)
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
							Byte_Manager::Copy_Bytes(1, Local_Networked_Origin, sizeof(Local_Networked_Origin), Local_Origin);

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

			if (Choked_Commands_Count < Interface_Minimum_Choked_Commands.Get_Integer())
			{
				Send_Packet = 0;
			}
			else
			{
				if (Choked_Commands_Count < Interface_Maximum_Choked_Commands.Get_Integer())
				{
					if (__builtin_powf(Local_Networked_Origin[0] - Local_Origin[0], 2.f) + __builtin_powf(Local_Networked_Origin[1] - Local_Origin[1], 2.f) + __builtin_powf(Local_Networked_Origin[2] - Local_Origin[2], 2.f) <= 4096.f)
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

		using Get_Latency_Type = float(*)(void* Network_Channel, __int32 Type);

		void* Network_Channel = *(void**)((unsigned __int64)Engine_Module + 5990752);

		float Latency = Get_Latency_Type((unsigned __int64)Engine_Module + 1945664)(Network_Channel, 0);

		using Get_Interpolation_Time_Type = float(*)();

		float Interpolation_Time = Get_Interpolation_Time_Type((unsigned __int64)Engine_Module + 698192)();

		float Corrected_Latency = std::clamp(Latency + Interpolation_Time, 0.f, 1.f);

		Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)((unsigned __int64)Client_Module + 8690824);

		struct Target_Structure
		{
			__int32 Priority;

			void* Self;

			__int32 Tick_Number;

			__int32 Valid;

			float Distance;
		};

		static std::vector<Target_Structure> Sorted_Target_List;

		Sorted_Target_List.clear();

		Traverse_Entity_List_Label:
		{
			Player_Data_Structure* Player_Data = &Players_Data[Entity_Number];

			if (Player_Data->Priority != -1)
			{
				void* Entity = *(void**)((unsigned __int64)Client_Module + 9532984 + (Entity_Number << 5));

				if (Entity != nullptr)
				{
					if (Entity != Local_Player)
					{
						if (*(__int8*)((unsigned __int64)Entity + 199) == 0)
						{
							if ((Interface_Team_Check.Get_Integer() != 1) + (*(__int32*)((unsigned __int64)Entity + 212) != *(__int32*)((unsigned __int64)Local_Player + 212)) != 0)
							{
								if (*(__int8*)((unsigned __int64)Entity + 506) == 0)
								{
									float Entity_Time = *(float*)((unsigned __int64)Entity + 160);

									float* Entity_Origin = (float*)((unsigned __int64)Entity + 1064);

									Target_Structure Target =
									{
										Player_Data->Priority == -2 ? 0 : Player_Data->Priority,

										Entity,

										(__int32)((Entity_Time + Interpolation_Time) / Global_Variables->Interval_Per_Tick + 0.5f),

										__builtin_fabsf(Corrected_Latency - (__int32)(Global_Variables->Tick_Number + (Interface_Alternative.Get_Integer() == 0) + (Latency - Entity_Time) / Global_Variables->Interval_Per_Tick + 0.5f) * Global_Variables->Interval_Per_Tick) <= 0.2f,

										__builtin_powf(Local_Origin[0] - Entity_Origin[0], 2.f) + __builtin_powf(Local_Origin[1] - Entity_Origin[1], 2.f) + __builtin_powf(Local_Origin[2] - Entity_Origin[2], 2.f)
									};

									Sorted_Target_List.push_back(Target);
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

		if (Bullets_Fired == 0)
		{
			if (*(__int32*)((unsigned __int64)Local_Player + 10560) != -1)
			{
				__int32 Weapon_Index = *(unsigned __int32*)((unsigned __int64)Local_Player + 10560) & 16383;
				
				if (*(__int32*)((unsigned __int64)Client_Module + 9532992 + (Weapon_Index << 5)) == (__int32)(*(unsigned __int32*)((unsigned __int64)Local_Player + 10560) >> 14))
				{
					void* Weapon = *(void**)((unsigned __int64)Client_Module + 9532984 + (Weapon_Index << 5));

					if (Weapon != nullptr)
					{
						Command->Buttons |= 8192 * (*(__int32*)((unsigned __int64)Weapon + 7248) == 0);
					}
				}
			}
		}
		else
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

							if (Interface_Alternative.Get_Integer() != 0)
							{
								Send_Packet_Sequence = 2;
							}

							if (Send_Packet_Sequence == 2)
							{
								size_t Target_Number = 0;

								using Get_Eye_Position_Type = void(*)(void* Entity, float* Eye_Position);

								float Eye_Position[3];

								Get_Eye_Position_Type((unsigned __int64)Client_Module + 1464960)(Local_Player, Eye_Position);

								Recent_Player_Data_Number = 0;

								Traverse_Sorted_Target_List_Label:
								{
									if (Target_Number != Sorted_Target_List.size())
									{
										Target_Structure* Target = &Sorted_Target_List.at(Target_Number);

										using Get_Studio_Header_Type = void*(*)(void* Entity);

										void* Studio_Header = Get_Studio_Header_Type((unsigned __int64)Client_Module + 663760)(Target->Self);

										void* Hitbox_Set = (void*)((unsigned __int64)*(void**)Studio_Header + *(__int32*)((unsigned __int64)*(void**)Studio_Header + 176) + 12 * *(__int32*)((unsigned __int64)Target->Self + 5848));

										auto Find_Hitbox_By_Group = [&](__int32 Group) -> void*
										{
											void* Hitbox;

											__int32 Hitbox_Number = 0;

											Traverse_Hitboxes_Label:
											{
												Hitbox = nullptr;

												if (Hitbox_Number != *(__int32*)((unsigned __int64)Hitbox_Set + 4))
												{
													Hitbox = (void*)((unsigned __int64)Hitbox_Set + *(__int32*)((unsigned __int64)Hitbox_Set + 8) + Hitbox_Number * 68);

													if (*(__int32*)((unsigned __int64)Hitbox + 4) != Group)
													{
														Hitbox_Number += 1;

														goto Traverse_Hitboxes_Label;
													}
												}
											}

											return Hitbox;
										};

										void* Hitbox = Find_Hitbox_By_Group(Interface_Aim_Hitgroup.Get_Integer());

										if (Hitbox != nullptr)
										{
											using Set_Local_Origin_Type = void(*)(void* Entity, float* Origin);
											
											float Target_Previous_Origin[3];
											
											Byte_Manager::Copy_Bytes(1, Target_Previous_Origin, sizeof(Target_Previous_Origin), (float*)((unsigned __int64)Target->Self + 1064));

											Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int64)Target->Self + 128)];
											
											if (Target->Valid == 1)
											{
												Byte_Manager::Copy_Bytes(1, (float*)((unsigned __int64)Target->Self + 1064), sizeof(Player_Data->Last_Update_Origin), Player_Data->Last_Update_Origin);
												
												Set_Local_Origin_Type((unsigned __int64)Client_Module + 1758400)(Target->Self, (float*)((unsigned __int64)Target->Self + 1064));
											}
											
											if (Interface_Extrapolation.Get_Integer() == 1)
											{
												if ((Target->Valid ^ 1) + Player_Data->Breaks_Lag_Compensation != 0)
												{
													if ((Player_Data->Simulation_Ticks[Target->Valid] - 1 | 22 - Player_Data->Simulation_Ticks[Target->Valid]) >= 0)
													{
														__int32 Delta_Ticks = max(0, Global_Variables->Tick_Number - Player_Data->Last_Update_Tick_Number[Target->Valid]);
														
														if (Player_Data->Simulation_Ticks[Target->Valid] - Delta_Ticks > 0)
														{
															__int32 Latency_Ticks = Latency / Global_Variables->Interval_Per_Tick + 0.5f;
															
															__int32 Extrapolation_Windows = (Latency_Ticks + Delta_Ticks + (Interface_Alternative.Get_Integer() == 0)) / Player_Data->Simulation_Ticks[Target->Valid];

															if (Extrapolation_Windows > 0)
															{
																if (*(__int32*)((unsigned __int64)Target->Self + 11452) == -1)
																{
																	float Previous_Velocity[3];
																	
																	Byte_Manager::Copy_Bytes(1, Previous_Velocity, sizeof(Previous_Velocity), (float*)((unsigned __int64)Target->Self + 328));
																	
																	if (__builtin_sqrtf(__builtin_powf(Previous_Velocity[0], 2.f) + __builtin_powf(Previous_Velocity[1], 2.f) + __builtin_powf(Previous_Velocity[2], 2.f)) >= 1.f)
																	{
																		float Previous_Current_Time = Global_Variables->Current_Time;
																		
																		void* Previous_Lua_Gamemode = *(void**)((unsigned __int64)Client_Module + 9096200);
																		
																		float Previous_View_Offset[3];
																		
																		Byte_Manager::Copy_Bytes(1, Previous_View_Offset, sizeof(Previous_View_Offset), (float*)((unsigned __int64)Target->Self + 316));
																		
																		float Previous_Gravity = *(float*)((unsigned __int64)Target->Self + 476);
																		
																		unsigned __int8 Previous_Move_Type = *(unsigned __int8*)((unsigned __int64)Target->Self + 500);
																		
																		unsigned __int8 Previous_Move_Collide = *(unsigned __int8*)((unsigned __int64)Target->Self + 501);
																		
																		unsigned __int8 Previous_Water_Level = *(unsigned __int8*)((unsigned __int64)Target->Self + 504);
																		
																		float Previous_Mins[3];
																		
																		Byte_Manager::Copy_Bytes(1, Previous_Mins, sizeof(Previous_Mins), (float*)((unsigned __int64)Target->Self + 560));
																		
																		float Previous_Maxs[3];
																		
																		Byte_Manager::Copy_Bytes(1, Previous_Maxs, sizeof(Previous_Maxs), (float*)((unsigned __int64)Target->Self + 572));
																		
																		unsigned __int8 Previous_Solid_Type = *(unsigned __int8*)((unsigned __int64)Target->Self + 617);
																		
																		__int32 Previous_Flags = *(__int32*)((unsigned __int64)Target->Self + 1088);
																		
																		__int8 Previous_Client_Side_Animation = *(__int8*)((unsigned __int64)Target->Self + 6616);
																		
																		__int32 Previous_Weapons[256];
																		
																		Byte_Manager::Copy_Bytes(1, Previous_Weapons, sizeof(Previous_Weapons), (__int32*)((unsigned __int64)Target->Self + 9536));
																		
																		__int32 Previous_Active_Weapon = *(__int32*)((unsigned __int64)Target->Self + 10560);
																		
																		float Previous_Max_Speed = *(float*)((unsigned __int64)Target->Self + 11464);
																		
																		__int32 Previous_View_Models[3];
																		
																		Byte_Manager::Copy_Bytes(1, Previous_View_Models, sizeof(Previous_View_Models), (__int32*)((unsigned __int64)Target->Self + 11680));
																		
																		__int8 Previous_Is_Sprinting = *(__int8*)((unsigned __int64)Target->Self + 13824);
																		
																		__int8 Previous_Is_Walking = *(__int8*)((unsigned __int64)Target->Self + 14060);
																		
																		__int8 Previous_Is_Typing = *(__int8*)((unsigned __int64)Target->Self + 14562);

																		Command_Structure Target_Command;
																		
																		Byte_Manager::Set_Bytes(1, &Target_Command, sizeof(Target_Command), 0);
																		
																		if (Previous_Move_Type != 2)
																		{
																			Target_Command.Angles[0] = __builtin_atan2f(-Previous_Velocity[2], __builtin_hypotf(Previous_Velocity[0], Previous_Velocity[1])) * 180.f / 3.1415927f;
																		}
																		
																		Target_Command.Angles[1] = __builtin_atan2f(Previous_Velocity[1], Previous_Velocity[0]) * 180.f / 3.1415927f;
																		
																		Target_Command.Move[0] = 10000.f;
																		
																		Target_Command.Buttons |= 4 * ((Previous_Flags & 2) == 2) | 8;
																		
																		if ((Previous_Flags & 1) == 1)
																		{
																			*(float*)((unsigned __int64)Target->Self + 1072) += 0.03125f;

																			Set_Local_Origin_Type((unsigned __int64)Client_Module + 1758400)(Target->Self, (float*)((unsigned __int64)Target->Self + 824));
																		}
																		
																		using Set_Ground_Entity_Type = void(*)(void* Entity, void* Ground_Entity);

																		Set_Ground_Entity_Type((unsigned __int64)Client_Module + 2708768)(Target->Self, (Previous_Flags & 1) == 1 ? *(void**)((unsigned __int64)Client_Module + 9462456) : nullptr);
																		
																		*(void**)((unsigned __int64)Client_Module + 9096200) = nullptr;
																		
																		*(__int32*)((unsigned __int64)Target->Self + 188) = -1;
																		
																		Byte_Manager::Set_Bytes(1, (float*)((unsigned __int64)Target->Self + 464), sizeof(float[3]), 0);

																		*(float*)((unsigned __int64)Target->Self + 772) = 1.f;
																		
																		*(__int8*)((unsigned __int64)Target->Self + 6616) = 1;
																		
																		Byte_Manager::Set_Bytes(1, (__int32*)((unsigned __int64)Target->Self + 9536), sizeof(__int32[256]), 255);
																		
																		*(__int32*)((unsigned __int64)Target->Self + 10560) = -1;
																		
																		*(__int8*)((unsigned __int64)Target->Self + 10720) = (Previous_Flags & 2) == 2;
																		
																		*(__int8*)((unsigned __int64)Target->Self + 10721) = 0;
																		
																		*(__int8*)((unsigned __int64)Target->Self + 10722) = 0;
																		
																		Byte_Manager::Set_Bytes(1, (float*)((unsigned __int64)Target->Self + 10724), sizeof(float[3]), 0);

																		*(__int32*)((unsigned __int64)Target->Self + 10744) = Target_Command.Buttons;
																		
																		*(__int8*)((unsigned __int64)Target->Self + 10960) = 1;
																		
																		*(float*)((unsigned __int64)Target->Self + 11240) = Previous_Max_Speed;
																		
																		*(float*)((unsigned __int64)Target->Self + 11248) = *(float*)((unsigned __int64)Local_Player + 11248);
																		
																		*(float*)((unsigned __int64)Target->Self + 11252) = *(float*)((unsigned __int64)Local_Player + 11252);
																		
																		*(float*)((unsigned __int64)Target->Self + 11256) = *(float*)((unsigned __int64)Local_Player + 11256);
																		
																		*(float*)((unsigned __int64)Target->Self + 11260) = *(float*)((unsigned __int64)Local_Player + 11260);

																		*(__int32*)((unsigned __int64)Target->Self + 11364) = Target_Command.Buttons;
																		
																		*(__int32*)((unsigned __int64)Target->Self + 11376) = -1;
																		
																		Byte_Manager::Set_Bytes(1, (float*)((unsigned __int64)Target->Self + 11380), sizeof(float[3]), 0);
																		
																		*(float*)((unsigned __int64)Target->Self + 11392) = 0.f;

																		*(float*)((unsigned __int64)Target->Self + 11564) = 0.f;
																		
																		*(float*)((unsigned __int64)Target->Self + 11576) = 1.f;
																		
																		Byte_Manager::Set_Bytes(1, (float*)((unsigned __int64)Target->Self + 11580), sizeof(float[2]), 0);

																		*(__int32*)((unsigned __int64)Target->Self + 11608) = Global_Variables->Tick_Number;

																		Byte_Manager::Set_Bytes(1, (__int32*)((unsigned __int64)Target->Self + 11680), sizeof(__int32[3]), 255);

																		*(float*)((unsigned __int64)Target->Self + 13136) = 1.f;
																		
																		*(__int32*)((unsigned __int64)Target->Self + 13188) = 0;
																		
																		*(void**)((unsigned __int64)Target->Self + 13192) = nullptr;
																		
																		*(float*)((unsigned __int64)Target->Self + 13200) = 1.f;
																		
																		*(__int8*)((unsigned __int64)Target->Self + 13204) = 0;

																		*(__int32*)((unsigned __int64)Target->Self + 13764) = -1;
																		
																		*(__int8*)((unsigned __int64)Target->Self + 13768) = 0;

																		*(__int8*)((unsigned __int64)Prediction + 12) = 1;

																		*(__int8*)((unsigned __int64)Prediction + 13) = 0;

																		Suppress_Events(1);

																		__int32 Extrapolation_Ticks = Extrapolation_Windows * Player_Data->Simulation_Ticks[Target->Valid];

																		Extrapolate_Target_Label:
																		{
																			if (Extrapolation_Ticks != 0)
																			{
																				Redirected_Run_Command(Prediction, Target->Self, &Target_Command, (void*)((unsigned __int64)Client_Module + 8720768));
						
																				Extrapolation_Ticks -= 1;
																				
																				goto Extrapolate_Target_Label;
																			}
																		}
																		
																		Suppress_Events(0);

																		*(__int8*)((unsigned __int64)Prediction + 12) = 0;
																		
																		Global_Variables->Current_Time = Previous_Current_Time;

																		*(void**)((unsigned __int64)Client_Module + 9096200) = Previous_Lua_Gamemode;
																		
																		Byte_Manager::Copy_Bytes(1, (float*)((unsigned __int64)Target->Self + 316), sizeof(Previous_View_Offset), Previous_View_Offset);
																		
																		Byte_Manager::Copy_Bytes(1, (float*)((unsigned __int64)Target->Self + 328), sizeof(Previous_Velocity), Previous_Velocity);
																		
																		*(__int32*)((unsigned __int64)Target->Self + 496) |= 4096;
																		
																		*(float*)((unsigned __int64)Target->Self + 476) = Previous_Gravity;
																		
																		*(unsigned __int8*)((unsigned __int64)Target->Self + 500) = Previous_Move_Type;
																		
																		*(unsigned __int8*)((unsigned __int64)Target->Self + 501) = Previous_Move_Collide;
																		
																		*(unsigned __int8*)((unsigned __int64)Target->Self + 504) = Previous_Water_Level;
																		
																		using Set_Collision_Bounds_Type = void(*)(void* Collision, float* Mins, float* Maxs);
																		
																		Set_Collision_Bounds_Type((unsigned __int64)Client_Module + 2174768)((void*)((unsigned __int64)Target->Self + 544), Previous_Mins, Previous_Maxs);
																		
																		using Set_Solid_Type = void(*)(void* Collision, __int32 Solid_Type);
																		
																		Set_Solid_Type((unsigned __int64)Client_Module + 2175664)((void*)((unsigned __int64)Target->Self + 544), Previous_Solid_Type);
																		
																		*(__int32*)((unsigned __int64)Target->Self + 1088) = Previous_Flags;
																		
																		*(__int8*)((unsigned __int64)Target->Self + 6616) = Previous_Client_Side_Animation;
																		
																		Byte_Manager::Copy_Bytes(1, (__int32*)((unsigned __int64)Target->Self + 9536), sizeof(Previous_Weapons), Previous_Weapons);
																		
																		*(__int32*)((unsigned __int64)Target->Self + 10560) = Previous_Active_Weapon;
																		
																		*(float*)((unsigned __int64)Target->Self + 11464) = Previous_Max_Speed;

																		Byte_Manager::Copy_Bytes(1, (__int32*)((unsigned __int64)Target->Self + 11680), sizeof(Previous_View_Models), Previous_View_Models);
																		
																		*(__int8*)((unsigned __int64)Target->Self + 13824) = Previous_Is_Sprinting;
																		
																		*(__int8*)((unsigned __int64)Target->Self + 14060) = Previous_Is_Walking;
																		
																		*(__int8*)((unsigned __int64)Target->Self + 14562) = Previous_Is_Typing;
																	}
																}
															}
														}
													}
												}
											}
											
											Compute_Custom_Torso_Rotation(*(void**)((unsigned __int64)Target->Self + 13856), Studio_Header);

											using Invalidate_Bone_Cache_Type = void(*)(void* Entity);

											Invalidate_Bone_Cache_Type((unsigned __int64)Client_Module + 1657568)(Target->Self);

											using Get_Bone_Cache_Type = void*(*)(unsigned __int32 Bone_Cache_Handle);

											void* Bone_Cache = Get_Bone_Cache_Type((unsigned __int64)Client_Module + 1592480)(*(unsigned __int32*)((unsigned __int64)Target->Self + 6816));

											if (Bone_Cache != nullptr)
											{
												*(float*)Bone_Cache = -1.f;
											}

											using Setup_Bones_Type = __int8(*)(void* Entity, void* Bones, __int32 Maximum_Bones, __int32 Mask, float Current_Time);

											float Bones[128][3][4];

											if (Setup_Bones_Type((unsigned __int64)Client_Module + 1674176)((void*)((unsigned __int64)Target->Self + 8), Bones, 128, 524032, Global_Variables->Current_Time) == 1)
											{
												auto Trace_Ray = [&](float Direction[3]) -> __int8
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

														__int32 Group;

														void* Handler;
													};

													struct Trace_Structure
													{
														__int8 Additional_Bytes_1[55];

														__int8 Start_Solid;

														__int8 Additional_Bytes_2[24];

														__int32 Group;

														__int8 Additional_Bytes_3[4];

														void* Entity;

														__int8 Additional_Bytes_4[4];
													};

													using Trace_Ray_Type = void(*)(void* Engine, Ray_Structure* Ray, __int32 Mask, Filter_Structure* Filter, Trace_Structure* Trace);

													Ray_Structure Ray;

													Vector_Normalize(Direction);

													float End[3]
													{
														Eye_Position[0] + Direction[0] * Weapon_Range,

														Eye_Position[1] + Direction[1] * Weapon_Range,

														Eye_Position[2] + Direction[2] * Weapon_Range
													};
													
													Ray.Initialize(Eye_Position, End);

													Filter_Structure Filter;

													Filter.Table = (void*)((unsigned __int64)Client_Module + 7016360);

													Filter.Skip = Local_Player;

													Filter.Group = 0;

													Filter.Handler = nullptr;

													Trace_Structure Trace;
													
													Trace.Entity = nullptr;
													
													Trace_Ray_Type((unsigned __int64)Engine_Module + 1721008)((void*)((unsigned __int64)Engine_Module + 5022592), &Ray, 1174421507, &Filter, &Trace);

													if (Trace.Start_Solid == 0)
													{
														using Clip_Trace_To_Players_Type = void(*)(float* Start, float* End, __int32 Mask, Filter_Structure* Filter, Trace_Structure* Trace);

														Clip_Trace_To_Players_Type((unsigned __int64)Client_Module + 2935776)(Eye_Position, End, 1174421507, &Filter, &Trace);
													}

													if (Trace.Entity == Target->Self)
													{
														if (Interface_Aim_Intersection.Get_Integer() == 0)
														{
															return Trace.Group == Interface_Aim_Hitgroup.Get_Integer();
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

												__int32 Bone_Index = *(__int32*)Hitbox;

												float Hitbox_Z_Vertices[8]
												{
													Bones[Bone_Index][2][0] * Hitbox_Minimum[0] + Bones[Bone_Index][2][1] * Hitbox_Minimum[1] + Bones[Bone_Index][2][2] * Hitbox_Minimum[2],

													Bones[Bone_Index][2][0] * Hitbox_Maximum[0] + Bones[Bone_Index][2][1] * Hitbox_Minimum[1] + Bones[Bone_Index][2][2] * Hitbox_Minimum[2],

													Bones[Bone_Index][2][0] * Hitbox_Minimum[0] + Bones[Bone_Index][2][1] * Hitbox_Maximum[1] + Bones[Bone_Index][2][2] * Hitbox_Minimum[2],

													Bones[Bone_Index][2][0] * Hitbox_Minimum[0] + Bones[Bone_Index][2][1] * Hitbox_Minimum[1] + Bones[Bone_Index][2][2] * Hitbox_Maximum[2],

													Bones[Bone_Index][2][0] * Hitbox_Maximum[0] + Bones[Bone_Index][2][1] * Hitbox_Maximum[1] + Bones[Bone_Index][2][2] * Hitbox_Minimum[2],

													Bones[Bone_Index][2][0] * Hitbox_Maximum[0] + Bones[Bone_Index][2][1] * Hitbox_Minimum[1] + Bones[Bone_Index][2][2] * Hitbox_Maximum[2],

													Bones[Bone_Index][2][0] * Hitbox_Minimum[0] + Bones[Bone_Index][2][1] * Hitbox_Maximum[1] + Bones[Bone_Index][2][2] * Hitbox_Maximum[2],

													Bones[Bone_Index][2][0] * Hitbox_Maximum[0] + Bones[Bone_Index][2][1] * Hitbox_Maximum[1] + Bones[Bone_Index][2][2] * Hitbox_Maximum[2]
												};

												float* Hitbox_Z_Extremes[2];

												std::tie(Hitbox_Z_Extremes[0], Hitbox_Z_Extremes[1]) = std::minmax_element(Hitbox_Z_Vertices, &Hitbox_Z_Vertices[sizeof(Hitbox_Z_Vertices) / sizeof(Hitbox_Z_Vertices[0])]);

												float Target_Origin[3] =
												{
													Bones[Bone_Index][0][0] * Hitbox_Center[0] + Bones[Bone_Index][0][1] * Hitbox_Center[1] + Bones[Bone_Index][0][2] * Hitbox_Center[2] + Bones[Bone_Index][0][3],

													Bones[Bone_Index][1][0] * Hitbox_Center[0] + Bones[Bone_Index][1][1] * Hitbox_Center[1] + Bones[Bone_Index][1][2] * Hitbox_Center[2] + Bones[Bone_Index][1][3],

													Hitbox_Z_Extremes[0][0] + (Hitbox_Z_Extremes[1][0] - Hitbox_Z_Extremes[0][0]) * Interface_Aim_Height.Get_Floating_Point() + Bones[Bone_Index][2][3]
												};

												float Direction[3] =
												{
													Target_Origin[0] - Eye_Position[0],

													Target_Origin[1] - Eye_Position[1],

													Target_Origin[2] - Eye_Position[2]
												};

												if (Trace_Ray(Direction) == 1)
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

															Construct_Type((unsigned __int64)Engine_Module + 601472)(this, Name, Value);
														}
													};
													
													Message_Structure Message;
													
													char Value[2] = { (char)('0' + Target->Valid) };
													
													Message.Construct((char*)"cl_lagcompensation", Value);
													
													using Write_Message_To_Buffer_Type = __int8(**)(void* Message, void* Buffer);
													
													(*Write_Message_To_Buffer_Type(*(unsigned __int64*)&Message + 40))(&Message, (void*)((unsigned __int64)Network_Channel + 88));

													Command->Angles[0] = __builtin_atan2f(-Direction[2], __builtin_hypotf(Direction[0], Direction[1])) * 180.f / 3.1415927f;

													Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180.f / 3.1415927f;

													Command->Buttons |= 1;

													if (Interface_Bruteforce.Get_Integer() == 1)
													{
														if (Player_Data->Priority != -2)
														{
															Recent_Player_Data_Number = *(__int32*)((unsigned __int64)Target->Self + 128);

															Byte_Manager::Copy_Bytes(1, &Previous_Recent_Player_Data, sizeof(Previous_Recent_Player_Data), Player_Data);

															if (Player_Data->Memory_Tolerance == 0)
															{
																if (Player_Data->Tolerance == 0)
																{
																	Player_Data->Shots_Fired = (Player_Data->Shots_Fired + 1) % Bruteforce_Angles_Count;

																	if (Player_Data->Shots_Fired == 0)
																	{
																		Player_Data->Switch_X ^= 1;
																	}

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

													Byte_Manager::Copy_Bytes(1, (float*)((unsigned __int64)Target->Self + 1064), sizeof(Target_Previous_Origin), Target_Previous_Origin);

													Set_Local_Origin_Type((unsigned __int64)Client_Module + 1758400)(Target->Self, (float*)((unsigned __int64)Target->Self + 1064));

													goto Found_Target_Label;
												}
											}
											
											Byte_Manager::Copy_Bytes(1, (float*)((unsigned __int64)Target->Self + 1064), sizeof(Target_Previous_Origin), Target_Previous_Origin);
											
											Set_Local_Origin_Type((unsigned __int64)Client_Module + 1758400)(Target->Self, (float*)((unsigned __int64)Target->Self + 1064));
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
									auto Calculate_Spread = [&](float* Spread) -> void
									{	
										using Random_Seed_Type = void(*)(__int32 Seed);

										static void* Standard_Library_Module = GetModuleHandleW(L"vstdlib.dll");

										Random_Seed_Type((unsigned __int64)Standard_Library_Module + 77536)(Command->Random_Seed & 255);

										float Random[2];

										using Random_Type = float(*)(float Minimum, float Maximum);
										
										void* Interface_Manager = *(void**)((unsigned __int64)Engine_Module + 12887056);

										using Find_Interface_Type = Interface_Structure*(**)(void* Interface_Manager, char* Name);

										static Interface_Structure* Interface_Shot_Bias_Min = (*Find_Interface_Type(*(unsigned __int64*)Interface_Manager + 136))(Interface_Manager, (char*)"ai_shot_bias_min");

										static Interface_Structure* Interface_Shot_Bias_Max = (*Find_Interface_Type(*(unsigned __int64*)Interface_Manager + 136))(Interface_Manager, (char*)"ai_shot_bias_max");

										float Shot_Bias_Min = Interface_Shot_Bias_Min->Get_Floating_Point();
										
										float Shot_Bias_Max = Interface_Shot_Bias_Max->Get_Floating_Point();

										float Shot_Bias = (Shot_Bias_Max - Shot_Bias_Min) + Shot_Bias_Min;

										float Flatness = __builtin_fabsf(Shot_Bias) * 0.5f;

										Calculate_Random_Label:
										{
											Random[0] = Random_Type((unsigned __int64)Standard_Library_Module + 77408)(-1.f, 1.f) * Flatness + Random_Type((unsigned __int64)Standard_Library_Module + 77408)(-1.f, 1.f) * (1.f - Flatness);

											Random[1] = Random_Type((unsigned __int64)Standard_Library_Module + 77408)(-1.f, 1.f) * Flatness + Random_Type((unsigned __int64)Standard_Library_Module + 77408)(-1.f, 1.f) * (1.f - Flatness);

											if (Shot_Bias < 0)
											{
												Random[0] = (Random[0] >= 0.f) ? 1.f - Random[0] : -1.f - Random[0];

												Random[1] = (Random[1] >= 0.f) ? 1.f - Random[1] : -1.f - Random[1];
											}

											if (__builtin_powf(Random[0], 2.f) + __builtin_powf(Random[1], 2.f) > 1.f)
											{
												goto Calculate_Random_Label;
											}
										}

										Spread[0] = 1.f;

										Spread[1] = -Weapon_Spread[0] * Random[0];

										Spread[2] = Weapon_Spread[1] * Random[1];

										Vector_Normalize(Spread);
									};

									float Forward[3];

									Angle_Vectors(Command->Angles, Forward, nullptr, nullptr);

									Command->Command_Number = -98069271;

									Command->Random_Seed = 33;

									float Spread[3];

									Calculate_Spread(Spread);

									float Square_X_Z = 1.f - Spread[1] * Spread[1];

									float Rotation[2];

									if (Forward[2] * Forward[2] > Square_X_Z)
									{
										Rotation[0] = __builtin_sqrtf(Square_X_Z);

										if (Forward[2] < 0.f)
										{
											Rotation[0] = -Rotation[0];
										}

										Rotation[1] = 0.f;
									}
									else
									{
										Rotation[0] = Forward[2];

										Rotation[1] = __builtin_sqrtf(Square_X_Z - Forward[2] * Forward[2]);
									}

									Command->Angles[0] = 180.f - __builtin_atan2f(Rotation[0] * -Spread[0] + Rotation[1] * Spread[2], Rotation[0] * Spread[2] + Rotation[1] * Spread[0]) * 180.f / 3.1415927f - Weapon_Recoil[0];
									
									Command->Angles[1] = 180.f + __builtin_atan2f(Forward[0] * -Spread[1] + Forward[1] * Rotation[1], Forward[0] * Rotation[1] + Forward[1] * Spread[1]) * 180.f / 3.1415927f - Weapon_Recoil[1];

									In_Attack = 1;

									Send_Packet = (Interface_Alternative.Get_Integer() != 0) * 2;

									Shot_Tick = *(__int32*)((unsigned __int64)Local_Player + 11608);

									Shot_Time = Global_Variables->Current_Time;
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

					Byte_Manager::Copy_Bytes(1, &Players_Data[Recent_Player_Data_Number], sizeof(Previous_Recent_Player_Data), &Previous_Recent_Player_Data);

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

		Correct_Movement();

		if (Send_Packet == 0)
		{
			using Send_Datagram_Type = __int32(*)(void* Network_Channel, void* Unknown_Parameter);

			__int32 Sequence_Number = *(__int32*)((unsigned __int64)Network_Channel + 12) = Send_Datagram_Type((unsigned __int64)Engine_Module + 1961712)(Network_Channel, nullptr);

			Sequences[Sequence_Number % 90] =
			{
				Sequence_Number,

				Sequence_Number - Choked_Commands_Count - 1
			};
		}
		else
		{
			Command->Extra_Simulations = max(0, Choked_Commands_Count - 14);

			Byte_Manager::Copy_Bytes(1, Update_Animation_Angles, sizeof(Update_Animation_Angles), Command->Angles);
		}
		
		*(__int8*)((unsigned __int64)Frame_Address + 304) = Send_Packet;
	}

	Original_Copy_Command_Caller.call<void>(Unknown_Parameter, Command);
}

__attribute__((naked)) void Redirected_Copy_Command()
{
	asm("leaq -8(%rsp), %r8");
	asm("jmp %P0" : : "i"(Copy_Command));
}