#include "Company.h"


Company::Company ( )
{
	openenig_time = 5;
	closing_time = 23;
	NoOfTrucks = 0;
	//false means ascending order
	loading_Ntruck.setPriorityOrder ( false );
	loading_Vtruck.setPriorityOrder ( false );
	loading_Struck.setPriorityOrder ( false );
	moving_Ntruck.setPriorityOrder ( false );
	moving_Vtruck.setPriorityOrder ( false );
	moving_Struck.setPriorityOrder ( false );

	Current_Time.setDay ( 1 );
	Current_Time.setHour ( 0 );
	totalNumOfNormalCargos = 0;
	totalNumOfPromotedCargos = 0;
}

bool Company::promoteCargo_normalTovip ( NormalCargo* pr_Cargo )
{
	if ( pr_Cargo )
	{
		Cargo* temp = dynamic_cast<Cargo*>(pr_Cargo);
		VipCargo* vtemp = (VipCargo*)temp;
		vtemp->SetType(Vip);
		float priority;
		priority= 12/ vtemp->GetpreparationTime().getDay() + 25 / (vtemp->GetpreparationTime().getHour()) + (50 / vtemp->GetDelieveryDistance()) + (6 * vtemp->GetCost());
		vtemp->SetPriority (priority); // need modification
		vip_Cargo.push ( vtemp, vtemp->GetPriority ( ) );
		return true;
	}
	return false;
}

bool Company::moveCargo_Todeliver ( Truck* t )
{
	bool x = false;
	PQueue<Cargo*, float>* cargos = t->GetCargosInTruck ( );
	Cargo* tempcargo = nullptr;
	NormalCargo* tempncargo = nullptr;
	SpecialCargo* tempscargo = nullptr;
	VipCargo* tempvcargo = nullptr;

	cargos->peek ( tempcargo );
	if ( tempcargo  && tempcargo->GetType ( ) == Normal )
	{
		while ( cargos->peek ( tempcargo ) && tempcargo->GetDeliveryTime ( ) <= Current_Time )
		{
			cargos->pop ( tempcargo );
			tempncargo = (NormalCargo*)tempcargo;

			delivered_NCargo.enqueue ( tempncargo );
			tempncargo->SetCase ( Delivered );

			x = true;

		}

	}
	else if ( tempcargo && tempcargo->GetType ( ) == Special )
	{
		while ( cargos->peek ( tempcargo ) && tempcargo->GetDeliveryTime ( ) <= Current_Time )
		{
			cargos->pop ( tempcargo );
			tempscargo = (SpecialCargo*)tempcargo;

			delivered_SCargo.enqueue ( tempscargo );
			tempscargo->SetCase ( Delivered );

			x = true;


		}
	}
	else
	{
		while ( cargos->peek ( tempcargo ) && tempcargo->GetDeliveryTime ( ) <= Current_Time )
		{
			cargos->pop ( tempcargo );
			tempvcargo = (VipCargo*)tempcargo;

			delivered_VCargo.enqueue ( tempvcargo );
			tempvcargo->SetCase ( Delivered );

			x = true;
		}

	}

	return x;
}


NormalCargo* Company::haveCargo_normal ( int id )
{
	Queue<NormalCargo*> temp_queue;
	NormalCargo* out_Cargo = nullptr;
	NormalCargo* temp_Cargo = nullptr;
	while ( normal_Cargo.dequeue ( temp_Cargo ) )
	{
		if ( temp_Cargo->GetID ( ) == id )
			out_Cargo = temp_Cargo;
		else
			temp_queue.enqueue ( temp_Cargo );
	}
	while ( temp_queue.dequeue ( temp_Cargo ) )
	{
		normal_Cargo.enqueue ( temp_Cargo );
	}
	return out_Cargo;
}
bool Company::addEvent ( Event* newEvent )
{
	if ( Events.enqueue ( newEvent ) )
		return true;
	return false;
}

bool Company::addCargo_normal ( NormalCargo* newCargo )
{
	if ( normal_Cargo.enqueue ( newCargo ) )
		return true;
	return false;
}

bool Company::addCargo_special ( SpecialCargo* newCargo )
{
	if ( special_Cargo.enqueue ( newCargo ) )
		return true;
	return false;
}

bool Company::addCargo_vip ( VipCargo* newCargo )
{
	if ( vip_Cargo.push ( newCargo, newCargo->GetPriority ( ) ) )
		return true;
	return false;
}

bool Company::addTruck_normal ( nTruck* newTruck )
{
	if ( normal_Truck.push ( newTruck, newTruck->GetPriority ( ) ) )
		return true;
	return false;
}

bool Company::addTruck_special ( sTruck* newTruck )
{
	if ( special_Truck.push ( newTruck, newTruck->GetPriority ( ) ) )
		return true;
	return false;
}

bool Company::addTruck_vip ( vTruck* newTruck )
{
	if ( vip_Truck.push ( newTruck, newTruck->GetPriority ( ) ) )
		return true;
	return false;
}

bool Company::moveNTruck_Toload ( )
{
	nTruck* temp = nullptr;
	if ( normal_Truck.pop ( temp ) )
	{
		loading_Ntruck.push ( temp, temp->GetEndLoadingTime ( ) );
		return true;
	}
	return false;
}

bool Company::moveSTruck_Toload ( )
{
	sTruck* temp = nullptr;
	if ( special_Truck.pop ( temp ) )
	{
		loading_Struck.push ( temp, temp->GetEndLoadingTime ( ) );
		return true;
	}
	return false;
}

bool Company::moveVTruck_Toload ( )
{
	vTruck* temp = nullptr;
	if ( vip_Truck.pop ( temp ) )
	{
		loading_Vtruck.push ( temp, temp->GetEndLoadingTime ( ) );
		return true;
	}
	return false;
}

bool Company::moveNTruck_Toload_Night()
{
	nTruck* temp = nullptr;
	if (normal_Truck_Night.pop(temp))
	{
		loading_Ntruck.push(temp, temp->GetEndLoadingTime());
		return true;
	}
	return false;
}

bool Company::moveSTruck_Toload_Night()
{
	sTruck* temp = nullptr;
	if (special_Truck_Night.pop(temp))
	{
		loading_Struck.push(temp, temp->GetEndLoadingTime());
		return true;
	}
	return false;
}

bool Company::moveVTruck_Toload_Night()
{
	vTruck* temp = nullptr;
	if (vip_Truck_Night.pop(temp))
	{
		loading_Vtruck.push(temp, temp->GetEndLoadingTime());
		return true;
	}
	return false;
}

bool Company::moveNTruck_Tomove ( )
{
	nTruck* temp = nullptr;
	if ( loading_Ntruck.pop ( temp ) )
	{
		moving_Ntruck.push ( temp, temp->GetDeliveryTime ( ) );
		return true;
	}
	return false;
}

bool Company::moveSTruck_Tomove ( )
{
	sTruck* temp = nullptr;
	if ( loading_Struck.pop ( temp ) )
	{
		moving_Struck.push ( temp, temp->GetDeliveryTime ( ) );
		return true;
	}
	return false;
}

bool Company::moveVTruck_Tomove ( )
{
	vTruck* temp = nullptr;
	if ( loading_Vtruck.pop ( temp ) )
	{
		moving_Vtruck.push ( temp, temp->GetDeliveryTime ( ) );
		return true;
	}
	return false;
}

bool Company::moveNTruck_Towaiting ( )
{
	nTruck* temp = nullptr;
	if ( moving_Ntruck.pop ( temp ) )
	{
		normal_Truck.push ( temp, temp->GetPriority ( ) );
		return true;
	}
	return false;

}

bool Company::moveSTruck_Towaiting ( )
{
	sTruck* temp = nullptr;
	if ( moving_Struck.pop ( temp ) )
	{
		special_Truck.push ( temp, temp->GetPriority ( ) );
		return true;
	}
	return false;

}

bool Company::moveVTruck_Towaiting ( )
{
	vTruck* temp = nullptr;
	if ( moving_Vtruck.pop ( temp ) )
	{
		vip_Truck.push ( temp, temp->GetPriority ( ) );
		return true;
	}
	return false;

}

bool Company::moveNTruck_Towaiting_Night()
{
	nTruck* temp = nullptr;
	if (moving_Ntruck.pop(temp))
	{
		normal_Truck_Night.push(temp, temp->GetPriority());
		return true;
	}
	return false;
}

bool Company::moveSTruck_Towaiting_Night()
{
	sTruck* temp = nullptr;
	if (moving_Struck.pop(temp))
	{
		special_Truck_Night.push(temp, temp->GetPriority());
		return true;
	}
	return false;
}

bool Company::moveVTruck_Towaiting_Night()
{
	vTruck* temp = nullptr;
	if (moving_Vtruck.pop(temp))
	{
		vip_Truck.push(temp, temp->GetPriority());
		return true;
	}
	return false;
}

bool Company::moveNTruck_ToMaintenance ( Time t )
{
	nTruck* temp = nullptr;
	if ( moving_Ntruck.pop ( temp ) )
	{
		Time tempt;
		tempt = t + temp->GetCheckupDuration ( );
		tempt = tempt + temp->GetDeliveryInterval ( );
		temp->SetEndCheckupTime ( tempt );
		temp->SetCurrentNoJourneys ( 0 );
		Maintenance_NTruck.enqueue ( temp );
		return true;
	}
	return false;
}

bool Company::moveSTruck_ToMaintenance ( Time t )
{
	sTruck* temp = nullptr;
	if ( moving_Struck.pop ( temp ) )
	{
		Time tempt;
		tempt = t + temp->GetCheckupDuration ( );
		tempt = tempt + temp->GetDeliveryInterval ( );
		temp->SetEndCheckupTime ( tempt );
		temp->SetCurrentNoJourneys ( 0 );
		Maintenance_STruck.enqueue ( temp );
		return true;
	}
	return false;
}

bool Company::moveVTruck_ToMaintenance ( Time t )
{
	vTruck* temp = nullptr;
	if ( moving_Vtruck.pop ( temp ) )
	{
		Time tempt;
		tempt = t + temp->GetCheckupDuration ( );
		tempt = tempt + temp->GetDeliveryInterval ( );
		temp->SetEndCheckupTime ( tempt );
		temp->SetCurrentNoJourneys ( 0 );
		Maintenance_VTruck.enqueue ( temp );
		return true;
	}
	return false;
}

bool Company::moveNTruck_FMTowaiting ( )
{
	nTruck* temp = nullptr;
	if ( Maintenance_NTruck.dequeue ( temp ) )
	{
		normal_Truck.push ( temp, temp->GetPriority ( ) );
		return true;
	}
	return false;
}

bool Company::moveSTruck_FMTowaiting ( )
{
	sTruck* temp = nullptr;
	if ( Maintenance_STruck.dequeue ( temp ) )
	{
		special_Truck.push ( temp, temp->GetPriority ( ) );
		return true;
	}
	return false;
}

bool Company::moveVTruck_FMTowaiting ( )
{
	vTruck* temp = nullptr;
	if ( Maintenance_VTruck.dequeue ( temp ) )
	{
		vip_Truck.push ( temp, temp->GetPriority ( ) );
		return true;
	}
	return false;
}

bool Company::moveNTruck_FMTowaiting_Night()
{
	nTruck* temp = nullptr;
	if (Maintenance_NTruck.dequeue(temp))
	{
		normal_Truck_Night.push(temp, temp->GetPriority());
		return true;
	}
	return false;
}

bool Company::moveSTruck_FMTowaiting_Night()
{
	sTruck* temp = nullptr;
	if (Maintenance_STruck.dequeue(temp))
	{
		special_Truck_Night.push(temp, temp->GetPriority());
		return true;
	}
	return false;
}

bool Company::moveVTruck_FMTowaiting_Night()
{
	vTruck* temp = nullptr;
	if (Maintenance_VTruck.dequeue(temp))
	{
		vip_Truck_Night.push(temp, temp->GetPriority());
		return true;
	}
	return false;
}

void Company::loadData()
{
	int k = 1;
	string file = "Data.txt";
	ifstream infile(file);
	int totalNumOfTrucks;
	int Truck_speed;

	int Truck_capacity;

	char Truck_shift;

	int noOfJourneysBeforeCheckup;
	int nTruck_checkupDuration;
	int sTruck_checkupDuration;
	int vTruck_checkupDuration;
	int AutoP;
	int MaxW;
	int noOfEvents;

	char truckType;
	nTruck* tempTruck1;
	sTruck* tempTruck2;
	vTruck* tempTruck3;



	infile >> totalNumOfTrucks;
	NoOfTrucks = totalNumOfTrucks;
	for (int i = 0; i < totalNumOfTrucks; i++)
	{
		infile >> truckType >> Truck_speed >> Truck_capacity >> Truck_shift;

		if (truckType == 'N')
		{
			nTruck* tempTruck = new nTruck;
			tempTruck->SetId(k++);
			tempTruck->SetSpeed(Truck_speed);
			tempTruck->SetTruckCapicity(Truck_capacity);
			tempTruck->SetPriority((5 * Truck_speed + 3 * (float)Truck_capacity) / (Truck_speed + (float)Truck_capacity));
			tempTruck->SetShift(Truck_shift);
			if (Truck_shift == 'D')
				normal_Truck.push(tempTruck, tempTruck->GetPriority());
			else if (Truck_shift == 'N')
				normal_Truck_Night.push(tempTruck, tempTruck->GetPriority());
		}
		else if (truckType == 'S')
		{
			sTruck* tempTruck = new sTruck;
			tempTruck->SetId(k++);
			tempTruck->SetSpeed(Truck_speed);
			tempTruck->SetTruckCapicity(Truck_capacity);
			tempTruck->SetPriority((5 * Truck_speed + 3 * (float)Truck_capacity) / (Truck_speed + (float)Truck_capacity));
			tempTruck->SetShift(Truck_shift);
			if (Truck_shift == 'D')
				special_Truck.push(tempTruck, tempTruck->GetPriority());
			else if (Truck_shift == 'N')
				special_Truck_Night.push(tempTruck, tempTruck->GetPriority());
		}
		else if (truckType == 'V')
		{
			vTruck* tempTruck = new vTruck;
			tempTruck->SetId(k++);
			tempTruck->SetSpeed(Truck_speed);
			tempTruck->SetTruckCapicity(Truck_capacity);
			tempTruck->SetPriority((5 * Truck_speed + 3 * (float)Truck_capacity) / (Truck_speed + (float)Truck_capacity));
			tempTruck->SetShift(Truck_shift);
			if (Truck_shift == 'D')
				vip_Truck.push(tempTruck, tempTruck->GetPriority());
			else if (Truck_shift == 'N')
				vip_Truck_Night.push(tempTruck, tempTruck->GetPriority());
		}

	}

	infile >> noOfJourneysBeforeCheckup >> nTruck_checkupDuration >> sTruck_checkupDuration >> vTruck_checkupDuration;
	infile >> AutoP >> MaxW;
	infile >> noOfEvents;
	if (!normal_Truck.isEmpty())
	{
		normal_Truck.peek(tempTruck1);
		tempTruck1->SetNoJourneys(noOfJourneysBeforeCheckup);
		tempTruck1->SetCheckupDuration(nTruck_checkupDuration);
	}
	if ( !normal_Truck_Night.isEmpty ( ) )
	{
		normal_Truck_Night.peek ( tempTruck1 );
		tempTruck1->SetNoJourneys ( noOfJourneysBeforeCheckup );
		tempTruck1->SetCheckupDuration ( nTruck_checkupDuration );
	}
	if (!special_Truck.isEmpty())
	{
		special_Truck.peek(tempTruck2);
		tempTruck2->SetNoJourneys(noOfJourneysBeforeCheckup);
		tempTruck2->SetCheckupDuration(sTruck_checkupDuration);
	}
	if (!special_Truck_Night.isEmpty())
	{
		special_Truck_Night.peek(tempTruck2);
		tempTruck2->SetNoJourneys(noOfJourneysBeforeCheckup);
		tempTruck2->SetCheckupDuration(sTruck_checkupDuration);
	}
	if (!vip_Truck.isEmpty())
	{
		vip_Truck.peek(tempTruck3);
		tempTruck3->SetNoJourneys(noOfJourneysBeforeCheckup);
		tempTruck3->SetCheckupDuration(sTruck_checkupDuration);
	}
	if ( !vip_Truck_Night.isEmpty ( ) )
	{
		vip_Truck_Night.peek ( tempTruck3 );
		tempTruck3->SetNoJourneys ( noOfJourneysBeforeCheckup );
		tempTruck3->SetCheckupDuration ( sTruck_checkupDuration );
	}

	char eventName;
	char cargoType;
	int day;
	int hour;
	char ignoredChar;
	int cargoId;
	float cargoDist;
	int LD;
	float cost;

	for (int i = 0; i < noOfEvents; i++)
	{
		infile >> eventName;
		if (eventName == 'R')
		{
			infile >> cargoType;
			infile >> day;
			infile.ignore(1);
			infile >> hour;
			infile >> cargoId;
			infile >> cargoDist;
			infile >> LD;
			infile >> cost;

			Time ld(0, LD);

			Time tempTime;
			tempTime.setDay(day);
			tempTime.setHour(hour);

			ReadyEvent* tempEvent = new ReadyEvent(AutoP, MaxW, cargoType, tempTime, cargoId, cargoDist, ld, cost);

			Events.enqueue(tempEvent);

		}
		else if (eventName == 'X')
		{
			infile >> day;
			infile.ignore(1);
			infile >> hour >> cargoId;
			Time tempTime(day, hour);
			CancellationEvent* tempEvent = new CancellationEvent(tempTime, cargoId);

			Events.enqueue(tempEvent);

		}
		else if (eventName == 'P')
		{
			infile >> day;
			infile.ignore(1);
			infile >> hour >> cargoId >> cost;
			Time tempTime(day, hour);

			PromotionEvent* tempEvent = new PromotionEvent(tempTime, cargoId, cost);

			Events.enqueue(tempEvent);

		}
	}

}



void Company::InterActiveMode ( Time t )
{
	this->printtime ( t );
	this->printWaitingCargos ( );
	this->printbreak ( );
	this->printLoadingTrucks ( );
	this->printbreak ( );
	this->printEmptyTrucks ( );
	this->printbreak ( );
	this->printMovingCargos ( );
	this->printbreak ( );
	this->printInCheckupTrucks ( );
	this->printbreak ( );
	this->printDeliverdCargos ( );
	this->printbreak ( );



}

void Company::printWaitingCargos ( )
{
	NormalCargo* ncargoPtr;
	SpecialCargo* scargoPtr;
	VipCargo* vcargoPtr;

	pOut->printInteger ( normal_Cargo.getCount ( ) + special_Cargo.getCount ( ) + vip_Cargo.getcounter ( ) );
	pOut->printString ( " Waiting Cargos: [" );

	normal_Cargo.print ( );
	pOut->printString ( "] (" );


	special_Cargo.print ( );
	pOut->printString ( ") {" );


	vip_Cargo.print ( );
	pOut->printString ( "}" );


	pOut->printEndl ( );
}

void Company::printLoadingTrucks ( )
{
	nTruck* ntemptruck = nullptr;
	sTruck* stemptruck;
	vTruck* vtemptruck;

	Cargo* tempcargo;

	PQueue<nTruck*, Time> temploading_Ntruck;
	PQueue<vTruck*, Time> temploading_Vtruck;
	PQueue<sTruck*, Time> temploading_Struck;

	temploading_Ntruck.setPriorityOrder ( false );
	temploading_Struck.setPriorityOrder ( false );
	temploading_Vtruck.setPriorityOrder ( false );



	pOut->printInteger ( loading_Ntruck.getcounter ( ) + loading_Struck.getcounter ( ) + loading_Vtruck.getcounter ( ) );
	pOut->printString ( " Loading Trucks: " );

	while ( !loading_Ntruck.isEmpty ( ) )
	{

		loading_Ntruck.pop ( ntemptruck );
		temploading_Ntruck.push ( ntemptruck, ntemptruck->GetEndLoadingTime ( ) );

		pOut->printInteger ( ntemptruck->GetId ( ) );


		ntemptruck->GetCargosInTruck ( )->peek ( tempcargo );

		if ( tempcargo->GetType ( ) == Normal )
		{
			pOut->printString ( "[" );
			ntemptruck->GetCargosInTruck ( )->print ( );
			pOut->printString ( "] " );
		}
		else if ( tempcargo->GetType ( ) == Special )
		{
			pOut->printString ( "(" );
			ntemptruck->GetCargosInTruck ( )->print ( );
			pOut->printString ( ") " );
		}
		else
		{
			pOut->printString ( "{" );
			ntemptruck->GetCargosInTruck ( )->print ( );
			pOut->printString ( "} " );
		}



	}

	while ( !loading_Struck.isEmpty ( ) )
	{

		loading_Struck.pop ( stemptruck );
		temploading_Struck.push ( stemptruck, stemptruck->GetEndLoadingTime ( ) );

		pOut->printInteger ( stemptruck->GetId ( ) );



		stemptruck->GetCargosInTruck ( )->peek ( tempcargo );

		if ( tempcargo->GetType ( ) == Normal )
		{
			pOut->printString ( "[" );
			stemptruck->GetCargosInTruck ( )->print ( );
			pOut->printString ( "] " );
		}
		else if ( tempcargo->GetType ( ) == Special )
		{
			pOut->printString ( "(" );
			stemptruck->GetCargosInTruck ( )->print ( );
			pOut->printString ( ") " );
		}
		else
		{
			pOut->printString ( "{" );
			stemptruck->GetCargosInTruck ( )->print ( );
			pOut->printString ( "} " );
		}

	}


	while ( !loading_Vtruck.isEmpty ( ) )
	{

		loading_Vtruck.pop ( vtemptruck );
		temploading_Vtruck.push ( vtemptruck, vtemptruck->GetEndLoadingTime ( ) );

		pOut->printInteger ( vtemptruck->GetId ( ) );



		vtemptruck->GetCargosInTruck ( )->peek ( tempcargo );

		if ( tempcargo->GetType ( ) == Normal )
		{
			pOut->printString ( "[" );
			vtemptruck->GetCargosInTruck ( )->print ( );
			pOut->printString ( "] " );
		}
		else if ( tempcargo->GetType ( ) == Special )
		{
			pOut->printString ( "(" );
			vtemptruck->GetCargosInTruck ( )->print ( );
			pOut->printString ( ") " );
		}
		else
		{
			pOut->printString ( "{" );
			vtemptruck->GetCargosInTruck ( )->print ( );
			pOut->printString ( "} " );
		}
	}

	pOut->printEndl ( );
	while ( !temploading_Ntruck.isEmpty ( ) )
	{
		temploading_Ntruck.pop ( ntemptruck );
		loading_Ntruck.push ( ntemptruck, ntemptruck->GetEndLoadingTime ( ) );

	}

	while ( !temploading_Struck.isEmpty ( ) )
	{
		temploading_Struck.pop ( stemptruck );
		loading_Struck.push ( stemptruck, stemptruck->GetEndLoadingTime ( ) );

	}

	while ( !temploading_Vtruck.isEmpty ( ) )
	{
		temploading_Vtruck.pop ( vtemptruck );
		loading_Vtruck.push ( vtemptruck, vtemptruck->GetEndLoadingTime ( ) );

	}

}

void Company::printEmptyTrucks()
{
	nTruck* ntemptruck;
	sTruck* stemptruck;
	vTruck* vtemptruck;
	Queue<vTruck*> viptempTruck;
	Queue<nTruck*> normaltempTruck;
	Queue<sTruck*> specialtempTruck;

	Queue<vTruck*> viptempTruckn;
	Queue<nTruck*> normaltempTruckn;
	Queue<sTruck*> specialtempTruckn;

	pOut->printInteger(normal_Truck.getcounter() + special_Truck.getcounter() + vip_Truck.getcounter());
	pOut->printString(" Empty Trucks: ");
	pOut->printString("D: ");
	while (!normal_Truck.isEmpty())
	{
		normal_Truck.pop(ntemptruck);
		normaltempTruck.enqueue(ntemptruck);
		pOut->printString("[");
		pOut->printInteger(ntemptruck->GetId());
		pOut->printString("]");
	}

	while (!special_Truck.isEmpty())
	{
		special_Truck.pop(stemptruck);
		specialtempTruck.enqueue(stemptruck);
		pOut->printString("(");
		pOut->printInteger(stemptruck->GetId());
		pOut->printString(")");
	}

	while (!vip_Truck.isEmpty())
	{
		vip_Truck.pop(vtemptruck);
		viptempTruck.enqueue(vtemptruck);
		pOut->printString("{");
		pOut->printInteger(vtemptruck->GetId());
		pOut->printString("}");
	}

	pOut->printString("  N: ");

	while (!normal_Truck_Night.isEmpty())
	{
		normal_Truck_Night.pop(ntemptruck);
		normaltempTruckn.enqueue(ntemptruck);
		pOut->printString("[");
		pOut->printInteger(ntemptruck->GetId());
		pOut->printString("]");
	}

	while (!special_Truck_Night.isEmpty())
	{
		special_Truck_Night.pop(stemptruck);
		specialtempTruckn.enqueue(stemptruck);
		pOut->printString("(");
		pOut->printInteger(stemptruck->GetId());
		pOut->printString(")");
	}

	while (!vip_Truck_Night.isEmpty())
	{
		vip_Truck_Night.pop(vtemptruck);
		viptempTruckn.enqueue(vtemptruck);
		pOut->printString("{");
		pOut->printInteger(vtemptruck->GetId());
		pOut->printString("}");
	}

	while (!normaltempTruck.isEmpty())
	{
		normaltempTruck.dequeue(ntemptruck);
		normal_Truck.push(ntemptruck, ntemptruck->GetPriority());
	}

	while (!specialtempTruck.isEmpty())
	{
		specialtempTruck.dequeue(stemptruck);
		special_Truck.push(stemptruck, stemptruck->GetPriority());
	}

	while (!viptempTruck.isEmpty())
	{
		viptempTruck.dequeue(vtemptruck);
		vip_Truck.push(vtemptruck, vtemptruck->GetPriority());
	}

	while (!normaltempTruckn.isEmpty())
	{
		normaltempTruckn.dequeue(ntemptruck);
		normal_Truck_Night.push(ntemptruck, ntemptruck->GetPriority());
	}

	while (!specialtempTruckn.isEmpty())
	{
		specialtempTruckn.dequeue(stemptruck);
		special_Truck_Night.push(stemptruck, stemptruck->GetPriority());
	}

	while (!viptempTruckn.isEmpty())
	{
		viptempTruckn.dequeue(vtemptruck);
		vip_Truck_Night.push(vtemptruck, vtemptruck->GetPriority());
	}

	pOut->printEndl();
}

void Company::printMovingCargos()
{

	nTruck* ntemptruck = nullptr;
	sTruck* stemptruck;
	vTruck* vtemptruck;

	Cargo* tempcargo = nullptr;

	PQueue<nTruck*, Time> tempmoving_Ntruck;
	PQueue<vTruck*, Time> tempmoving_Vtruck;
	PQueue<sTruck*, Time> tempmoving_Struck;

	tempmoving_Ntruck.setPriorityOrder(false);
	tempmoving_Struck.setPriorityOrder(false);
	tempmoving_Vtruck.setPriorityOrder(false);


	int n = 0;
	int movingTrucksNum = 0;

	while (!moving_Ntruck.isEmpty())
	{
		moving_Ntruck.pop(ntemptruck);
		tempmoving_Ntruck.push(ntemptruck, ntemptruck->GetDeliveryTime());
		n = n + ntemptruck->GetCargosInTruck()->getcounter();
		movingTrucksNum++;
	}

	while (!moving_Vtruck.isEmpty())
	{
		moving_Vtruck.pop(vtemptruck);
		tempmoving_Vtruck.push(vtemptruck, vtemptruck->GetDeliveryTime());
		n = n + vtemptruck->GetCargosInTruck()->getcounter();
		movingTrucksNum++;
	}

	while (!moving_Struck.isEmpty())
	{
		moving_Struck.pop(stemptruck);
		tempmoving_Struck.push(stemptruck, stemptruck->GetDeliveryTime());
		n = n + stemptruck->GetCargosInTruck()->getcounter();
		movingTrucksNum++;
	}

	while (!tempmoving_Ntruck.isEmpty())
	{
		tempmoving_Ntruck.pop(ntemptruck);
		moving_Ntruck.push(ntemptruck, ntemptruck->GetDeliveryTime());
	}
	while (!tempmoving_Struck.isEmpty())
	{
		tempmoving_Struck.pop(stemptruck);
		moving_Struck.push(stemptruck, stemptruck->GetDeliveryTime());
	}
	while (!tempmoving_Vtruck.isEmpty())
	{
		tempmoving_Vtruck.pop(vtemptruck);
		moving_Vtruck.push(vtemptruck, vtemptruck->GetDeliveryTime());
	}

	//pOut->printInteger ( moving_NCargo.getcounter ( ) + moving_SCargo.getcounter ( ) + moving_VCargo.getcounter ( ) );
	pOut->printInteger(movingTrucksNum);
	pOut->printString(" Moving Trucks Carrying ");
	pOut->printInteger(n);
	pOut->printString(" Cargos: ");
	while (!moving_Ntruck.isEmpty())
	{

		moving_Ntruck.pop(ntemptruck);
		tempmoving_Ntruck.push(ntemptruck, ntemptruck->GetDeliveryTime());

		pOut->printInteger(ntemptruck->GetId());


		ntemptruck->GetCargosInTruck()->peek(tempcargo);
		if (!ntemptruck->GetCargosInTruck()->isEmpty())
		{

			if (tempcargo->GetType() == Normal)
			{
				pOut->printString("[");
				ntemptruck->GetCargosInTruck()->print();
				pOut->printString("] ");
			}
			else if (tempcargo->GetType() == Special)
			{
				pOut->printString("(");
				ntemptruck->GetCargosInTruck()->print();
				pOut->printString(") ");
			}
			else
			{
				pOut->printString("{");
				ntemptruck->GetCargosInTruck()->print();
				pOut->printString("} ");
			}
		}
		else
		{
			pOut->printString("  ");
		}
	}

	while (!moving_Struck.isEmpty())
	{

		moving_Struck.pop(stemptruck);
		tempmoving_Struck.push(stemptruck, stemptruck->GetDeliveryTime());

		pOut->printInteger(stemptruck->GetId());

		stemptruck->GetCargosInTruck()->peek(tempcargo);

		if (!stemptruck->GetCargosInTruck()->isEmpty())
		{

			if (tempcargo->GetType() == Normal)
			{
				pOut->printString("[");
				stemptruck->GetCargosInTruck()->print();
				pOut->printString("] ");
			}
			else if (tempcargo->GetType() == Special)
			{
				pOut->printString("(");
				stemptruck->GetCargosInTruck()->print();
				pOut->printString(") ");
			}
			else
			{
				pOut->printString("{");
				stemptruck->GetCargosInTruck()->print();
				pOut->printString("} ");
			}
		}
		else
		{
			pOut->printString("  ");
		}
	}

	while (!moving_Vtruck.isEmpty())
	{

		moving_Vtruck.pop(vtemptruck);
		tempmoving_Vtruck.push(vtemptruck, vtemptruck->GetDeliveryTime());

		pOut->printInteger(vtemptruck->GetId());


		vtemptruck->GetCargosInTruck()->peek(tempcargo);

		if (!vtemptruck->GetCargosInTruck()->isEmpty())
		{

			if (tempcargo->GetType() == Normal)
			{
				pOut->printString("[");
				vtemptruck->GetCargosInTruck()->print();
				pOut->printString("] ");
			}
			else if (tempcargo->GetType() == Special)
			{
				pOut->printString("(");
				vtemptruck->GetCargosInTruck()->print();
				pOut->printString(") ");
			}
			else
			{
				pOut->printString("{");
				vtemptruck->GetCargosInTruck()->print();
				pOut->printString("} ");
			}
		}
		else
		{
			pOut->printString("  ");
		}

	}

	pOut->printEndl();
	while (!tempmoving_Ntruck.isEmpty())
	{
		tempmoving_Ntruck.pop(ntemptruck);
		moving_Ntruck.push(ntemptruck, ntemptruck->GetEndLoadingTime());

	}

	while (!tempmoving_Struck.isEmpty())
	{
		tempmoving_Struck.pop(stemptruck);
		moving_Struck.push(stemptruck, stemptruck->GetEndLoadingTime());

	}

	while (!tempmoving_Vtruck.isEmpty())
	{
		tempmoving_Vtruck.pop(vtemptruck);
		moving_Vtruck.push(vtemptruck, vtemptruck->GetEndLoadingTime());

	}

}


void Company::printInCheckupTrucks ( )
{
	nTruck* ntemptruck;
	sTruck* stemptruck;
	vTruck* vtemptruck;

	Queue<vTruck*> viptempTruck;
	Queue<nTruck*> normaltempTruck;
	Queue<sTruck*> specialtempTruck;

	pOut->printInteger ( Maintenance_NTruck.getCount ( ) + Maintenance_STruck.getCount ( ) + Maintenance_VTruck.getCount ( ) );
	pOut->printString ( " In-Checkup Trucks: " );
	while ( !Maintenance_NTruck.isEmpty ( ) )
	{
		Maintenance_NTruck.dequeue ( ntemptruck );
		normaltempTruck.enqueue ( ntemptruck );
		pOut->printString ( "[" );
		pOut->printInteger ( ntemptruck->GetId ( ) );
		pOut->printString ( "]" );
	}

	while ( !Maintenance_STruck.isEmpty ( ) )
	{
		Maintenance_STruck.dequeue ( stemptruck );
		specialtempTruck.enqueue ( stemptruck );
		pOut->printString ( "(" );
		pOut->printInteger ( stemptruck->GetId ( ) );
		pOut->printString ( ")" );
	}

	while ( !Maintenance_VTruck.isEmpty ( ) )
	{
		Maintenance_VTruck.dequeue ( vtemptruck );
		viptempTruck.enqueue ( vtemptruck );
		pOut->printString ( "{" );
		pOut->printInteger ( vtemptruck->GetId ( ) );
		pOut->printString ( "}" );
	}

	while ( !normaltempTruck.isEmpty ( ) )
	{
		normaltempTruck.dequeue ( ntemptruck );
		Maintenance_NTruck.enqueue ( ntemptruck );
	}

	while ( !specialtempTruck.isEmpty ( ) )
	{
		specialtempTruck.dequeue ( stemptruck );
		Maintenance_STruck.enqueue ( stemptruck );
	}

	while ( !viptempTruck.isEmpty ( ) )
	{
		viptempTruck.dequeue ( vtemptruck );
		Maintenance_VTruck.enqueue ( vtemptruck );
	}
	pOut->printEndl ( );
}

void Company::printDeliverdCargos ( )
{
	/*NormalCargo* ntempcargo;
	SpecialCargo* stempcargo;
	VipCargo* vtempcargo;*/

	/*Queue<NormalCargo*> ntempcargoqueue;
	Queue<SpecialCargo*> stempcargoqueue;
	Queue<VipCargo*> vtempcargoqueue;*/

	pOut->printInteger ( delivered_NCargo.getCount ( ) + delivered_SCargo.getCount ( ) + delivered_VCargo.getCount ( ) );
	pOut->printString ( " Delivered Cargos: [" );


	delivered_NCargo.print ( );
	pOut->printString ( "] (" );

	delivered_SCargo.print ( );
	pOut->printString ( ") {" );

	delivered_VCargo.print ( );
	pOut->printString ( "}" );

	pOut->printEndl ( );
}

void Company::printtime ( Time t )
{
	pOut->printString ( "Current Time (Day:Hour):" );
	pOut->printString ( to_string ( t.getDay ( ) ) );
	pOut->printString ( ":" );
	pOut->printString ( to_string ( t.getHour ( ) ) );
	pOut->printEndl ( );


}

void Company::printbreak ( )
{
	pOut->printString ( "---------------------------------------------------" );
	pOut->printEndl ( );
}


void Company::Assign_Cargos ( Time simTime )
{

	nTruck* n_truck = nullptr;
	vTruck* v_truck = nullptr;
	sTruck* s_truck = nullptr;

	//loading rule "only 1 trucks for cargo typ"
	bool loading_NC = false;
	bool loading_SC = false;
	bool loading_VC = false;
	//check normal trucks (loading)
	Queue<nTruck*> tempn;
	int x = loading_Ntruck.getcounter ();
	for ( int i = 0; i < x; i++ )
	{
		nTruck* temp_truck = nullptr;
		Cargo* temp_cargo = nullptr;
		loading_Ntruck.pop ( temp_truck );
		temp_truck->GetCargosInTruck ( )->peek ( temp_cargo );
		if ( temp_cargo )
		{
			if ( temp_cargo->GetType ( ) == Normal )
				loading_NC = true;
			else if ( temp_cargo->GetType ( ) == Special )
				loading_SC = true;
			else if ( temp_cargo->GetType ( ) == Vip )
				loading_VC = true;
		}
		tempn.enqueue ( temp_truck );
	}
	int x1 = tempn.getCount ( );
	for ( int i = 0; i < x1; i++ )
	{
		nTruck* temp_truck = nullptr;
		tempn.dequeue ( temp_truck );
		loading_Ntruck.push ( temp_truck, temp_truck->GetEndLoadingTime ( ) );
	}
	//check special trucks (loading)
	Queue<sTruck*> temps;
	int x2 = loading_Struck.getcounter ( );
	for ( int i = 0; i < x2; i++ )
	{
		sTruck* temp_truck = nullptr;
		Cargo* temp_cargo = nullptr;
		loading_Struck.pop ( temp_truck );
		temp_truck->GetCargosInTruck ( )->peek ( temp_cargo );
		if ( temp_cargo )
		{
			if ( temp_cargo->GetType ( ) == Normal )
				loading_NC = true;
			else if ( temp_cargo->GetType ( ) == Special )
				loading_SC = true;
			else if ( temp_cargo->GetType ( ) == Vip )
				loading_VC = true;
		}
		temps.enqueue ( temp_truck );
	}
	int x3 = temps.getCount ( );
	for ( int i = 0; i < x3; i++ )
	{
		sTruck* temp_truck = nullptr;
		temps.dequeue ( temp_truck );
		loading_Struck.push ( temp_truck, temp_truck->GetEndLoadingTime ( ) );
	}
	//check vip trucks (loading)
	Queue<vTruck*> tempv;
	int x4 = loading_Vtruck.getcounter ( );
	for ( int i = 0; i < x4; i++ )
	{
		vTruck* temp_truck = nullptr;
		Cargo* temp_cargo = nullptr;
		loading_Vtruck.pop ( temp_truck );
		temp_truck->GetCargosInTruck ( )->peek ( temp_cargo );
		if ( temp_cargo )
		{
			if ( temp_cargo->GetType ( ) == Normal )
				loading_NC = true;
			else if ( temp_cargo->GetType ( ) == Special )
				loading_SC = true;
			else if ( temp_cargo->GetType ( ) == Vip )
				loading_VC = true;
		}
		tempv.enqueue ( temp_truck );
	}
	int x5 = tempv.getCount ( );
	for ( int i = 0; i < x5; i++ )
	{
		vTruck* temp_truck = nullptr;
		tempv.dequeue ( temp_truck );
		loading_Vtruck.push ( temp_truck, temp_truck->GetEndLoadingTime ( ) );
	}

	//--------loading cargos after MaxW---------//
	//1st special ones
	special_Truck.peek ( s_truck );
	SpecialCargo* s_CargoMw = nullptr;
	special_Cargo.peek ( s_CargoMw );
	while ( s_truck && s_CargoMw && s_CargoMw->Exceeded_MaxW ( Current_Time ) )
	{
		s_truck->AddCargo ( s_CargoMw, Current_Time ); //this will set endloading time
		s_CargoMw->SetCarryingTruck ( s_truck ); ///////////////

		special_Cargo.dequeue ( s_CargoMw );
		moveSTruck_Toload ( );
		s_truck->setStartLoadingTime ( simTime );
		s_CargoMw = nullptr;
		special_Cargo.peek ( s_CargoMw );
		s_truck = nullptr;
		special_Truck.peek ( s_truck );
	}
	//2nd vip ones
	normal_Truck.peek ( n_truck );
	vip_Truck.peek ( v_truck );
	VipCargo* v_CargoMw = nullptr;
	vip_Cargo.peek ( v_CargoMw );
	while ( (n_truck || v_truck) && v_CargoMw && v_CargoMw->Exceeded_MaxW ( Current_Time ) )
	{
		if ( v_truck )
		{
			v_truck->AddCargo ( v_CargoMw, Current_Time ); //this will set endloading time
			v_CargoMw->SetCarryingTruck ( v_truck ); ////////////////////////

			vip_Cargo.pop ( v_CargoMw );
			moveVTruck_Toload ( );
			v_truck->setStartLoadingTime ( simTime );
			v_CargoMw = nullptr;
			vip_Cargo.peek ( v_CargoMw );
			v_truck = nullptr;
			vip_Truck.peek ( v_truck );
		}
		else if ( n_truck )
		{
			n_truck->AddCargo ( v_CargoMw, Current_Time ); //this will set endloading time
	
			v_CargoMw->SetCarryingTruck ( n_truck ); //////////////////////////////

			vip_Cargo.pop ( v_CargoMw );
			moveNTruck_Toload ( );
			n_truck->setStartLoadingTime ( simTime );
			v_CargoMw = nullptr;
			vip_Cargo.peek ( v_CargoMw );
			n_truck = nullptr;
			normal_Truck.peek ( n_truck );
		}
	}
	//3nd normal ones
	normal_Truck.peek ( n_truck );
	vip_Truck.peek ( v_truck );
	NormalCargo* n_CargoMw = nullptr;
	normal_Cargo.peek ( n_CargoMw );
	while ( (n_truck || v_truck) && n_CargoMw && n_CargoMw->Exceeded_MaxW ( Current_Time ) )
	{
		if ( n_truck )
		{
			n_truck->AddCargo ( n_CargoMw, Current_Time ); //this will set endloading time

			n_CargoMw->SetCarryingTruck ( n_truck ); //////////////////////////////

			normal_Cargo.dequeue ( n_CargoMw );
			moveNTruck_Toload ( );
			n_truck->setStartLoadingTime ( simTime );
			n_CargoMw = nullptr;
			normal_Cargo.peek ( n_CargoMw );
			n_truck = nullptr;
			normal_Truck.peek ( n_truck );
		}
		else if ( v_truck )
		{
			v_truck->AddCargo ( n_CargoMw, Current_Time ); //this will set endloading time
			n_CargoMw->SetCarryingTruck ( v_truck ); ////////////////////////

			normal_Cargo.dequeue ( n_CargoMw );
			moveVTruck_Toload ( );
			v_truck->setStartLoadingTime ( simTime );
			n_CargoMw = nullptr;
			normal_Cargo.peek ( n_CargoMw );
			v_truck = nullptr;
			vip_Truck.peek ( v_truck );
		}
	}

	//--------loading cargos before MaxW---------//

	//1st assign vip cargos 
	normal_Truck.peek ( n_truck );
	vip_Truck.peek ( v_truck );
	special_Truck.peek ( s_truck );
	if (!loading_VC )
	{
		if ( v_truck && vip_Cargo.getcounter ( ) >= v_truck->GetTruckCapicity ( ) )
		{
			VipCargo* v_Cargo = nullptr;
			for ( int i = 0; i < v_truck->GetTruckCapicity ( ); i++ )
			{
				vip_Cargo.peek ( v_Cargo );
				v_truck->AddCargo ( v_Cargo, Current_Time ); //this will set endloading time

				v_Cargo->SetCarryingTruck ( v_truck ); ////////////////////

				vip_Cargo.pop ( v_Cargo );
			}
			moveVTruck_Toload ( );
			v_truck->setStartLoadingTime ( simTime );

		}
		else if ( n_truck && vip_Cargo.getcounter ( ) >= n_truck->GetTruckCapicity ( ) )
		{
			VipCargo* v_Cargo = nullptr;
			for ( int i = 0; i < n_truck->GetTruckCapicity ( ); i++ )
			{
				vip_Cargo.peek ( v_Cargo );
				n_truck->AddCargo ( v_Cargo, Current_Time ); //this will set endloading time

				v_Cargo->SetCarryingTruck ( n_truck ); //////////////////////

				vip_Cargo.pop ( v_Cargo );
			}
			moveNTruck_Toload ( );
			n_truck->setStartLoadingTime ( simTime );

		}
		else if ( s_truck && vip_Cargo.getcounter ( ) >= s_truck->GetTruckCapicity ( ) )
		{
			VipCargo* v_Cargo = nullptr;
			for ( int i = 0; i < s_truck->GetTruckCapicity ( ); i++ )
			{
				vip_Cargo.peek ( v_Cargo );
				s_truck->AddCargo ( v_Cargo, Current_Time ); //this will set endloading time

				v_Cargo->SetCarryingTruck ( s_truck ); /////////////////////

				vip_Cargo.pop ( v_Cargo );
			}
			moveSTruck_Toload ( );
			s_truck->setStartLoadingTime ( simTime );

		}
	}
	//2nd assign special cargos
	special_Truck.peek ( s_truck );
	if (!loading_SC )
	{
		if ( s_truck && special_Cargo.getCount ( ) >= s_truck->GetTruckCapicity ( ) )
		{
			SpecialCargo* s_Cargo = nullptr;
			for ( int i = 0; i < s_truck->GetTruckCapicity ( ); i++ )
			{
				special_Cargo.peek ( s_Cargo );
				s_truck->AddCargo ( s_Cargo, Current_Time ); //this will set endloading time

				s_Cargo->SetCarryingTruck ( s_truck ); //////////////////

				special_Cargo.dequeue ( s_Cargo );
			}
			moveSTruck_Toload ( );
			s_truck->setStartLoadingTime ( simTime );

		}
	}
	//3rd assign normal cargos
	normal_Truck.peek ( n_truck );
	vip_Truck.peek ( v_truck );
	if (!loading_NC )
	{
		if ( n_truck && normal_Cargo.getCount ( ) >= n_truck->GetTruckCapicity ( ) )
		{
			NormalCargo* n_Cargo = nullptr;
			for ( int i = 0; i < n_truck->GetTruckCapicity ( ); i++ )
			{
				normal_Cargo.peek ( n_Cargo );
				n_truck->AddCargo ( n_Cargo, Current_Time ); //this will set endloading time

				n_Cargo->SetCarryingTruck ( n_truck ); /////////////////////

				normal_Cargo.dequeue ( n_Cargo );
			}
			moveNTruck_Toload ( );
			n_truck->setStartLoadingTime ( simTime );

		}
		else if ( v_truck && normal_Cargo.getCount ( ) >= v_truck->GetTruckCapicity ( ) )
		{
			NormalCargo* n_Cargo = nullptr;
			for ( int i = 0; i < v_truck->GetTruckCapicity ( ); i++ )
			{
				normal_Cargo.peek ( n_Cargo );
				v_truck->AddCargo ( n_Cargo, Current_Time ); //this will set endloading time

				n_Cargo->SetCarryingTruck ( v_truck ); /////////////

				normal_Cargo.dequeue ( n_Cargo );
			}
			moveVTruck_Toload ( );
			v_truck->setStartLoadingTime ( simTime );

		}
	}
}
void Company::Assign_Cargos_Night(Time simTime)
{

	nTruck* n_truck = nullptr;
	vTruck* v_truck = nullptr;
	sTruck* s_truck = nullptr;
	//loading rule "only 1 trucks for cargo typ"
	bool loading_NC = false;
	bool loading_SC = false;
	bool loading_VC = false;
	//check normal trucks (loading)
	Queue<nTruck*> tempn;
	int x = loading_Ntruck.getcounter();
	for (int i = 0; i < x; i++)
	{
		nTruck* temp_truck = nullptr;
		Cargo* temp_cargo = nullptr;
		loading_Ntruck.pop(temp_truck);
		temp_truck->GetCargosInTruck()->peek(temp_cargo);
		if (temp_cargo)
		{
			if (temp_cargo->GetType() == Normal)
				loading_NC = true;
			else if (temp_cargo->GetType() == Special)
				loading_SC = true;
			else if (temp_cargo->GetType() == Vip)
				loading_VC = true;
		}
		tempn.enqueue(temp_truck);
	}
	int x1 = tempn.getCount();
	for (int i = 0; i < x1; i++)
	{
		nTruck* temp_truck = nullptr;
		tempn.dequeue(temp_truck);
		loading_Ntruck.push(temp_truck, temp_truck->GetEndLoadingTime());
	}
	//check special trucks (loading)
	Queue<sTruck*> temps;
	int x2 = loading_Struck.getcounter();
	for (int i = 0; i < x2; i++)
	{
		sTruck* temp_truck = nullptr;
		Cargo* temp_cargo = nullptr;
		loading_Struck.pop(temp_truck);
		temp_truck->GetCargosInTruck()->peek(temp_cargo);
		if (temp_cargo)
		{
			if (temp_cargo->GetType() == Normal)
				loading_NC = true;
			else if (temp_cargo->GetType() == Special)
				loading_SC = true;
			else if (temp_cargo->GetType() == Vip)
				loading_VC = true;
		}
		temps.enqueue(temp_truck);
	}
	int x3 = temps.getCount();
	for (int i = 0; i < x3; i++)
	{
		sTruck* temp_truck = nullptr;
		temps.dequeue(temp_truck);
		loading_Struck.push(temp_truck, temp_truck->GetEndLoadingTime());
	}
	//check vip trucks (loading)
	Queue<vTruck*> tempv;
	int x4 = loading_Vtruck.getcounter();
	for (int i = 0; i < x4; i++)
	{
		vTruck* temp_truck = nullptr;
		Cargo* temp_cargo = nullptr;
		loading_Vtruck.pop(temp_truck);
		temp_truck->GetCargosInTruck()->peek(temp_cargo);
		if (temp_cargo)
		{
			if (temp_cargo->GetType() == Normal)
				loading_NC = true;
			else if (temp_cargo->GetType() == Special)
				loading_SC = true;
			else if (temp_cargo->GetType() == Vip)
				loading_VC = true;
		}
		tempv.enqueue(temp_truck);
	}
	int x5 = tempv.getCount();
	for (int i = 0; i < x5; i++)
	{
		vTruck* temp_truck = nullptr;
		tempv.dequeue(temp_truck);
		loading_Vtruck.push(temp_truck, temp_truck->GetEndLoadingTime());
	}

	//--------loading cargos after MaxW---------//
	//1st special ones
	special_Truck_Night.peek(s_truck);
	SpecialCargo* s_CargoMw = nullptr;
	special_Cargo.peek(s_CargoMw);
	while (s_truck && s_CargoMw && s_CargoMw->Exceeded_MaxW(Current_Time))
	{
		s_truck->AddCargo(s_CargoMw, Current_Time); //this will set endloading time

		s_CargoMw->SetCarryingTruck(s_truck); ///////////////

		special_Cargo.dequeue(s_CargoMw);
		moveSTruck_Toload_Night();
		s_truck->setStartLoadingTime(simTime);
		s_CargoMw = nullptr;
		special_Cargo.peek(s_CargoMw);
		s_truck = nullptr;
		special_Truck_Night.peek(s_truck);
	}
	//2nd special ones
	normal_Truck_Night.peek(n_truck);
	vip_Truck_Night.peek(v_truck);
	VipCargo* v_CargoMw = nullptr;
	vip_Cargo.peek(v_CargoMw);
	while ((n_truck || v_truck) && v_CargoMw && v_CargoMw->Exceeded_MaxW(Current_Time))
	{
		if (v_truck)
		{
			v_truck->AddCargo(v_CargoMw, Current_Time); //this will set endloading time
			v_CargoMw->SetCarryingTruck(v_truck); ////////////////////////


			vip_Cargo.pop(v_CargoMw);
			moveVTruck_Toload_Night();
			v_truck->setStartLoadingTime(simTime);
			v_CargoMw = nullptr;
			vip_Cargo.peek(v_CargoMw);
			v_truck = nullptr;
			vip_Truck_Night.peek(v_truck);
		}
		else if (n_truck)
		{
			n_truck->AddCargo(v_CargoMw, Current_Time); //this will set endloading time

			v_CargoMw->SetCarryingTruck(n_truck); //////////////////////////////

			vip_Cargo.pop(v_CargoMw);
			moveNTruck_Toload_Night();
			n_truck->setStartLoadingTime(simTime);
			v_CargoMw = nullptr;
			vip_Cargo.peek(v_CargoMw);
			n_truck = nullptr;
			normal_Truck_Night.peek(n_truck);
		}
	}
	//3nd normal ones
	normal_Truck_Night.peek(n_truck);
	vip_Truck_Night.peek(v_truck);
	NormalCargo* n_CargoMw = nullptr;
	normal_Cargo.peek(n_CargoMw);
	while ((n_truck || v_truck) && n_CargoMw && n_CargoMw->Exceeded_MaxW(Current_Time))
	{
		if (n_truck)
		{
			n_truck->AddCargo(n_CargoMw, Current_Time); //this will set endloading time

			n_CargoMw->SetCarryingTruck(n_truck); //////////////////////////////

			normal_Cargo.dequeue(n_CargoMw);
			moveNTruck_Toload_Night();
			n_truck->setStartLoadingTime(simTime);
			n_CargoMw = nullptr;
			normal_Cargo.peek(n_CargoMw);
			n_truck = nullptr;
			normal_Truck_Night.peek(n_truck);
		}
		else if (v_truck)
		{
			v_truck->AddCargo(n_CargoMw, Current_Time); //this will set endloading time
			n_CargoMw->SetCarryingTruck(v_truck); ////////////////////////

			normal_Cargo.dequeue(n_CargoMw);
			moveVTruck_Toload_Night();
			v_truck->setStartLoadingTime(simTime);
			n_CargoMw = nullptr;
			normal_Cargo.peek(n_CargoMw);
			v_truck = nullptr;
			vip_Truck_Night.peek(v_truck);
		}
	}

	//--------loading cargos before MaxW---------//

	//1st assign vip cargos 
	normal_Truck_Night.peek(n_truck);
	vip_Truck_Night.peek(v_truck);
	special_Truck_Night.peek(s_truck);
	if (!loading_VC)
	{
		if (v_truck && vip_Cargo.getcounter() >= v_truck->GetTruckCapicity())
		{
			VipCargo* v_Cargo = nullptr;
			for (int i = 0; i < v_truck->GetTruckCapicity(); i++)
			{
				vip_Cargo.peek(v_Cargo);
				v_truck->AddCargo(v_Cargo, Current_Time); //this will set endloading time

				v_Cargo->SetCarryingTruck(v_truck); ////////////////////

				vip_Cargo.pop(v_Cargo);
			}
			moveVTruck_Toload_Night();
			v_truck->setStartLoadingTime(simTime);

		}
		else if (n_truck && vip_Cargo.getcounter() >= n_truck->GetTruckCapicity())
		{
			VipCargo* v_Cargo = nullptr;
			for (int i = 0; i < n_truck->GetTruckCapicity(); i++)
			{
				vip_Cargo.peek(v_Cargo);
				n_truck->AddCargo(v_Cargo, Current_Time); //this will set endloading time

				v_Cargo->SetCarryingTruck(n_truck); //////////////////////

				vip_Cargo.pop(v_Cargo);
			}
			moveNTruck_Toload_Night();
			n_truck->setStartLoadingTime(simTime);

		}
		else if (s_truck && vip_Cargo.getcounter() >= s_truck->GetTruckCapicity())
		{
			VipCargo* v_Cargo = nullptr;
			for (int i = 0; i < s_truck->GetTruckCapicity(); i++)
			{
				vip_Cargo.peek(v_Cargo);
				s_truck->AddCargo(v_Cargo, Current_Time); //this will set endloading time

				v_Cargo->SetCarryingTruck(s_truck); /////////////////////

				vip_Cargo.pop(v_Cargo);
			}
			moveSTruck_Toload_Night();
			s_truck->setStartLoadingTime(simTime);

		}
	}
	//2nd assign special cargos
	special_Truck_Night.peek(s_truck);
	if (!loading_SC)
	{
		if (s_truck && special_Cargo.getCount() >= s_truck->GetTruckCapicity())
		{
			SpecialCargo* s_Cargo = nullptr;
			for (int i = 0; i < s_truck->GetTruckCapicity(); i++)
			{
				special_Cargo.peek(s_Cargo);
				s_truck->AddCargo(s_Cargo, Current_Time); //this will set endloading time

				s_Cargo->SetCarryingTruck(s_truck); //////////////////

				special_Cargo.dequeue(s_Cargo);
			}
			moveSTruck_Toload_Night();
			s_truck->setStartLoadingTime(simTime);

		}
	}
	//3rd assign normal cargos
	normal_Truck_Night.peek(n_truck);
	vip_Truck_Night.peek(v_truck);
	if (!loading_NC)
	{
		if (n_truck && normal_Cargo.getCount() >= n_truck->GetTruckCapicity())
		{
			NormalCargo* n_Cargo = nullptr;
			for (int i = 0; i < n_truck->GetTruckCapicity(); i++)
			{
				normal_Cargo.peek(n_Cargo);
				n_truck->AddCargo(n_Cargo, Current_Time); //this will set endloading time

				n_Cargo->SetCarryingTruck(n_truck); /////////////////////

				normal_Cargo.dequeue(n_Cargo);
			}
			moveNTruck_Toload_Night();
			n_truck->setStartLoadingTime(simTime);

		}
		else if (v_truck && normal_Cargo.getCount() >= v_truck->GetTruckCapicity())
		{
			NormalCargo* n_Cargo = nullptr;
			for (int i = 0; i < v_truck->GetTruckCapicity(); i++)
			{
				normal_Cargo.peek(n_Cargo);
				v_truck->AddCargo(n_Cargo, Current_Time); //this will set endloading time

				n_Cargo->SetCarryingTruck(v_truck); /////////////

				normal_Cargo.dequeue(n_Cargo);
			}
			moveVTruck_Toload_Night();
			v_truck->setStartLoadingTime(simTime);

		}
	}
}

void Company::simulate(int x)
{
	loadData();
	bool check = false;
	Cargo* cargo;

	char shift;

	sTruck* struck = nullptr;
	nTruck* ntruck = nullptr;
	vTruck* vtruck = nullptr;

	NormalCargo* ncargo;
	SpecialCargo* scargo;
	VipCargo* vcargo;

	Event* tempevent;



	sTruck* tempstruck;
	nTruck* tempntruck;
	vTruck* tempvtruck;

	PQueue<nTruck*, Time> tempnpqueue;
	PQueue<sTruck*, Time> tempspqueue;
	PQueue<vTruck*, Time> tempvpqueue;

	tempnpqueue.setPriorityOrder(false);
	tempspqueue.setPriorityOrder(false);
	tempvpqueue.setPriorityOrder(false);



	if (x != 1 && x != 2)
	{
		pOut->printString("Silent Mode");
		pOut->printEndl();
		pOut->printString("Simulation starts");
		pOut->printEndl();

	}


	while (((Events.getCount() > 0 || !normal_Cargo.isEmpty() || !special_Cargo.isEmpty() ||
		!vip_Cargo.isEmpty() || !loading_Ntruck.isEmpty() || !loading_Struck.isEmpty() ||
		!loading_Vtruck.isEmpty() || !moving_Ntruck.isEmpty() || !moving_Struck.isEmpty() ||
		!moving_Vtruck.isEmpty() || !Maintenance_NTruck.isEmpty() || !Maintenance_STruck.isEmpty() ||
		!Maintenance_VTruck.isEmpty()) && (NoOfTrucks >= 1 || !Events.isEmpty())) && ((!loading_Ntruck.isEmpty() ||
			!loading_Struck.isEmpty() || !loading_Vtruck.isEmpty() || !moving_Ntruck.isEmpty() || !moving_Struck.isEmpty() ||
			!moving_Vtruck.isEmpty() || !normal_Cargo.isEmpty() || !vip_Cargo.isEmpty() || special_Cargo.isEmpty() ||
			!special_Truck.isEmpty() || !special_Truck_Night.isEmpty() || !Maintenance_NTruck.isEmpty() ||
			!Maintenance_STruck.isEmpty() || !Maintenance_VTruck.isEmpty()) || !Events.isEmpty())) 
	{


		if (Current_Time.getHour() <= 23 && Current_Time.getHour() >= 5)
		{

			while (Events.peek(tempevent) && tempevent->gettime() <= Current_Time)
			{
				tempevent->Apply(this);
				Events.dequeue(tempevent);
				Events.peek(tempevent);
			}

			Assign_Cargos(Current_Time);

			//auto promotion
			NormalCargo* tempC_autop = nullptr;
			normal_Cargo.peek(tempC_autop);
			while (tempC_autop && tempC_autop->Exceeded_Autop(Current_Time))
			{
				normal_Cargo.dequeue(tempC_autop);
				promoteCargo_normalTovip(tempC_autop);
				tempC_autop = nullptr;
				normal_Cargo.peek(tempC_autop);
				this->increaseNumOfPromotedCargos();
			}

		}

		else
		{
			Assign_Cargos_Night ( Current_Time );
		}

		{
			randfail();
			returnfailedtrucks();

			while (!moving_Ntruck.isEmpty() || !moving_Struck.isEmpty() || !moving_Vtruck.isEmpty())
			{
				moving_Ntruck.peek(ntruck);
				if (ntruck != nullptr)
				{
					ntruck->GetCargosInTruck()->peek(cargo);
					while (!moving_Ntruck.isEmpty() && cargo->GetDeliveryTime() == Current_Time && !ntruck->GetCargosInTruck()->isEmpty())
					{
						moveCargo_Todeliver(ntruck);
						ntruck->GetCargosInTruck()->peek(cargo);
					}
				}
				if (!moving_Ntruck.isEmpty())
				{
					moving_Ntruck.pop(tempntruck);
					tempnpqueue.push(tempntruck, tempntruck->GetDeliveryTime());
				}

				moving_Struck.peek(struck);
				if (struck != nullptr)
				{
					struck->GetCargosInTruck()->peek(cargo);
					while (!moving_Struck.isEmpty() && cargo->GetDeliveryTime() == Current_Time && !struck->GetCargosInTruck()->isEmpty())
					{
						moveCargo_Todeliver(struck);
						struck->GetCargosInTruck()->peek(cargo);
					}
				}
				if (!moving_Struck.isEmpty())
				{
					moving_Struck.pop(tempstruck);
					tempspqueue.push(tempstruck, tempstruck->GetDeliveryTime());
				}

				moving_Vtruck.peek(vtruck);
				if (vtruck != nullptr)
				{
					vtruck->GetCargosInTruck()->peek(cargo);
					while (!moving_Vtruck.isEmpty() && cargo->GetDeliveryTime() <= Current_Time && !vtruck->GetCargosInTruck()->isEmpty())
					{
						moveCargo_Todeliver(vtruck);
						vtruck->GetCargosInTruck()->peek(cargo);
					}
				}
				if (!moving_Vtruck.isEmpty())
				{
					moving_Vtruck.pop(tempvtruck);
					tempvpqueue.push(tempvtruck, tempvtruck->GetDeliveryTime());
				}

			}

			while (!tempnpqueue.isEmpty())
			{
				tempnpqueue.pop(tempntruck);
				moving_Ntruck.push(tempntruck, tempntruck->GetDeliveryTime());
			}
			while (!tempspqueue.isEmpty())
			{
				tempspqueue.pop(tempstruck);
				moving_Struck.push(tempstruck, tempstruck->GetDeliveryTime());
			}
			while (!tempvpqueue.isEmpty())
			{
				tempvpqueue.pop(tempvtruck);
				moving_Vtruck.push(tempvtruck, tempvtruck->GetDeliveryTime());
			}


			moving_Ntruck.peek(ntruck);
			while (!moving_Ntruck.isEmpty() && ntruck->GetEndTripTime() <= Current_Time && ntruck->GetCargosInTruck()->isEmpty())
			{
				shift = ntruck->GetShift();

				if (ntruck->GetCurrentNoJourneys() == ntruck->GetNoJourneys())
				{

					moveNTruck_ToMaintenance(Current_Time);



					ntruck->increaseActiveTime(ntruck->getMovingTime());

				}
				else
				{
					if (shift == 'D')
						moveNTruck_Towaiting();
					else if (shift == 'N')
						moveNTruck_Towaiting_Night();

					ntruck->increaseActiveTime(ntruck->getMovingTime());


				}
				moving_Ntruck.peek(ntruck);

			}

			moving_Struck.peek(struck);
			while (!moving_Struck.isEmpty() && struck->GetEndTripTime() <= Current_Time && struck->GetCargosInTruck()->isEmpty())
			{
				shift = struck->GetShift();

				if (struck->GetCurrentNoJourneys() == struck->GetNoJourneys())
				{
					moveSTruck_ToMaintenance(Current_Time);
					struck->increaseActiveTime(struck->getMovingTime());

				}
				else
				{
					if (shift == 'D')
						moveSTruck_Towaiting();
					else if (shift == 'N')
						moveNTruck_Towaiting_Night();
					struck->increaseActiveTime(struck->getMovingTime());

				}
				moving_Struck.peek(struck);

			}

			moving_Vtruck.peek(vtruck);
			while (!moving_Vtruck.isEmpty() && vtruck->GetEndTripTime() <= Current_Time && vtruck->GetCargosInTruck()->isEmpty())
			{
				shift = vtruck->GetShift();

				if (vtruck->GetCurrentNoJourneys() == vtruck->GetNoJourneys())
				{
					moveVTruck_ToMaintenance(Current_Time);
					vtruck->increaseActiveTime(vtruck->getMovingTime());

				}
				else
				{
					if (shift == 'D')
						moveVTruck_Towaiting();
					else if (shift == 'N')
						moveVTruck_Towaiting_Night();

					vtruck->increaseActiveTime(vtruck->getMovingTime());

				}
				moving_Vtruck.peek(vtruck);

			}

			loading_Ntruck.peek(ntruck);
			while (!loading_Ntruck.isEmpty() && ntruck->GetEndLoadingTime() <= Current_Time)
			{

				ntruck->increasetNJ(1);
				ntruck->increasetDC(ntruck->GetCargosInTruck()->getcounter());

				ntruck->setcdtforcargos(Current_Time);
				moveNTruck_Tomove();
				ntruck->setMovingTime(ntruck->GetDeliveryTime() - Current_Time);
				ntruck->increaseActiveTime(ntruck->GetDeliveryTime() - ntruck->getStartLoadingTime());
				ntruck->SetCurrentNoJourneys(ntruck->GetCurrentNoJourneys() + 1);
				loading_Ntruck.peek(ntruck);
			}

			loading_Struck.peek(struck);
			while (!loading_Struck.isEmpty() && struck->GetEndLoadingTime() <= Current_Time)
			{
				moveSTruck_Tomove();

				struck->increasetNJ(1);
				struck->increasetDC(struck->GetCargosInTruck()->getcounter());

				struck->SetCurrentNoJourneys(struck->GetCurrentNoJourneys() + 1);
				struck->setcdtforcargos(Current_Time);
				struck->setMovingTime(struck->GetDeliveryTime() - Current_Time);
				struck->increaseActiveTime(struck->GetDeliveryTime() - struck->getStartLoadingTime());

				loading_Struck.peek(struck);
			}

			loading_Vtruck.peek(vtruck);
			while (!loading_Vtruck.isEmpty() && vtruck->GetEndLoadingTime() <= Current_Time)
			{
				moveVTruck_Tomove();
				vtruck->SetCurrentNoJourneys(vtruck->GetCurrentNoJourneys() + 1);


				vtruck->increasetNJ(1);
				vtruck->increasetDC(vtruck->GetCargosInTruck()->getcounter());

				vtruck->setcdtforcargos(Current_Time);
				vtruck->setMovingTime(vtruck->GetDeliveryTime() - Current_Time);
				vtruck->increaseActiveTime(vtruck->GetDeliveryTime() - vtruck->getStartLoadingTime());

				loading_Vtruck.peek(vtruck);
			}

			Maintenance_NTruck.peek(ntruck);
			while (!Maintenance_NTruck.isEmpty() && ntruck->GetEndCheckupTime() <= Current_Time)
			{
				shift = ntruck->GetShift();
				if (shift == 'D')
					moveNTruck_FMTowaiting();
				else if (shift == 'N')
					moveNTruck_FMTowaiting_Night();

				Maintenance_NTruck.peek(ntruck);
			}

			Maintenance_STruck.peek(struck);
			while (!Maintenance_STruck.isEmpty() && struck->GetEndCheckupTime() <= Current_Time)
			{
				shift = struck->GetShift();
				if (shift == 'D')
					moveSTruck_FMTowaiting();
				else if (shift == 'N')
					moveSTruck_FMTowaiting_Night();

				Maintenance_STruck.peek(struck);
			}

			Maintenance_VTruck.peek(vtruck);
			while (!Maintenance_VTruck.isEmpty() && vtruck->GetEndCheckupTime() <= Current_Time)
			{
				shift = vtruck->GetShift();
				if (shift == 'D')
					moveVTruck_FMTowaiting();
				else if (shift == 'N')
					moveVTruck_FMTowaiting_Night();

				Maintenance_VTruck.peek(vtruck);
			}


		}




		if (x == 1)
		{
			InterActiveMode(Current_Time);
			pOut->printString("Press Enter to Continue the Simulation");
			pOut->printEndl();
			pOut->WaitEnterPress();
		}


		else if (x == 2)
		{
			InterActiveMode(Current_Time);
			pOut->printEndl();
			sleep_until(system_clock::now() + seconds(1));
		}
		if (!check)
		{
			pOut->WaitEnterPress();
		}


		Current_Time = Current_Time + 1;
		check = true;
	}

	this->generateOutputFile(Current_Time);

	if (x != 1 && x != 2)
	{
		pOut->printString("Simulation ends, Output file created");
	}

}

void Company::randfail()
{
	PQueue<nTruck*, Time> tempmoving_Ntruck;
	PQueue<vTruck*, Time> tempmoving_Vtruck;
	PQueue<sTruck*, Time> tempmoving_Struck;

	nTruck* tempntruck;
	sTruck* tempstruck;
	vTruck* tempvtruck;


	while (!moving_Ntruck.isEmpty())
	{
		moving_Ntruck.pop(tempntruck);
		tempntruck->randomfail();
		tempmoving_Ntruck.push(tempntruck, tempntruck->GetDeliveryTime());

	}

	while (!moving_Struck.isEmpty())
	{
		moving_Struck.pop(tempstruck);
		tempstruck->randomfail();
		tempmoving_Struck.push(tempstruck, tempstruck->GetDeliveryTime());
	}

	while (!moving_Vtruck.isEmpty())
	{
		moving_Vtruck.pop(tempvtruck);
		tempvtruck->randomfail();
		tempmoving_Vtruck.push(tempvtruck, tempvtruck->GetDeliveryTime());
	}

	while (!tempmoving_Ntruck.isEmpty())
	{
		tempmoving_Ntruck.pop(tempntruck);
		moving_Ntruck.push(tempntruck, tempntruck->GetDeliveryTime());
	}

	while (!tempmoving_Struck.isEmpty())
	{
		tempmoving_Struck.pop(tempstruck);
		moving_Struck.push(tempstruck, tempstruck->GetDeliveryTime());
	}

	while (!tempmoving_Vtruck.isEmpty())
	{
		tempmoving_Vtruck.pop(tempvtruck);
		moving_Vtruck.push(tempvtruck, tempvtruck->GetDeliveryTime());
	}

}

void Company::returnfailedtrucks()
{
	PQueue<nTruck*, Time> tempmoving_Ntruck;
	PQueue<vTruck*, Time> tempmoving_Vtruck;
	PQueue<sTruck*, Time> tempmoving_Struck;

	nTruck* tempntruck;
	sTruck* tempstruck;
	vTruck* tempvtruck;

	PQueue<Cargo*, float>* tempcargoqueue = nullptr;

	Cargo* tempcargo;
	NormalCargo* tempnormalcargo;
	SpecialCargo* tempspecialcargo;
	VipCargo* tempvipcargo;

	Time t;

	while (!moving_Ntruck.isEmpty())
	{
		moving_Ntruck.pop(tempntruck);

		if (tempntruck->Getfail())
		{
			tempcargoqueue = tempntruck->GetCargosInTruck();

			t = Current_Time + tempntruck->GetCheckupDuration();

			if (!tempcargoqueue->isEmpty())
			{
				tempcargoqueue->peek(tempcargo);


				if (!tempcargoqueue->isEmpty())
					t = t + tempcargo->GetLoadUnloadTime();

			}

			tempntruck->SetEndCheckupTime(t);


			Maintenance_NTruck.enqueue(tempntruck);


			while (!tempcargoqueue->isEmpty())
			{
				tempcargoqueue->pop(tempcargo);
				if (tempcargo->GetType() == Normal)
				{
					tempnormalcargo = (NormalCargo*)tempcargo;
					tempnormalcargo->SetType(Normal);
					normal_Cargo.enqueue(tempnormalcargo);
				}
				else if (tempcargo->GetType() == Special)
				{
					tempspecialcargo = (SpecialCargo*)tempcargo;
					tempspecialcargo->SetType(Special);
					special_Cargo.enqueue(tempspecialcargo);
				}
				else if (tempcargo->GetType() == Vip)
				{
					tempvipcargo = (VipCargo*)tempcargo;
					tempvipcargo->SetType(Vip);
					float Priority;
					Priority = (12 / tempcargo->GetpreparationTime().getDay()) + 25 / (tempcargo->GetpreparationTime().getHour()) + (50 / tempvipcargo->GetDelieveryDistance()) + (6 * tempvipcargo->GetCost());
					vip_Cargo.push(tempvipcargo, Priority);
				}
			}
		}
		else
		{

			tempmoving_Ntruck.push(tempntruck, tempntruck->GetDeliveryTime());

		}
	}
	while (!moving_Struck.isEmpty())
	{
		moving_Struck.pop(tempstruck);

		if (tempstruck->Getfail())
		{
			tempcargoqueue = tempstruck->GetCargosInTruck();
			t = Current_Time + tempstruck->GetCheckupDuration();

			if (!tempcargoqueue->isEmpty())
			{
				tempcargoqueue->peek(tempcargo);


				if (!tempcargoqueue->isEmpty())
					t = t + tempcargo->GetLoadUnloadTime();

			}

			tempstruck->SetEndCheckupTime(t);

			Maintenance_STruck.enqueue(tempstruck);

			while (!tempcargoqueue->isEmpty())
			{
				tempcargoqueue->pop(tempcargo);
				if (tempcargo->GetType() == Normal)
				{
					tempnormalcargo = (NormalCargo*)tempcargo;
					tempnormalcargo->SetType(Normal);
					normal_Cargo.enqueue(tempnormalcargo);
				}
				else if (tempcargo->GetType() == Special)
				{
					tempspecialcargo = (SpecialCargo*)tempcargo;
					tempspecialcargo->SetType(Special);
					special_Cargo.enqueue(tempspecialcargo);
				}
				else if (tempcargo->GetType() == Vip)
				{
					tempvipcargo = (VipCargo*)tempcargo;
					tempvipcargo->SetType(Vip);
					float Priority;
					Priority = (2 * Current_Time.getDay()) + (Current_Time.getHour()) + (50 / tempvipcargo->GetDelieveryDistance()) + (6 * tempvipcargo->GetCost());
					vip_Cargo.push(tempvipcargo, Priority);
				}
			}
		}
		else
		{

			tempmoving_Struck.push(tempstruck, tempstruck->GetDeliveryTime());

		}
	}

	while (!moving_Vtruck.isEmpty())
	{
		moving_Vtruck.pop(tempvtruck);

		if (tempvtruck->Getfail())
		{
			tempcargoqueue = tempvtruck->GetCargosInTruck();
			t = Current_Time + tempvtruck->GetCheckupDuration();

			if (!tempcargoqueue->isEmpty())
			{
				tempcargoqueue->peek(tempcargo);


				if (!tempcargoqueue->isEmpty())
					t = t + tempcargo->GetLoadUnloadTime();

			}

			tempvtruck->SetEndCheckupTime(t);
			Maintenance_VTruck.enqueue(tempvtruck);

			while (!tempcargoqueue->isEmpty())
			{
				tempcargoqueue->pop(tempcargo);
				if (tempcargo->GetType() == Normal)
				{
					tempnormalcargo = (NormalCargo*)tempcargo;
					tempnormalcargo->SetType(Normal);
					normal_Cargo.enqueue(tempnormalcargo);
				}
				else if (tempcargo->GetType() == Special)
				{
					tempspecialcargo = (SpecialCargo*)tempcargo;
					tempspecialcargo->SetType(Special);
					special_Cargo.enqueue(tempspecialcargo);
				}
				else if (tempcargo->GetType() == Vip)
				{
					tempvipcargo = (VipCargo*)tempcargo;
					tempvipcargo->SetType(Vip);
					float Priority;
					Priority = (2 * Current_Time.getDay()) + (Current_Time.getHour()) + (50 / tempvipcargo->GetDelieveryDistance()) + (6 * tempvipcargo->GetCost());
					vip_Cargo.push(tempvipcargo, Priority);
				}
			}
		}
		else
		{

			tempmoving_Vtruck.push(tempvtruck, tempvtruck->GetDeliveryTime());

		}
	}

	while (!tempmoving_Ntruck.isEmpty())
	{
		tempmoving_Ntruck.pop(tempntruck);
		moving_Ntruck.push(tempntruck, tempntruck->GetDeliveryTime());
	}

	while (!tempmoving_Struck.isEmpty())
	{
		tempmoving_Struck.pop(tempstruck);
		moving_Struck.push(tempstruck, tempstruck->GetDeliveryTime());
	}

	while (!tempmoving_Vtruck.isEmpty())
	{
		tempmoving_Vtruck.pop(tempvtruck);
		moving_Vtruck.push(tempvtruck, tempvtruck->GetDeliveryTime());
	}
}

void Company::generateOutputFile ( Time currenttime )
{

	int k = 1;
	string file = "Data out.txt";
	ofstream outfile ( file );

	NormalCargo* ntempcargo;
	SpecialCargo* stempcargo;
	VipCargo* vtempcargo;

	Queue<NormalCargo*> tempnqueue;
	Queue<SpecialCargo*> tempsqueue;
	Queue<VipCargo*> tempvqueue;


	delivered_NCargo.peek ( ntempcargo );
	delivered_SCargo.peek ( stempcargo );
	delivered_VCargo.peek ( vtempcargo );

	PQueue<nTruck*, Time> tempmoving_Ntruck;
	PQueue<nTruck*, Time> temploading_Ntruck;

	tempmoving_Ntruck.setPriorityOrder ( false );
	temploading_Ntruck.setPriorityOrder ( false );

	nTruck* ntemptruck;
	int n = 0;

	Time totalWaitingTime ( 0, 0 );

	while ( !moving_Ntruck.isEmpty ( ) )
	{
		moving_Ntruck.pop ( ntemptruck );
		tempmoving_Ntruck.push ( ntemptruck, ntemptruck->GetDeliveryTime ( ) );
		n = n + ntemptruck->GetCargosInTruck ( )->getcounter ( );
	}
	while ( !loading_Ntruck.isEmpty ( ) )
	{
		loading_Ntruck.pop ( ntemptruck );
		temploading_Ntruck.push ( ntemptruck, ntemptruck->GetDeliveryTime ( ) );
		n = n + ntemptruck->GetCargosInTruck ( )->getcounter ( );
	}

	while ( !tempmoving_Ntruck.isEmpty ( ) )
	{
		tempmoving_Ntruck.pop ( ntemptruck );
		moving_Ntruck.push ( ntemptruck, ntemptruck->GetDeliveryTime ( ) );
	}
	while ( !temploading_Ntruck.isEmpty ( ) )
	{
		temploading_Ntruck.pop ( ntemptruck );
		loading_Ntruck.push ( ntemptruck, ntemptruck->GetEndLoadingTime ( ) );
	}


	outfile << "CDT  ID  PT   WT  TID" << endl;
	while ( !delivered_NCargo.isEmpty() || !delivered_SCargo.isEmpty() || !delivered_VCargo.isEmpty() )
	{

		delivered_NCargo.peek ( ntempcargo ); 
		delivered_SCargo.peek ( stempcargo );
		delivered_VCargo.peek ( vtempcargo );
		if ( !delivered_NCargo.isEmpty ( ) && ((delivered_SCargo.isEmpty ( ) || (ntempcargo->GetDeliveryTime ( ) <= stempcargo->GetDeliveryTime ( ))) && (delivered_VCargo.isEmpty ( ) || ntempcargo->GetDeliveryTime ( ) <= vtempcargo->GetDeliveryTime ( ))) )


		{
			delivered_NCargo.dequeue ( ntempcargo );
			tempnqueue.enqueue ( ntempcargo );
			outfile << ntempcargo->GetDeliveryTime ( ).getDay ( ) << ":" << ntempcargo->GetDeliveryTime ( ).getHour ( ) << "  ";
			outfile << ntempcargo->GetID ( ) << "  " << ntempcargo->GetpreparationTime ( ).getDay ( ) << ":" << ntempcargo->GetpreparationTime ( ).getHour ( ) << "  ";


			if ( (ntempcargo->getMoveTime ( ).getHour ( ) - ntempcargo->GetpreparationTime ( ).getHour ( )) < 0 )
			{
				outfile << ntempcargo->getMoveTime ( ).getDay ( ) - ntempcargo->GetpreparationTime ( ).getDay ( ) - 1 << ":" << ntempcargo->getMoveTime ( ).getHour ( ) - ntempcargo->GetpreparationTime ( ).getHour ( ) + 24 << "  ";
				totalWaitingTime = totalWaitingTime + ntempcargo->getMoveTime ( ) - ntempcargo->GetpreparationTime ( );
			}
			else
			{
				outfile << ntempcargo->getMoveTime ( ).getDay ( ) - ntempcargo->GetpreparationTime ( ).getDay ( ) << ":" << ntempcargo->getMoveTime ( ).getHour ( ) - ntempcargo->GetpreparationTime ( ).getHour ( ) << "  ";
				totalWaitingTime = totalWaitingTime + ntempcargo->getMoveTime ( ) - ntempcargo->GetpreparationTime ( );
			}

			outfile << ntempcargo->GetCarryingTruck ( )->GetId ( );
		}


		else if ( !delivered_SCargo.isEmpty ( ) && ((delivered_NCargo.isEmpty ( ) || stempcargo->GetDeliveryTime ( ) <= ntempcargo->GetDeliveryTime ( )) && (delivered_VCargo.isEmpty ( ) || stempcargo->GetDeliveryTime ( ) <= vtempcargo->GetDeliveryTime ( ))) )

		{
			delivered_SCargo.dequeue ( stempcargo );
			tempsqueue.enqueue ( stempcargo );
			outfile << stempcargo->GetDeliveryTime ( ).getDay ( ) << ":" << stempcargo->GetDeliveryTime ( ).getHour ( ) << "  ";
			outfile << stempcargo->GetID ( ) << "  " << stempcargo->GetpreparationTime ( ).getDay ( ) << ":" << stempcargo->GetpreparationTime ( ).getHour ( ) << "  ";

			if ( (stempcargo->getMoveTime ( ).getHour ( ) - stempcargo->GetpreparationTime ( ).getHour ( )) < 0 )
			{
				outfile << stempcargo->getMoveTime ( ).getDay ( ) - stempcargo->GetpreparationTime ( ).getDay ( ) - 1 << ":" << stempcargo->getMoveTime ( ).getHour ( ) - stempcargo->GetpreparationTime ( ).getHour ( ) + 24 << "  ";
				totalWaitingTime = totalWaitingTime + stempcargo->getMoveTime ( ) - stempcargo->GetpreparationTime ( );
			}
			else
			{
				outfile << stempcargo->getMoveTime ( ).getDay ( ) - stempcargo->GetpreparationTime ( ).getDay ( ) << ":" << stempcargo->getMoveTime ( ).getHour ( ) - stempcargo->GetpreparationTime ( ).getHour ( ) << "  ";
				totalWaitingTime = totalWaitingTime + stempcargo->getMoveTime ( ) - stempcargo->GetpreparationTime ( );
			}
			outfile << stempcargo->GetCarryingTruck ( )->GetId ( );
		}


		else if ( !delivered_VCargo.isEmpty ( ) && ((delivered_NCargo.isEmpty ( ) || vtempcargo->GetDeliveryTime ( ) <= ntempcargo->GetDeliveryTime ( )) && (delivered_SCargo.isEmpty ( ) || vtempcargo->GetDeliveryTime ( ) <= stempcargo->GetDeliveryTime ( ))) )

		{
			delivered_VCargo.dequeue ( vtempcargo );
			tempvqueue.enqueue ( vtempcargo );
			outfile << vtempcargo->GetDeliveryTime ( ).getDay ( ) << ":" << vtempcargo->GetDeliveryTime ( ).getHour ( ) << "  ";
			outfile << vtempcargo->GetID ( ) << "  " << vtempcargo->GetpreparationTime ( ).getDay ( ) << ":" << vtempcargo->GetpreparationTime ( ).getHour ( ) << "  ";

			if ( (vtempcargo->getMoveTime ( ).getHour ( ) - vtempcargo->GetpreparationTime ( ).getHour ( )) < 0 )
			{
				outfile << vtempcargo->getMoveTime ( ).getDay ( ) - vtempcargo->GetpreparationTime ( ).getDay ( ) - 1 << ":" << vtempcargo->getMoveTime ( ).getHour ( ) - vtempcargo->GetpreparationTime ( ).getHour ( ) + 24 << "  ";
				totalWaitingTime = totalWaitingTime + vtempcargo->getMoveTime ( ) - vtempcargo->GetpreparationTime ( );
			}
			else
			{
				outfile << vtempcargo->getMoveTime ( ).getDay ( ) - vtempcargo->GetpreparationTime ( ).getDay ( ) << ":" << vtempcargo->getMoveTime ( ).getHour ( ) - vtempcargo->GetpreparationTime ( ).getHour ( ) << "  ";
				totalWaitingTime = totalWaitingTime + vtempcargo->getMoveTime ( ) - vtempcargo->GetpreparationTime ( );
			}
			outfile << vtempcargo->GetCarryingTruck ( )->GetId ( );
		}
		outfile << endl;

	}


	while ( !tempnqueue.isEmpty ( ) )
	{
		tempnqueue.dequeue ( ntempcargo );
		delivered_NCargo.enqueue ( ntempcargo );
	}

	while ( !tempsqueue.isEmpty ( ) )
	{
		tempsqueue.dequeue ( stempcargo );
		delivered_SCargo.enqueue ( stempcargo );
	}

	while ( !tempvqueue.isEmpty ( ) )
	{
		tempvqueue.dequeue ( vtempcargo );
		delivered_VCargo.enqueue ( vtempcargo );
	}

	outfile << "..............................................." << endl << "..............................................." << endl;

	outfile << "Cargos: " << this->getTotalNumofNormalCargos ( ) + this->getTotalNumofSpecialCargos ( ) + this->getTotalNumofVipCargos ( );
	outfile << " [N: " << this->getTotalNumofNormalCargos ( ) << ", S: " << this->getTotalNumofSpecialCargos ( ) << ", V: " << this->getTotalNumofVipCargos ( ) << "]" << endl;

	totalWaitingTime = totalWaitingTime / (delivered_NCargo.getCount ( ) + delivered_SCargo.getCount ( ) + delivered_VCargo.getCount ( ));
	
	outfile << "Cargo Avg Wait = ";
	outfile << totalWaitingTime.getDay ( ) << ":" << totalWaitingTime.getHour ( ) << endl;
	
	
	if ( totalNumOfNormalCargos != 0 )
		outfile << "Auto-promoted Caros: " << int ( float ( this->getTotalNumofPromotedCargos ( ) ) / totalNumOfNormalCargos * 100.0 ) << "%" << endl;
	else
		outfile << "Auto-promoted Caros: " << "0" << "%" << endl;

	outfile << "Trucks: " << this->getTotalNumofNormalTrucks ( ) + this->getTotalNumofSpecialTrucks ( ) + this->getTotalNumofVipTrucks ( ) << " [N:";
	outfile << this->getTotalNumofNormalTrucks ( ) << ", S: " << this->getTotalNumofSpecialTrucks ( ) << ", V: " << this->getTotalNumofVipTrucks ( ) << "]" << endl;

	Time t;
	int x;
	t = this->getTotalAvgTimeOfNormalTrucks ( ) + this->getTotalAvgTimeOfSpecialTrucks ( ) + this->getTotalAvgTimeOfVipTrucks ( );
	t = t / (this->getTotalNumofNormalTrucks ( ) + this->getTotalNumofSpecialTrucks ( ) + this->getTotalNumofVipTrucks ( ));
	x = ((t.getDay ( ) * 24.0 + float ( t.getHour ( ) )) / (currenttime.getDay ( ) * 24.0 + currenttime.getHour ( ))) * 100;
	outfile << "Avg Active time = " << x << "%" << endl;


	outfile << "Avg utilization = " << this->getTotalTruckUtilization ( currenttime ) << "%" << endl;


}

int Company::getTotalNumofNormalCargos ( )
{
	PQueue<nTruck*, Time> tempmoving_Ntruck;
	PQueue<nTruck*, Time> temploading_Ntruck;

	nTruck* ntemptruck;
	int n = 0;

	while ( !moving_Ntruck.isEmpty ( ) )
	{
		moving_Ntruck.pop ( ntemptruck );
		tempmoving_Ntruck.push ( ntemptruck, ntemptruck->GetDeliveryTime ( ) );
		n = n + ntemptruck->GetCargosInTruck ( )->getcounter ( );
	}
	while ( !loading_Ntruck.isEmpty ( ) )
	{
		loading_Ntruck.pop ( ntemptruck );
		temploading_Ntruck.push ( ntemptruck, ntemptruck->GetDeliveryTime ( ) );
		n = n + ntemptruck->GetCargosInTruck ( )->getcounter ( );
	}

	while ( !tempmoving_Ntruck.isEmpty ( ) )
	{
		tempmoving_Ntruck.pop ( ntemptruck );
		moving_Ntruck.push ( ntemptruck, ntemptruck->GetDeliveryTime ( ) );
	}
	while ( !temploading_Ntruck.isEmpty ( ) )
	{
		temploading_Ntruck.pop ( ntemptruck );
		loading_Ntruck.push ( ntemptruck, ntemptruck->GetEndLoadingTime ( ) );
	}
	return (normal_Cargo.getCount ( ) + n + delivered_NCargo.getCount ( ));
}

int Company::getTotalNumofSpecialCargos ( )
{
	PQueue<sTruck*, Time> tempmoving_Struck;
	PQueue<sTruck*, Time> temploading_Struck;

	sTruck* stemptruck;
	int n = 0;

	while ( !moving_Struck.isEmpty ( ) )
	{
		moving_Struck.pop ( stemptruck );
		tempmoving_Struck.push ( stemptruck, stemptruck->GetDeliveryTime ( ) );
		n = n + stemptruck->GetCargosInTruck ( )->getcounter ( );
	}
	while ( !loading_Struck.isEmpty ( ) )
	{
		loading_Struck.pop ( stemptruck );
		temploading_Struck.push ( stemptruck, stemptruck->GetDeliveryTime ( ) );
		n = n + stemptruck->GetCargosInTruck ( )->getcounter ( );
	}

	while ( !tempmoving_Struck.isEmpty ( ) )
	{
		tempmoving_Struck.pop ( stemptruck );
		moving_Struck.push ( stemptruck, stemptruck->GetDeliveryTime ( ) );
	}
	while ( !temploading_Struck.isEmpty ( ) )
	{
		temploading_Struck.pop ( stemptruck );
		loading_Struck.push ( stemptruck, stemptruck->GetEndLoadingTime ( ) );
	}
	return (special_Cargo.getCount ( ) + n + delivered_SCargo.getCount ( ));
}

int Company::getTotalNumofVipCargos ( )
{


	PQueue<vTruck*, Time> tempmoving_Vtruck;
	PQueue<vTruck*, Time> temploading_Vtruck;

	vTruck* vtemptruck;
	int n = 0;

	while ( !moving_Vtruck.isEmpty ( ) )
	{
		moving_Vtruck.pop ( vtemptruck );
		tempmoving_Vtruck.push ( vtemptruck, vtemptruck->GetDeliveryTime ( ) );
		n = n + vtemptruck->GetCargosInTruck ( )->getcounter ( );
	}
	while ( !loading_Vtruck.isEmpty ( ) )
	{
		loading_Vtruck.pop ( vtemptruck );
		temploading_Vtruck.push ( vtemptruck, vtemptruck->GetDeliveryTime ( ) );
		n = n + vtemptruck->GetCargosInTruck ( )->getcounter ( );
	}

	while ( !tempmoving_Vtruck.isEmpty ( ) )
	{
		tempmoving_Vtruck.pop ( vtemptruck );
		moving_Vtruck.push ( vtemptruck, vtemptruck->GetDeliveryTime ( ) );
	}
	while ( !temploading_Vtruck.isEmpty ( ) )
	{
		temploading_Vtruck.pop ( vtemptruck );
		loading_Vtruck.push ( vtemptruck, vtemptruck->GetEndLoadingTime ( ) );
	}

	return (vip_Cargo.getcounter ( ) + n + delivered_VCargo.getCount ( ));
}


int Company::getTotalNumofPromotedCargos ( )
{
	return totalNumOfPromotedCargos;
}

int Company::getTotalNumofNormalTrucks ( )
{
	return normal_Truck_Night.getcounter()+normal_Truck.getcounter ( ) + loading_Ntruck.getcounter ( ) + moving_Ntruck.getcounter ( ) + Maintenance_NTruck.getCount ( );
}

int Company::getTotalNumofSpecialTrucks ( )
{
	return special_Truck_Night.getcounter()+special_Truck.getcounter ( ) + loading_Struck.getcounter ( ) + moving_Struck.getcounter ( ) + Maintenance_STruck.getCount ( );
}

int Company::getTotalNumofVipTrucks ( )
{
	return vip_Truck_Night.getcounter()+vip_Truck.getcounter ( ) + loading_Vtruck.getcounter ( ) + moving_Vtruck.getcounter ( ) + Maintenance_VTruck.getCount ( );
}

Time Company::getTotalAvgTimeOfNormalTrucks ( )
{
	nTruck* tempntruck;

	Queue<nTruck*> tempnqueue;

	PQueue<nTruck*, Time> tempnpqueue;


	Time activeTime ( 0, 0 );

	while ( !normal_Truck.isEmpty ( ) )
	{
		normal_Truck.pop ( tempntruck );
		tempnqueue.enqueue ( tempntruck );
		activeTime = activeTime + tempntruck->getActiveTime ( );
	}
	while ( !tempnqueue.isEmpty ( ) )
	{
		tempnqueue.dequeue ( tempntruck );
		normal_Truck.push ( tempntruck, tempntruck->GetPriority ( ) );
	}
	///////
	while ( !normal_Truck_Night.isEmpty ( ) )
	{
		normal_Truck_Night.pop ( tempntruck );
		tempnqueue.enqueue ( tempntruck );
		activeTime = activeTime + tempntruck->getActiveTime ( );
	}
	while ( !tempnqueue.isEmpty ( ) )
	{
		tempnqueue.dequeue ( tempntruck );
		normal_Truck_Night.push ( tempntruck, tempntruck->GetPriority ( ) );
	}	
	///////
	while ( !loading_Ntruck.isEmpty ( ) )
	{
		loading_Ntruck.pop ( tempntruck );
		tempnpqueue.push ( tempntruck, tempntruck->GetEndLoadingTime ( ) );
		activeTime = activeTime + tempntruck->getActiveTime ( );
	}
	while ( !tempnpqueue.isEmpty ( ) )
	{
		tempnpqueue.pop ( tempntruck );
		loading_Ntruck.push ( tempntruck, tempntruck->GetEndLoadingTime ( ) );
	}
	/////
	while ( !Maintenance_NTruck.isEmpty ( ) )
	{
		Maintenance_NTruck.dequeue ( tempntruck );
		tempnqueue.enqueue ( tempntruck );
		activeTime = activeTime + tempntruck->getActiveTime ( );
	}
	while ( !tempnqueue.isEmpty ( ) )
	{
		tempnqueue.dequeue ( tempntruck );
		Maintenance_NTruck.enqueue ( tempntruck );
	}
	//////
	while ( !moving_Ntruck.isEmpty ( ) )
	{
		moving_Ntruck.pop ( tempntruck );
		tempnpqueue.push ( tempntruck, tempntruck->GetEndLoadingTime ( ) );
		activeTime = activeTime + tempntruck->getActiveTime ( );
	}
	while ( !tempnpqueue.isEmpty ( ) )
	{
		tempnpqueue.pop ( tempntruck );
		moving_Ntruck.push ( tempntruck, tempntruck->GetEndLoadingTime ( ) );
	}

	return activeTime;
}

Time Company::getTotalAvgTimeOfSpecialTrucks ( )
{
	sTruck* tempstruck;

	Queue<sTruck*> tempsqueue;

	PQueue<sTruck*, Time> tempspqueue;

	Time activeTime ( 0, 0 );

	while ( !special_Truck.isEmpty ( ) )
	{
		special_Truck.pop ( tempstruck );
		tempsqueue.enqueue ( tempstruck );
		activeTime = activeTime + tempstruck->getActiveTime ( );
	}
	while ( !tempsqueue.isEmpty ( ) )
	{
		tempsqueue.dequeue ( tempstruck );
		special_Truck.push ( tempstruck, tempstruck->GetPriority ( ) );
	}
	///////
	while ( !special_Truck_Night.isEmpty ( ) )
	{
		special_Truck_Night.pop ( tempstruck );
		tempsqueue.enqueue ( tempstruck );
		activeTime = activeTime + tempstruck->getActiveTime ( );
	}
	while ( !tempsqueue.isEmpty ( ) )
	{
		tempsqueue.dequeue ( tempstruck );
		special_Truck_Night.push ( tempstruck, tempstruck->GetPriority ( ) );
	}
	///////
	while ( !loading_Struck.isEmpty ( ) )
	{
		loading_Struck.pop ( tempstruck );
		tempspqueue.push ( tempstruck, tempstruck->GetEndLoadingTime ( ) );
		activeTime = activeTime + tempstruck->getActiveTime ( );
	}
	while ( !tempspqueue.isEmpty ( ) )
	{
		tempspqueue.pop ( tempstruck );
		loading_Struck.push ( tempstruck, tempstruck->GetEndLoadingTime ( ) );
	}
	/////
	while ( !Maintenance_STruck.isEmpty ( ) )
	{
		Maintenance_STruck.dequeue ( tempstruck );
		tempsqueue.enqueue ( tempstruck );
		activeTime = activeTime + tempstruck->getActiveTime ( );
	}
	while ( !tempsqueue.isEmpty ( ) )
	{
		tempsqueue.dequeue ( tempstruck );
		Maintenance_STruck.enqueue ( tempstruck );
	}
	//////
	while ( !moving_Struck.isEmpty ( ) )
	{
		moving_Struck.pop ( tempstruck );
		tempspqueue.push ( tempstruck, tempstruck->GetEndLoadingTime ( ) );
		activeTime = activeTime + tempstruck->getActiveTime ( );
	}
	while ( !tempspqueue.isEmpty ( ) )
	{
		tempspqueue.pop ( tempstruck );
		moving_Struck.push ( tempstruck, tempstruck->GetEndLoadingTime ( ) );
	}
	return activeTime;

}

Time Company::getTotalAvgTimeOfVipTrucks ( )
{

	vTruck* tempvtruck;

	Queue<vTruck*> tempvqueue;

	PQueue<vTruck*, Time> tempvpqueue;

	Time activeTime ( 0, 0 );

	while ( !vip_Truck.isEmpty ( ) )
	{
		vip_Truck.pop ( tempvtruck );
		tempvqueue.enqueue ( tempvtruck );
		activeTime = activeTime + tempvtruck->getActiveTime ( );
	}
	while ( !tempvqueue.isEmpty ( ) )
	{
		tempvqueue.dequeue ( tempvtruck );
		vip_Truck.push ( tempvtruck, tempvtruck->GetPriority ( ) );
	}
	///////
	while ( !vip_Truck_Night.isEmpty ( ) )
	{
		vip_Truck_Night.pop ( tempvtruck );
		tempvqueue.enqueue ( tempvtruck );
		activeTime = activeTime + tempvtruck->getActiveTime ( );
	}
	while ( !tempvqueue.isEmpty ( ) )
	{
		tempvqueue.dequeue ( tempvtruck );
		vip_Truck_Night.push ( tempvtruck, tempvtruck->GetPriority ( ) );
	}
	///////
	while ( !loading_Vtruck.isEmpty ( ) )
	{
		loading_Vtruck.pop ( tempvtruck );
		tempvpqueue.push ( tempvtruck, tempvtruck->GetEndLoadingTime ( ) );
		activeTime = activeTime + tempvtruck->getActiveTime ( );
	}
	while ( !tempvpqueue.isEmpty ( ) )
	{
		tempvpqueue.pop ( tempvtruck );
		loading_Vtruck.push ( tempvtruck, tempvtruck->GetEndLoadingTime ( ) );
	}
	/////
	while ( !Maintenance_VTruck.isEmpty ( ) )
	{
		Maintenance_VTruck.dequeue ( tempvtruck );
		tempvqueue.enqueue ( tempvtruck );
		activeTime = activeTime + tempvtruck->getActiveTime ( );
	}
	while ( !tempvqueue.isEmpty ( ) )
	{
		tempvqueue.dequeue ( tempvtruck );
		Maintenance_VTruck.enqueue ( tempvtruck );
	}
	//////
	while ( !moving_Vtruck.isEmpty ( ) )
	{
		moving_Vtruck.pop ( tempvtruck );
		tempvpqueue.push ( tempvtruck, tempvtruck->GetEndLoadingTime ( ) );
		activeTime = activeTime + tempvtruck->getActiveTime ( );
	}
	while ( !tempvpqueue.isEmpty ( ) )
	{
		tempvpqueue.pop ( tempvtruck );
		moving_Vtruck.push ( tempvtruck, tempvtruck->GetEndLoadingTime ( ) );
	}

	return activeTime;
}

int Company::getTotalTruckUtilization(Time currentSimulationTime)
{
	nTruck* tempntruck;
	sTruck* tempstruck;
	vTruck* tempvtruck;

	Queue<nTruck*> tempnqueue;
	Queue<vTruck*> tempvqueue;
	Queue<sTruck*> tempsqueue;

	PQueue<nTruck*, Time> tempnpqueue;
	PQueue<vTruck*, Time> tempvpqueue;
	PQueue<sTruck*, Time> tempspqueue;

	float ut = 0;
	int numOfTrucks = this->getTotalNumofNormalTrucks() + this->getTotalNumofSpecialTrucks() + this->getTotalNumofVipTrucks();

	while (!normal_Truck.isEmpty())
	{
		normal_Truck.pop(tempntruck);
		tempnqueue.enqueue(tempntruck);
		ut = ut + tempntruck->getUtilization(currentSimulationTime);
	}
	while (!tempnqueue.isEmpty())
	{
		tempnqueue.dequeue(tempntruck);
		normal_Truck.push(tempntruck, tempntruck->GetPriority());
	}
	///////
	while (!normal_Truck_Night.isEmpty())
	{
		normal_Truck_Night.pop(tempntruck);
		tempnpqueue.push(tempntruck, tempntruck->GetPriority());
		ut = ut + tempntruck->getUtilization(currentSimulationTime);
	}
	while (!tempnpqueue.isEmpty())
	{
		tempnpqueue.pop(tempntruck);
		normal_Truck_Night.push(tempntruck, tempntruck->GetPriority());
	}
	///////
	while (!loading_Ntruck.isEmpty())
	{
		loading_Ntruck.pop(tempntruck);
		tempnpqueue.push(tempntruck, tempntruck->GetEndLoadingTime());
		ut = ut + tempntruck->getUtilization(currentSimulationTime);
	}
	while (!tempnpqueue.isEmpty())
	{
		tempnpqueue.pop(tempntruck);
		loading_Ntruck.push(tempntruck, tempntruck->GetEndLoadingTime());
	}
	/////
	while (!Maintenance_NTruck.isEmpty())
	{
		Maintenance_NTruck.dequeue(tempntruck);
		tempnqueue.enqueue(tempntruck);
		ut = ut + tempntruck->getUtilization(currentSimulationTime);
	}
	while (!tempnqueue.isEmpty())
	{
		tempnqueue.dequeue(tempntruck);
		Maintenance_NTruck.enqueue(tempntruck);
	}
	//////
	while (!moving_Ntruck.isEmpty())
	{
		moving_Ntruck.pop(tempntruck);
		tempnpqueue.push(tempntruck, tempntruck->GetEndLoadingTime());
		ut = ut + tempntruck->getUtilization(currentSimulationTime);
	}
	while (!tempnpqueue.isEmpty())
	{
		tempnpqueue.pop(tempntruck);
		moving_Ntruck.push(tempntruck, tempntruck->GetEndLoadingTime());
	}


	/////////////////////////


	while (!special_Truck.isEmpty())
	{
		special_Truck.pop(tempstruck);
		tempsqueue.enqueue(tempstruck);
		ut = ut + tempstruck->getUtilization(currentSimulationTime);
	}
	while (!tempsqueue.isEmpty())
	{
		tempsqueue.dequeue(tempstruck);
		special_Truck.pop(tempstruck);
	}

	///////
	while (!special_Truck_Night.isEmpty())
	{
		special_Truck_Night.pop(tempstruck);
		tempspqueue.push(tempstruck, tempstruck->GetPriority());
		ut = ut + tempstruck->getUtilization(currentSimulationTime);
	}
	while (!tempspqueue.isEmpty())
	{
		tempspqueue.pop(tempstruck);
		special_Truck_Night.push(tempstruck, tempstruck->GetPriority());
	}
	///////

	while (!loading_Struck.isEmpty())
	{
		loading_Struck.pop(tempstruck);
		tempspqueue.push(tempstruck, tempstruck->GetEndLoadingTime());
		ut = ut + tempstruck->getUtilization(currentSimulationTime);
	}
	while (!tempspqueue.isEmpty())
	{
		tempspqueue.pop(tempstruck);
		loading_Struck.push(tempstruck, tempstruck->GetEndLoadingTime());
	}
	/////
	while (!Maintenance_STruck.isEmpty())
	{
		Maintenance_STruck.dequeue(tempstruck);
		tempsqueue.enqueue(tempstruck);
		ut = ut + tempstruck->getUtilization(currentSimulationTime);
	}
	while (!tempsqueue.isEmpty())
	{
		tempsqueue.dequeue(tempstruck);
		Maintenance_STruck.enqueue(tempstruck);
	}
	//////
	while (!moving_Struck.isEmpty())
	{
		moving_Struck.pop(tempstruck);
		tempspqueue.push(tempstruck, tempstruck->GetEndLoadingTime());
		ut = ut + tempstruck->getUtilization(currentSimulationTime);
	}
	while (!tempspqueue.isEmpty())
	{
		tempspqueue.pop(tempstruck);
		moving_Struck.push(tempstruck, tempstruck->GetEndLoadingTime());
	}
	/////////////// 

	while (!vip_Truck.isEmpty())
	{
		vip_Truck.pop(tempvtruck);
		tempvqueue.enqueue(tempvtruck);
		ut = ut + tempvtruck->getUtilization(currentSimulationTime);
	}
	while (!tempvqueue.isEmpty())
	{
		tempvqueue.dequeue(tempvtruck);
		vip_Truck.push(tempvtruck, tempvtruck->GetPriority());
	}
	///////
	while (!vip_Truck_Night.isEmpty())
	{
		vip_Truck_Night.pop(tempvtruck);
		tempvpqueue.push(tempvtruck, tempvtruck->GetPriority());
		ut = ut + tempvtruck->getUtilization(currentSimulationTime);
	}
	while (!tempvpqueue.isEmpty())
	{
		tempvpqueue.pop(tempvtruck);
		vip_Truck_Night.push(tempvtruck, tempvtruck->GetPriority());
	}
	/////
	while (!loading_Vtruck.isEmpty())
	{
		loading_Vtruck.pop(tempvtruck);
		tempvpqueue.push(tempvtruck, tempvtruck->GetEndLoadingTime());
		ut = ut + tempvtruck->getUtilization(currentSimulationTime);
	}
	while (!tempvpqueue.isEmpty())
	{
		tempvpqueue.pop(tempvtruck);
		loading_Vtruck.push(tempvtruck, tempvtruck->GetEndLoadingTime());
	}
	/////
	while (!Maintenance_VTruck.isEmpty())
	{
		Maintenance_VTruck.dequeue(tempvtruck);
		tempvqueue.enqueue(tempvtruck);
		ut = ut + tempvtruck->getUtilization(currentSimulationTime);
	}
	while (!tempvqueue.isEmpty())
	{
		tempvqueue.dequeue(tempvtruck);
		Maintenance_VTruck.enqueue(tempvtruck);
	}
	//////
	while (!moving_Vtruck.isEmpty())
	{
		moving_Vtruck.pop(tempvtruck);
		tempvpqueue.push(tempvtruck, tempvtruck->GetEndLoadingTime());
		ut = ut + tempvtruck->getUtilization(currentSimulationTime);
	}
	while (!tempvpqueue.isEmpty())
	{
		tempvpqueue.pop(tempvtruck);
		moving_Vtruck.push(tempvtruck, tempvtruck->GetEndLoadingTime());
	}

	if (numOfTrucks != 0)
	{
		return (ut / numOfTrucks * 100.0);
	}
	else
	{
		return 0;
	}
	/////////////////////////


}

void Company::increaseNumOfNormalCargos ( )
{
	totalNumOfNormalCargos++;
}

void Company::increaseNumOfPromotedCargos ( )
{
	totalNumOfPromotedCargos++;
}

void Company::decreaseNumOfNormalCargos()
{
	totalNumOfNormalCargos--;
}