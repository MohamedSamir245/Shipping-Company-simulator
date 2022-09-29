#include "Truck.h"
#include<ctime>
#include<random>

int Truck::NoJourneys = 0;
Truck::Truck(float TC, int id, int NJ, Time DI, float S)
{
	Truck_Capacity = TC;
	ID = id;
	NoJourneys = NJ;
	CurrentNoJourneys = 0;
	Delivery_Interval = DI;
	CargosInTruck.setPriorityOrder(false);
	movingTime.setTime(0, 0);
	tAT.setTime(0, 0);
	startloadingTime.setTime(0, 0);
	tDC = 0;
	tNJ = 0;
	fail = false;
}

void Truck::AddCargo(Cargo* c, Time t)
{
	for (int i = 0; i < GetCargosInTruck()->getcounter(); i++)
	{
		t = t + c->GetLoadUnloadTime();

	}

	t = t + c->GetLoadUnloadTime();

	c->SetEndLoadingTime(t);
	this->SetEndLoadingTime(t);
	GetCargosInTruck()->push(c, c->GetDelieveryDistance());
}

void Truck::SetTruckCapicity(float TC)
{
	if (TC >= 0)
		Truck_Capacity = TC;
	else
		Truck_Capacity = 0;
}

void Truck::SetDeliveryInterval(Time DI)
{
	Delivery_Interval = DI;
}

float Truck::GetTruckCapicity() const
{
	return Truck_Capacity;
}


Time Truck::GetDeliveryInterval() const
{
	return Delivery_Interval;
}

bool Truck::operator<(Truck t)
{
	if (this->Truck_Capacity < t.Truck_Capacity)
		return true;
	else
		return false;

}

bool Truck::operator<=(Truck t)
{
	if (this->Truck_Capacity <= t.Truck_Capacity)
		return true;
	else
		return false;
}

bool Truck::operator==(Truck t)
{
	if (this->Truck_Capacity == t.Truck_Capacity)
		return true;
	else
		return false;
}

void Truck::SetNoJourneys(int n)
{
	NoJourneys = n;
}

int Truck::GetNoJourneys() const
{
	return NoJourneys;
}


void Truck::SetId(int id)
{
	ID = id;
}

int Truck::GetId()
{
	return ID;
}

Time Truck::GetDeliveryTime()
{
	return DeliveryTime;
}

Time Truck::GetEndLoadingTime()
{
	return EndLoadingTime;
}


void Truck::SetDeliveryTime(Time t)
{
	DeliveryTime = t;
}

void Truck::SetEndLoadingTime(Time t)
{
	EndLoadingTime = t;
}


PQueue<Cargo*, float>* Truck::GetCargosInTruck()
{
	return &CargosInTruck;
}

int Truck::GetCurrentNoJourneys()
{
	return CurrentNoJourneys;
}

void Truck::SetCurrentNoJourneys(int c)
{
	CurrentNoJourneys = c;
}

void Truck::SetEndTripTime(Time t)
{
	EndTripTime = t;
}

Time Truck::GetEndTripTime()
{
	return EndTripTime;
}


float Truck::getUtilization(Time currentSimulationTime)
{
	if (tNJ == 0 || (currentSimulationTime.getDay() == 0 && currentSimulationTime.getHour() == 0))
		return 0;
	else
		return (float(tDC) / (Truck_Capacity * tNJ) * ((tAT.getDay() * 24.0 + tAT.getHour()) / (currentSimulationTime.getDay() * 24.0 + currentSimulationTime.getHour())));
}

void Truck::increaseActiveTime(Time t)
{
	tAT = tAT + t;
}

Time Truck::getActiveTime()
{
	return tAT;
}

void Truck::increasetDC(int x)
{
	tDC = tDC + x;
}

void Truck::increasetNJ(int x)
{
	tNJ = tNJ + x;
}

void Truck::setMovingTime(Time t)
{
	movingTime = t;
}

Time Truck::getMovingTime()
{
	return movingTime;
}

void Truck::setStartLoadingTime(Time t)
{
	startloadingTime = t;
}

Time Truck::getStartLoadingTime()
{
	return startloadingTime;
}

void Truck::SetSpeed(float S)
{
	if (S >= 0)
		Speed = S;
	else
		Speed = 0;
}

float Truck::GetSpeed() const
{
	return Speed;
}

void Truck::SetPriority(float x)
{
	priority = x;
}

float Truck::GetPriority()
{
	return priority;
}

void Truck::SetShift(char s)
{
	Shift = s;
}

char Truck::GetShift()
{
	return Shift;
}

bool Truck::Getfail()
{
	return fail;
}

void Truck::randomfail()
{
	int num;

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 100);

	num = dist6(rng);
	if (num <= 3)
		fail = true;
	else
		fail = false;
}