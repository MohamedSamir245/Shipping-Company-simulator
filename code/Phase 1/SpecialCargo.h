#pragma once
#include "Cargo.h"
class SpecialCargo : public Cargo
{
	static 	Time LoadUnloadTime;

public:

	SpecialCargo(int mw,int id, int c, Time L, Time P = 0, float D = -1, float C = -1);
	static  Time GetLoadUnloadTime();
	bool Exceeded_MaxW(Time Current_Time);

};

