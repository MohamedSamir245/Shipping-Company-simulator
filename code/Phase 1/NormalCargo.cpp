#include"NormalCargo.h"

Time NormalCargo::LoadUnloadTime;
int NormalCargo::AutoP;

NormalCargo::NormalCargo(int autop,int mw,int id, int c, Time L, Time P, float D, float C) :Cargo(mw,id, c, P, D, C)
{
	AutoP = autop;
	if (LoadUnloadTime.getDay() == 1&&LoadUnloadTime.getHour()==0)
		LoadUnloadTime = L;
}
Time NormalCargo::GetLoadUnloadTime()
{
	return LoadUnloadTime;
}
bool NormalCargo::Exceeded_MaxW(Time Current_Time)
{
	if ((Current_Time - this->GetpreparationTime()) >= this->GetMaxW())
		return true;
	return false;
}

bool NormalCargo::Exceeded_Autop(Time Current_Time)
{
	Time temp(AutoP, 0);
	if ( (Current_Time - this->GetpreparationTime ( )).getDay ( ) >= AutoP )
		return true;
	return false;
}
