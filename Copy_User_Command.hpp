struct User_Command_Structure
{
	__int8 Additional_Bytes_1[4];

	__int32 Command_Number;

	__int32 Tick_Number;

	float Angles[3];

	float Move[3];

	__int32 Buttons;

	__int8 Additional_Bytes_2[9];

	__int32 Random_Seed;
};

Player_Data_Structure Previous_Recent_Player_Data;

void* Original_Copy_User_Command_Caller_Location;

void __thiscall Redirected_Copy_User_Command(void* Unknown_Parameter, User_Command_Structure* User_Command)
{
	void* Local_Player = *(void**)607867332;

	if (*(__int8*)((unsigned __int32)Local_Player + 135) == 0)
	{
		void* Prediction = *(void**)540494880;

		if (*(__int32*)541926608 != 1)
		{
			using Update_Type = void(__thiscall*)(void* Prediction, __int8 Unknown_Parameter_1, __int8 Unknown_Parameter_2, void* Unknown_Parameter_3, __int32 Unknown_Parameter_4);

			Update_Type(605209712)(Prediction, 1, 1, *(void**)540627876, *(__int32*)540627868 + *(__int32*)540627872);
		}

		auto Angle_Vectors = [](float* Angles, float* Forward, float* Right, float* Up) -> void
		{
			using Angle_Vectors_Type = void(__cdecl*)(float* Angles, float* Forward, float* Right, float* Up);

			Angle_Vectors_Type(606384752)(Angles, Forward, Right, Up);
		};

		float Move_Angles[3] =
		{
			User_Command->Angles[0],

			User_Command->Angles[1],

			0
		};

		static float Previous_Move_Angle_Y;

		if ((User_Command->Buttons & 2) == 2)
		{
			User_Command->Move[0] = 0;

			if (*(__int32*)((unsigned __int32)Local_Player + 456) == -1)
			{
				User_Command->Buttons &= ~(*(__int32*)((unsigned __int32)Local_Player + 308) & 2);
			}
			else
			{
				User_Command->Buttons &= ~(*(__int32*)((unsigned __int32)Local_Player + 3420) & 2);
			}

			float Difference = __builtin_remainderf(Move_Angles[1] - Previous_Move_Angle_Y, 360);

			Previous_Move_Angle_Y = Move_Angles[1];

			float* Velocity = (float*)((unsigned __int32)Local_Player + 224);

			if (__builtin_fabsf(Difference) < __builtin_atan2f(30, __builtin_hypotf(Velocity[0], Velocity[1])) * 180 / 3.1415927f)
			{
				float Strafe_Angle = __builtin_remainderf(Move_Angles[1] - __builtin_atan2f(Velocity[1], Velocity[0]) * 180 / 3.1415927f, 360);

				if (__builtin_signbitf(Strafe_Angle) == 0)
				{
					User_Command->Move[1] = -400;
				}
				else
				{
					User_Command->Move[1] = 400;
				}

				Move_Angles[1] -= Strafe_Angle;
			}
			else
			{
				if (__builtin_signbitf(Difference) == 0)
				{
					User_Command->Move[1] = -400;
				}
				else
				{
					User_Command->Move[1] = 400;
				}
			}
		}
		else
		{
			Previous_Move_Angle_Y = Move_Angles[1];
		}

		float Previous_Move[2] =
		{
			User_Command->Move[0],

			User_Command->Move[1]
		};

		float Desired_Move_Forward[3];

		float Desired_Move_Right[3];

		Angle_Vectors(Move_Angles, Desired_Move_Forward, Desired_Move_Right, nullptr);

		Desired_Move_Forward[2] = 0;

		auto Vector_Normalize = [](float* Vector) -> float
		{
			using Vector_Normalize_Type = float(__thiscall*)(float* Vector);

			return Vector_Normalize_Type(606378096)(Vector);
		};

		Vector_Normalize(Desired_Move_Forward);

		Desired_Move_Right[2] = 0;

		Vector_Normalize(Desired_Move_Right);

		float Desired_Move[2] =
		{
			Desired_Move_Forward[0] * User_Command->Move[0] + Desired_Move_Right[0] * User_Command->Move[1],

			Desired_Move_Forward[1] * User_Command->Move[0] + Desired_Move_Right[1] * User_Command->Move[1]
		};

		auto Correct_Movement = [&]() -> void
		{
			float Move_Forward[3];

			float Move_Right[3];

			Angle_Vectors(User_Command->Angles, Move_Forward, Move_Right, nullptr);

			Move_Forward[2] = 0;

			Vector_Normalize(Move_Forward);

			Move_Right[2] = 0;

			Vector_Normalize(Move_Right);

			float Divider = Move_Forward[0] * Move_Right[1] - Move_Right[0] * Move_Forward[1];

			User_Command->Move[0] = (__int16)((Desired_Move[0] * Move_Right[1] - Move_Right[0] * Desired_Move[1]) / Divider);

			User_Command->Move[1] = (__int16)((Move_Forward[0] * Desired_Move[1] - Desired_Move[0] * Move_Forward[1]) / Divider);
		};

		Correct_Movement();

		void* Previous_Audio_Device = *(void**)542589456;

		*(void**)542589456 = nullptr;

		float Local_Player_Previous_Origin[3];

		float* Local_Player_Origin = (float*)((unsigned __int32)Local_Player + 668);

		if (Interface_Alternative.Integer == 0)
		{
			Byte_Manager::Copy_Bytes(0, Local_Player_Previous_Origin, sizeof(Local_Player_Previous_Origin), Local_Player_Origin);
		}

		float Previous_Friction = *(float*)((unsigned __int32)Local_Player + 3936);

		using Run_Command_Type = void(__thiscall*)(void* Prediction, void* Local_Player, User_Command_Structure* User_Command, void* Move_Helper);

		Run_Command_Type(605207600)(Prediction, Local_Player, User_Command, (void*)607735532);

		*(void**)542589456 = Previous_Audio_Device;

		*(float*)((unsigned __int32)Local_Player + 3936) = Previous_Friction;

		User_Command->Move[0] = Previous_Move[0];

		User_Command->Move[1] = Previous_Move[1];

		static __int8 Send_Packet;

		__int32 Choked_Commands_Count = *(__int32*)540627872;

		__int8 Predicted_Send_Packet = 0;

		static float Networked_Origin[3];

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
					if (__builtin_powf(Networked_Origin[0] - Local_Player_Previous_Origin[0], 2) + __builtin_powf(Networked_Origin[1] - Local_Player_Previous_Origin[1], 2) + __builtin_powf(Networked_Origin[2] - Local_Player_Previous_Origin[2], 2) <= 4096)
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
								if (__builtin_powf(Networked_Origin[0] - Local_Player_Origin[0], 2) + __builtin_powf(Networked_Origin[1] - Local_Player_Origin[1], 2) + __builtin_powf(Networked_Origin[2] - Local_Player_Origin[2], 2) > 4096)
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
					if (__builtin_powf(Networked_Origin[0] - Local_Player_Origin[0], 2) + __builtin_powf(Networked_Origin[1] - Local_Player_Origin[1], 2) + __builtin_powf(Networked_Origin[2] - Local_Player_Origin[2], 2) <= 4096)
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

		__int32 Team_Number = *(__int32*)((unsigned __int32)Local_Player + 144);

		using Get_Latency_Type = float(__thiscall*)(void* Network_Channel, __int32 Type);

		void* Network_Channel = *(void**)540608912;

		float Total_Latency = Get_Latency_Type(537919008)(Network_Channel, 0) + Get_Latency_Type(537919008)(Network_Channel, 1);

		float Interpolation_Time = max(*(float*)541928632, std::clamp(*(float*)607906336, *(float*)542242312, *(float*)542242072) / std::clamp(*(__int32*)540495212, *(__int32*)542221268, *(__int32*)542221412));

		float Corrected_Total_Latency = std::clamp(Total_Latency + Interpolation_Time, 0.f, 1.f);

		Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)607726732;

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
				void* Entity = *(void**)((unsigned __int32)607973860 + ((Entity_Number - 4097) << 4));

				if (Entity != nullptr)
				{
					if (*(__int8*)((unsigned __int32)Entity + 135) == 0)
					{
						if (*(__int32*)((unsigned __int32)Entity + 144) != Team_Number)
						{
							if (*(__int8*)((unsigned __int32)Entity + 320) == 0)
							{
								__int32 Tick_Number = (*(float*)((unsigned __int32)Entity + 104) + Interpolation_Time) / Global_Variables->Interval_Per_Tick + 0.5f;

								float* Entity_Origin = (float*)((unsigned __int32)Entity + 668);

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

		if (__builtin_fabsf(Global_Variables->Current_Time - Shot_Time) > 0.5f)
		{
			if (Shot_Time == 0)
			{
				Passed_Shot_Time_Check_Label:
				{
					if ((User_Command->Buttons & 2048) == 0)
					{
						__int8 Send_Packet_Sequence = (Send_Packet == 0) + (Predicted_Send_Packet == 1);

						if (Interface_Alternative.Integer != 0)
						{
							Send_Packet_Sequence = 2;
						}

						if (Send_Packet_Sequence == 2)
						{
							if (*(float*)((unsigned __int32)Local_Player + 2544) <= Global_Variables->Current_Time)
							{
								void* Weapon = *(void**)((unsigned __int32)607973860 + (((*(unsigned __int32*)((unsigned __int32)Local_Player + 2872) & 4095) - 4097) << 4));

								if (Weapon != nullptr)
								{
									if (*(__int32*)((unsigned __int32)Weapon + 1780) != -1)
									{
										if (*(__int32*)((unsigned __int32)Weapon + 1788) > 0)
										{
											if (*(float*)((unsigned __int32)Weapon + 1720) <= Global_Variables->Current_Time)
											{
												size_t Target_Number = 0;

												using Get_Eye_Position_Type = void(__thiscall*)(void* Player, float* Eye_Position);

												float Eye_Position[3];

												Get_Eye_Position_Type(604058320)(Local_Player, Eye_Position);

												using Get_Weapon_Information_Type = void*(__thiscall*)(void* Weapon);

												float Weapon_Range = *(float*)((unsigned __int32)Get_Weapon_Information_Type(604037872)(Weapon) + 2020);

												Recent_Player_Data_Number = 0;

												Traverse_Sorted_Target_List_Label:
												{
													if (Target_Number != Sorted_Target_List.size())
													{
														Target_Structure* Target = &Sorted_Target_List.at(Target_Number);

														if (Target->Valid == 1)
														{
															Redirected_Compute_Torso_Rotation((void*)(*(unsigned __int32*)((unsigned __int32)Target->Self + 3968) - 148));

															using Setup_Bones_Type = __int8(__thiscall*)(void* Entity, void* Bones, __int32 Maximum_Bones, __int32 Mask, float Current_Time);

															float Bones[128][3][4];

															if (Setup_Bones_Type(604209888)((void*)((unsigned __int32)Target->Self + 4), Bones, 128, 524032, Global_Variables->Current_Time) == 1)
															{
																auto Trace_Ray = [&](float Direction[3]) -> __int8
																{
																	struct alignas(4) Ray_Structure
																	{
																		__int8 Additional_Bytes[50];
																	};

																	struct Filter_Structure
																	{
																		void* Table;

																		void* Skip;

																		__int32 Group;
																	};

																	struct Trace_Structure
																	{
																		__int8 Additional_Bytes_1[68];

																		__int32 Group;

																		__int8 Additional_Bytes_2[4];

																		void* Entity;

																		__int8 Additional_Bytes_3[4];
																	};

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

																	Initialize_Ray_Type(537380224)(&Ray, Eye_Position, End);

																	Filter_Structure Filter;

																	Filter.Table = (void*)607282692;

																	Filter.Skip = Local_Player;

																	Filter.Group = 0;

																	Trace_Structure Trace;

																	Trace_Ray_Type(537565888)((void*)540446304, &Ray, 1174421515, &Filter, &Trace);

																	using Clip_Trace_To_Players_Type = void(__cdecl*)(float* Start, float* End, __int32 Mask, Filter_Structure* Filter, Trace_Structure* Trace);

																	End[0] += Direction[0] * 40;

																	End[1] += Direction[1] * 40;

																	End[2] += Direction[2] * 40;

																	Clip_Trace_To_Players_Type(605426672)(Eye_Position, End, 1174421515, &Filter, &Trace);

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

																using Get_Studio_Header_Type = void*(__thiscall*)(void* Entity);

																void* Studio_Header = *(void**)Get_Studio_Header_Type(604188448)(Target->Self);

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
																	User_Command->Tick_Number = Target->Tick_Number;

																	User_Command->Angles[0] = __builtin_atan2f(-Direction[2], __builtin_hypotf(Direction[0], Direction[1])) * 180 / 3.1415927f;

																	User_Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180 / 3.1415927f;

																	User_Command->Buttons |= 1;

																	if (Interface_Bruteforce.Integer == 1)
																	{
																		__int32 Target_Number = *(__int32*)((unsigned __int32)Target->Self + 80);

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

												if ((User_Command->Buttons & 1) == 1)
												{
													float Rotations[2][3][3];

													unsigned __int8 Calculation_Number = 0;

													float Forward[3];

													float Right[3];

													float Up[3];

													Angle_Vectors(User_Command->Angles, Forward, Right, Up);

													User_Command->Command_Number = -2076434770;

													User_Command->Random_Seed = 32;

													using Random_Seed_Type = void(__cdecl*)(__int32 Seed);

													static void* Random_Seed_Location = (void*)((unsigned __int32)GetModuleHandleW(L"vstdlib.dll") + 11856);

													Random_Seed_Type((unsigned __int32)Random_Seed_Location)((User_Command->Random_Seed & 255) + 1);

													using Random_Float_Type = float(__cdecl*)(float Minimum, float Maximum);

													static void* Random_Float_Location = (void*)((unsigned __int32)GetModuleHandleW(L"vstdlib.dll") + 11872);

													float Random_X = Random_Float_Type(Random_Float_Location)(-0.5f, 0.5f) + Random_Float_Type(Random_Float_Location)(-0.5f, 0.5f);

													Weapon_Spread = -1;

													using Primary_Attack_Type = void(__thiscall**)(void* Weapon);

													(*Primary_Attack_Type(*(unsigned __int32*)Weapon + 856))(Weapon);

													float Random_Y = Random_Float_Type(Random_Float_Location)(-0.5f, 0.5f) + Random_Float_Type(Random_Float_Location)(-0.5f, 0.5f);

													float Directions[2][3] =
													{
														{
															Forward[0],

															Forward[1],

															Forward[2]
														},

														{
															Forward[0] + Random_X * Weapon_Spread * Right[0] + Random_Y * Weapon_Spread * Up[0],

															Forward[1] + Random_X * Weapon_Spread * Right[1] + Random_Y * Weapon_Spread * Up[1],

															Forward[2] + Random_X * Weapon_Spread * Right[2] + Random_Y * Weapon_Spread * Up[2]
														}
													};

													Weapon_Spread = 0;

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

													float* Recoil = (float*)((unsigned __int32)Local_Player + 2992);

													User_Command->Angles[0] = 180 - __builtin_atan2f(-Rotated_Forward[2], __builtin_hypotf(Rotated_Forward[0], Rotated_Forward[1])) * 180 / 3.1415927f - Recoil[0] * 2;

													User_Command->Angles[1] = 180 + __builtin_atan2f(Rotated_Forward[1], Rotated_Forward[0]) * 180 / 3.1415927f - Recoil[1] * 2;

													float Rotated_Up[3] =
													{
														Up[0] * Rotation[0][0] + Up[1] * Rotation[0][1] + Up[2] * Rotation[0][2],

														Up[0] * Rotation[1][0] + Up[1] * Rotation[1][1] + Up[2] * Rotation[1][2],

														Up[0] * Rotation[2][0] + Up[1] * Rotation[2][1] + Up[2] * Rotation[2][2]
													};

													User_Command->Angles[2] = 180 + __builtin_atan2f(Rotated_Forward[1] * Rotated_Up[0] - Rotated_Forward[0] * Rotated_Up[1], Rotated_Forward[0] * (Rotated_Forward[0] * Rotated_Up[2] - Rotated_Forward[2] * Rotated_Up[0]) - Rotated_Forward[1] * (Rotated_Forward[2] * Rotated_Up[1] - Rotated_Forward[1] * Rotated_Up[2])) * 180 / 3.1415927f - Recoil[2] * 2;

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

		User_Command->Buttons &= ~2048;

		if (In_Attack == 0)
		{
			User_Command->Buttons &= ~1;

			if (Sorted_Target_List.size() != 0)
			{
				User_Command->Angles[0] = Interface_Angle_X.Floating_Point;

				float* Target_Origin = (float*)((unsigned __int32)Sorted_Target_List.at(0).Self + 668);

				float Direction[2] =
				{
					Target_Origin[0] - Local_Player_Origin[0],

					Target_Origin[1] - Local_Player_Origin[1]
				};

				if (Send_Packet == 0)
				{
					if ((User_Command->Command_Number % 2) == 0)
					{
						User_Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180 / 3.1415927f + Interface_First_Choked_Angle_Y.Floating_Point;
					}
					else
					{
						User_Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180 / 3.1415927f + Interface_Second_Choked_Angle_Y.Floating_Point;
					}
				}
				else
				{
					User_Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180 / 3.1415927f + Interface_Angle_Y.Floating_Point;
				}
			}
		}

		Correct_Movement();

		auto Compress_Angle = [](float Value, __int32 Shift) -> float
		{
			return ((__int32)(Value / 360 * Shift) & Shift - 1) * (360 / (float)Shift);
		};

		User_Command->Angles[0] = Compress_Angle(User_Command->Angles[0], 65536);

		User_Command->Angles[1] = Compress_Angle(User_Command->Angles[1], 65536);

		User_Command->Angles[2] = Compress_Angle(User_Command->Angles[2], 256);

		if (Send_Packet != 0)
		{
			Byte_Manager::Copy_Bytes(0, Update_Animation_Angles, sizeof(Update_Animation_Angles), User_Command->Angles);
		}

		*(__int8*)((unsigned __int32)__builtin_frame_address(0) + 24) = Send_Packet;
	}

	(decltype(&Redirected_Copy_User_Command)(Original_Copy_User_Command_Caller_Location))(Unknown_Parameter, User_Command);
}