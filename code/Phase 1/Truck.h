#pragma once
#include"Time.h"
#include"PQueue.h"

class Truck
{
	float Truck_Capacity;
	Time Delivery_Interval;
	int ID;
	static int NoJourneys;
	int CurrentNoJourneys;
	Time DeliveryTime;
	Time EndLoadingTime;
	Time EndTripTime;
	//statue Case;
	PQueue<Cargo*, float> CargosInTruck;

	char Shift;

	int tDC;
	int tNJ;
	Time tAT;   //  enddelivering time - endloading time   

	Time movingTime;
	Time startloadingTime;
	float Speed;
	float priority;
	bool fail;

public:

	Truck ( float TC = 0, int id = 0, int NJ = 0, Time DI = 0 , float S = 0);
	void AddCargo(Cargo* ,Time ); 
	void SetTruckCapicity ( float TC );
    void SetDeliveryInterval ( Time DI );
    float GetTruckCapicity ( ) const;
	Time GetDeliveryInterval ( )const;
	bool operator < ( Truck t );
	bool operator <= ( Truck t );
	bool operator == ( Truck t );
	void SetNoJourneys(int n);
	int GetNoJourneys() const;
	void SetId(int id);
	int GetId();
	Time GetDeliveryTime();
	Time GetEndLoadingTime();

	void SetDeliveryTime(Time t);
	void SetEndLoadingTime(Time t);

	PQueue<Cargo*, float>* GetCargosInTruck();

	int GetCurrentNoJourneys();
	void SetCurrentNoJourneys(int);

	void SetEndTripTime(Time);
	Time GetEndTripTime();

	float getUtilization ( Time currentSimulationTime );

	void increaseActiveTime ( Time t );
	Time getActiveTime ( );

	void increasetDC ( int x );
	void increasetNJ ( int x );

	void setMovingTime ( Time t );
	Time getMovingTime ( );

	void setStartLoadingTime ( Time t );
	Time getStartLoadingTime ( );


	void SetSpeed ( float S );
	float GetSpeed ( )const;

	void SetPriority (float x );
	float GetPriority ( );

	void SetShift(char s);
	char GetShift();

	bool Getfail();

	void randomfail();

};

