#pragma once
#include "Cargo.h"
class VipCargo : public Cargo
{
	static 	Time LoadUnloadTime;
	float Priority;
	bool Promoted;

public:

	VipCargo(int mw,int id, int c,float pr, Time L, Time P = 0, float D = -1, float C = -1);
	static  Time GetLoadUnloadTime();
	void SetPriority(float);
	float GetPriority();
	bool Exceeded_MaxW(Time Current_Time);
	bool isPromoted ( );

};

