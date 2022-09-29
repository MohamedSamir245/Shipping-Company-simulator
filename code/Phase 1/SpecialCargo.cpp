#include"SpecialCargo.h"

Time SpecialCargo::LoadUnloadTime;

SpecialCargo::SpecialCargo(int mw,int id, int c, Time L, Time P, float D, float C) :Cargo(mw,id, c, P, D, C)
{
	if (LoadUnloadTime.getDay() == 1 && LoadUnloadTime.getHour() == 0)
		LoadUnloadTime = L;
}
Time SpecialCargo::GetLoadUnloadTime()
{
	return LoadUnloadTime;
}
bool SpecialCargo::Exceeded_MaxW(Time Current_Time)
{
	if ((Current_Time - this->GetpreparationTime()) >= this->GetMaxW())
		return true;
	return false;
}