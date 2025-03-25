__int8 Aim_Heights_Count;

float* Aim_Heights;

void Aim_Set_Heights(Interface_Structure* Interface)
{
	Aim_Heights_Count = 1;

	Aim_Heights = (float*)__builtin_realloc(Aim_Heights, Aim_Heights_Count * sizeof(Aim_Heights));

	Interface = (Interface_Structure*)((unsigned __int32)Interface - 24);

	Aim_Heights[Aim_Heights_Count - 1] = atof(Interface->String);

	char* String = __builtin_strchr(Interface->String, ',');

	Set_Aim_Heights_Label:
	{
		if (String != nullptr)
		{
			Aim_Heights_Count += 1;

			Aim_Heights = (float*)__builtin_realloc(Aim_Heights, Aim_Heights_Count * sizeof(Aim_Heights));

			String = (char*)((unsigned __int32)String + 1);

			Aim_Heights[Aim_Heights_Count - 1] = atof(String);

			String = __builtin_strchr(String, ',');

			goto Set_Aim_Heights_Label;
		}
	}
}