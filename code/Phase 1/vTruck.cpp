#include "vTruck.h"

int vTruck::Checkup_Duration = 0;


vTruck::vTruck ( float TC, int id, int NJ, Time DI, float S,int D ) :Truck ( TC, id, NJ, DI ,S )
{
	
	
	if (Checkup_Duration == 0)
		Checkup_Duration = D;
}


void vTruck::SetEndCheckupTime ( Time CH_Time )
{
	End_Checkup_Time = CH_Time;
}

Time vTruck::GetEndCheckupTime ( ) const
{
	return End_Checkup_Time;
}


void vTruck::SetCheckupDuration(int n)
{
	Checkup_Duration = n;
}

int vTruck::GetCheckupDuration() const
{
	return Checkup_Duration;
}

void vTruck::setcdtforcargos(Time t)
{
	if (GetCargosInTruck()->isEmpty())
		return;

	Cargo* tcargo;
	Cargo* ttcargo;

	PQueue<Cargo*, float> tempCargosInTruck;
	tempCargosInTruck.setPriorityOrder(false);//ascending
	PQueue<Cargo*, float> tempCargosInTruck2;//descending

	Time temp;

	//first cargo
	GetCargosInTruck()->pop(tcargo);
	temp = t;
	temp = temp + ceil(tcargo->GetDelieveryDistance() / (float)GetSpeed());
	temp = temp + tcargo->GetLoadUnloadTime().getHour();
	tcargo->setMoveTime ( t );

	tcargo->SetDeliveryTime(temp);
	tempCargosInTruck.push(tcargo, tcargo->GetDelieveryDistance());


	while (!GetCargosInTruck()->isEmpty())
	{
		tempCargosInTruck.peek(ttcargo);

		GetCargosInTruck()->pop(tcargo);

		temp = temp + tcargo->GetLoadUnloadTime().getHour();


		temp = temp + ceil((tcargo->GetDelieveryDistance() - ttcargo->GetDelieveryDistance()) / (float)GetSpeed());

		tcargo->setMoveTime ( t );

		tcargo->SetDeliveryTime(temp);
		tempCargosInTruck.push(tcargo, tcargo->GetDelieveryDistance());
	}
	while (!tempCargosInTruck.isEmpty())
	{
		tempCargosInTruck.pop(tcargo);
		tempCargosInTruck2.push(tcargo, tcargo->GetDelieveryDistance());
		GetCargosInTruck()->push(tcargo, tcargo->GetDelieveryDistance());
	}
	this->SetDeliveryTime(temp);



	tempCargosInTruck2.peek(tcargo);
	Time tt;
	tt.setHour(ceil(tcargo->GetDelieveryDistance() / (float)GetSpeed()));
	tt.setDay(0);
	this->SetDeliveryInterval(tt);
	temp = temp + this->GetDeliveryInterval();

	this->SetEndTripTime(temp);
}