#pragma once
#include"Time.h"
#include<iostream>
using namespace std;
class Truck;
enum statue {Waiting,Loading,Moving,Delivered};
enum type {Normal,Special,Vip};
class Cargo
{
	Time preparationTime;
	float DelieveryDistance;
	float Cost;
	static int NumtoCheckUp ;
	int ID;
	int MaxW;
	statue Case;
	type Type;
	Time DeliveryTime;
	Time EndLoadingTime;
	Truck* carryingTruck;

	Time StartLoadingTime;

	Time MoveTime;

public:

	Cargo(int mw = -1, int id = -1, int n = -1, Time P = 0, float D = -1, float C = -1);
	void SetpreparationTime(Time P);
	void SetDelieveryDistance(float D);
	void SetCost(float D);
	void SetID(int id);
	void SetDeliveryTime(Time t);
	void SetEndLoadingTime(Time);
	void SetCase(statue c);
	void SetType(type);
	void SetMaxW(int mw);
	Time GetpreparationTime();
	float GetDelieveryDistance();
	float GetCost();
	int GetID();
	Time GetDeliveryTime();
	Time GetEndLoadingTime();
	statue GetCase();
	type GetType();
	int GetMaxW();
	bool operator<( const Cargo& C);
	bool operator==(const Cargo& C);
	void SetCarryingTruck(Truck* cT);
	Truck* GetCarryingTruck();
	virtual Time GetLoadUnloadTime();
	
	void setStartLoadingTime(Time t);
	Time getStartLoadingTime();

	void setMoveTime ( Time t );
	Time getMoveTime ( );




};




