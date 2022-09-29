#include"VipCargo.h"

Time VipCargo::LoadUnloadTime;

VipCargo::VipCargo(int mw,int id, int c,float pr, Time L, Time P, float D, float C) :Cargo(mw,id, c, P, D, C)
{
	if (LoadUnloadTime.getDay() == 1 && LoadUnloadTime.getHour() == 0)
		LoadUnloadTime = L;
	SetPriority(pr);
	Promoted = false;

}
Time VipCargo::GetLoadUnloadTime()
{
	return LoadUnloadTime;
}

void VipCargo::SetPriority(float p)
{
	Priority = p;
}

float VipCargo::GetPriority()
{
	return Priority;
}

bool VipCargo::Exceeded_MaxW(Time Current_Time)
{
	if ((Current_Time - this->GetpreparationTime()) >= this->GetMaxW())
		return true;
	return false;
}

bool VipCargo::isPromoted ( )
{
	return Promoted;
}