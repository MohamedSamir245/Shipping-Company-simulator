#pragma once
#include "Cargo.h"
class NormalCargo: public Cargo
{
	static int AutoP;
	static 	Time LoadUnloadTime;

public:

	NormalCargo(int autop,int mw,int id, int c, Time L, Time P = 0, float D = -1, float C = -1);
	static  Time GetLoadUnloadTime();
	bool Exceeded_MaxW(Time Current_Time);
	bool Exceeded_Autop(Time Current_Time);

};

