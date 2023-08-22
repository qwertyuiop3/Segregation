float Update_Animation_Angles[2];

void* Original_Update_Animation_Caller;

void __thiscall Redirected_Update_Animation(void* Player)
{
    if (Player == *(void**)607867332)
    {
        *(float*)((unsigned __int32)Player + 4124) = Update_Animation_Angles[0];

        *(float*)((unsigned __int32)Player + 4128) = Update_Animation_Angles[1];
    }

    (decltype(&Redirected_Update_Animation)(Original_Update_Animation_Caller))(Player);
}