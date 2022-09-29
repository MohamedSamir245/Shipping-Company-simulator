#include "Cargo.h"
#include"NormalCargo.h"
#include"SpecialCargo.h"
#include"VipCargo.h"
using namespace std;


int Cargo::NumtoCheckUp = -1;

Cargo::Cargo(int mw,int id,int n,Time P, float D, float C)
{
	SetMaxW(mw);
	SetpreparationTime(P);
	SetDelieveryDistance(D);
	SetCost(C);
	SetID(id);
	if (NumtoCheckUp == -1)
		NumtoCheckUp = n;
}

void Cargo::SetpreparationTime(Time t)
{
	preparationTime = t;
}

void Cargo::SetDelieveryDistance(float D)
{
	if (D > 0)
		DelieveryDistance = D;
	else
		DelieveryDistance = -1;
}

void Cargo::SetCost(float C)
{
	if (C > 0)
		Cost = C;
	else
		Cost = -1;
}

void Cargo::SetID(int id)
{
	ID = id;
}

void Cargo::SetDeliveryTime(Time t)
{
	if (t > preparationTime)
		DeliveryTime = t;
	else
	{
		Time t1(1, 0);
		DeliveryTime = t1;
	}
}

void Cargo::SetEndLoadingTime(Time t)
{
		EndLoadingTime = t;
}

void Cargo:: SetCase(statue c)
{
	Case = c;
}

void Cargo::SetType(type t)
{
	Type = t;
}

void Cargo::SetMaxW(int mw)
{
	MaxW = mw;
}

Time Cargo::GetpreparationTime()
{
	return preparationTime;
}

float Cargo::GetDelieveryDistance()
{
	return DelieveryDistance;
}

float Cargo::GetCost() 
{
	return Cost;
}

int Cargo::GetID()
{
	return ID;
}

Time Cargo::GetDeliveryTime()
{
	return DeliveryTime;
}

Time Cargo::GetEndLoadingTime()
{
	return EndLoadingTime;
}

statue Cargo::GetCase()
{
	return Case;
}

type Cargo::GetType()
{
	return Type;
}

int Cargo::GetMaxW()
{
	return MaxW;
}

bool Cargo::operator<(const Cargo& C)
{
	switch (Case)
	{

	case Waiting:
	{
		if (this->preparationTime > C.preparationTime)
			return false;
		return true;
	}

	case Moving:
	{
		if (this->EndLoadingTime > C.EndLoadingTime)
			return false; 
		return true;
	}

	case Delivered:
	{
		//doesn't matter
		if (this->DeliveryTime > C.DeliveryTime)
			return false;
		return true;
	}

	}
	
}

bool Cargo::operator==(const Cargo& C)
{
	if (this->ID == C.ID)
		return true;
	return false;
}
void Cargo::SetCarryingTruck(Truck* cT)
{
	carryingTruck = cT;
}

Truck* Cargo::GetCarryingTruck()
{
	return carryingTruck;
}


Time Cargo::GetLoadUnloadTime()
{
	
	switch (this->GetType())
	{
	case Normal:return NormalCargo::GetLoadUnloadTime();
	case Special:return SpecialCargo::GetLoadUnloadTime();
	case Vip:return VipCargo::GetLoadUnloadTime();
	}
}

void Cargo::setStartLoadingTime (Time t)
{
	StartLoadingTime=t;
}

Time Cargo::getStartLoadingTime()
{
	return StartLoadingTime;
}

void Cargo::setMoveTime ( Time t )
{
	MoveTime = t;
}

Time Cargo::getMoveTime ( )
{
	return MoveTime;
}

