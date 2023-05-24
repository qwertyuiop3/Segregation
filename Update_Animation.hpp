float Update_Animation_Angles[2];

void* Original_Update_Animation_Caller_Location;

void __thiscall Redirected_Update_Animation(void* Player)
{
    if (Player == *(void**)((unsigned __int32)Client_Module_Location + 5015784))
    {
        *(float*)((unsigned __int32)Player + 5276) = Update_Animation_Angles[0];

        *(float*)((unsigned __int32)Player + 5280) = Update_Animation_Angles[1];
    }
    else
    {
        if (*(float*)((unsigned __int32)Player + 5276) == 180.087936f)
        {
            *(float*)((unsigned __int32)Player + 5276) = 90;
        }
    }

    (decltype(&Redirected_Update_Animation)(Original_Update_Animation_Caller_Location))(Player);
}