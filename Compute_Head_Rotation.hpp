void* Original_Compute_Head_Rotation_Caller_Location;

void __thiscall Redirected_Compute_Head_Rotation(void* Animation_State, void* Studio_Header)
{
	if (Interface_Bruteforce.Integer == 1)
	{
		void* Entity = *(void**)((unsigned __int32)Animation_State + 20);

		if (Entity != *(void**)((unsigned __int32)Client_Module_Location + 5015784))
		{
			if (*(void**)Entity == (void*)((unsigned __int32)Client_Module_Location + 3952404))
			{
				Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int32)Entity + 84)];

				if (Player_Data->Priority != -2)
				{
					if (*(float*)((unsigned __int32)Animation_State + 28) == -179.91206f)
					{
						*(float*)((unsigned __int32)Animation_State + 28) = Player_Data->Switch_X == 0 ? 90 : -90;
					}
				}
			}
		}
	}

	(decltype(&Redirected_Compute_Head_Rotation)(Original_Compute_Head_Rotation_Caller_Location))(Animation_State, Studio_Header);
}