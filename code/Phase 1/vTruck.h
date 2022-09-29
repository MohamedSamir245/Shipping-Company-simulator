#pragma once
#include "Truck.h"
class vTruck :
    public Truck
{
    Time End_Checkup_Time;
    static int Checkup_Duration;


public:

    vTruck ( float TC = 0, int id = 0, int NJ = 0, Time DI = 0, float S = 0, int D=0 );
    void SetEndCheckupTime ( Time CH_Time );
    Time GetEndCheckupTime ( ) const;
    void SetCheckupDuration(int n);
    int GetCheckupDuration()const;

    void setcdtforcargos(Time);

};

