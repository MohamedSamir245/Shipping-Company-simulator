#pragma once
#include"Event.h"
#include"Cargo.h"
#include"NormalCargo.h"
#include"SpecialCargo.h"
#include"VipCargo.h"
#include"Truck.h"
#include"nTruck.h"
#include"sTruck.h"
#include"vTruck.h"
#include"Queue.h"
#include"PQueue.h"
#include <fstream>
#include"ReadyEvent.h"
#include "PromotionEvent.h"
#include"CancellationEvent.h"
#include "UIClass.h"

#include <chrono>
#include <thread>

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

class Company
{

	int totalNumOfNormalCargos;
	int totalNumOfPromotedCargos;
	int NoOfTrucks;

	/*__________Trucks___________*/
	//Waiting Trucks:Night Shift 
	PQueue<nTruck*, float> normal_Truck_Night;
	PQueue<sTruck*, float> special_Truck_Night;
	PQueue<vTruck*, float> vip_Truck_Night;
	//waiting truck
	PQueue<nTruck*, float> normal_Truck;
	PQueue<vTruck*, float> vip_Truck;
	PQueue<sTruck*, float> special_Truck;
	//loading trucks
	PQueue<nTruck*, Time> loading_Ntruck;
	PQueue<vTruck*, Time> loading_Vtruck;
	PQueue<sTruck*, Time> loading_Struck;
	//moving trucks
	PQueue<nTruck*, Time> moving_Ntruck;
	PQueue<vTruck*, Time> moving_Vtruck;
	PQueue<sTruck*, Time> moving_Struck;
	//in-checkup truck
	Queue<nTruck*> Maintenance_NTruck;
	Queue<vTruck*> Maintenance_VTruck;
	Queue<sTruck*> Maintenance_STruck;

	/*__________Cargos___________*/
	//waiting cargos
	Queue<NormalCargo*> normal_Cargo;
	Queue<SpecialCargo*> special_Cargo;
	PQueue<VipCargo*, int> vip_Cargo;
	//deliverd Cargos
	Queue<NormalCargo*> delivered_NCargo;
	Queue<SpecialCargo*> delivered_SCargo;
	Queue<VipCargo*> delivered_VCargo;

	/*________________________*/
	//events
	Queue<Event*> Events;
	//company time
	int openenig_time;
	int closing_time;
	UIClass* pOut; //output pointer
	UIClass* pIn; //input pointer
	//current time
	Time Current_Time;


	/*___________Private_Functions_____________*/

	/*____________Cargos______________*/
	//deliviring
	bool moveCargo_Todeliver(Truck*);

	/*____________Trucks______________*/
	//add trucks
	bool addTruck_normal(nTruck* newTruck);
	bool addTruck_special(sTruck* newTruck);
	bool addTruck_vip(vTruck* newTruck);
	//loading:Day
	bool moveNTruck_Toload();
	bool moveSTruck_Toload();
	bool moveVTruck_Toload();
	//loading:Night
	bool moveNTruck_Toload_Night();
	bool moveSTruck_Toload_Night();
	bool moveVTruck_Toload_Night();
	//movining
	bool moveNTruck_Tomove();
	bool moveSTruck_Tomove();
	bool moveVTruck_Tomove();
	//deliviring:Day
	bool moveNTruck_Towaiting();
	bool moveSTruck_Towaiting();
	bool moveVTruck_Towaiting();
	//deliviring:Night
	bool moveNTruck_Towaiting_Night();
	bool moveSTruck_Towaiting_Night();
	bool moveVTruck_Towaiting_Night();
	//Maintenance
	bool moveNTruck_ToMaintenance(Time);
	bool moveSTruck_ToMaintenance(Time);
	bool moveVTruck_ToMaintenance(Time);
	//End_Maintenance:Day
	bool moveNTruck_FMTowaiting();
	bool moveSTruck_FMTowaiting();
	bool moveVTruck_FMTowaiting();
	//End_Maintenance:Night
	bool moveNTruck_FMTowaiting_Night();
	bool moveSTruck_FMTowaiting_Night();
	bool moveVTruck_FMTowaiting_Night();

	/*____________Functions______________*/
	//load data
	void loadData();
	//Delivry failure
	void randfail();
	void returnfailedtrucks();
	//Assignment Cargos:Day Shift Trucks
	void Assign_Cargos(Time simTime);
	//Assignment Cargos:Night Shift Trucks
	void Assign_Cargos_Night(Time simTime);
	//Program Interface
	void InterActiveMode(Time);
	void printWaitingCargos();
	void printLoadingTrucks();
	void printEmptyTrucks();
	void printMovingCargos();
	void printInCheckupTrucks();
	void printDeliverdCargos();
	void printtime(Time);
	void printbreak();
	//output file
	void generateOutputFile(Time t);
	//statistics
	int getTotalNumofNormalCargos();
	int getTotalNumofSpecialCargos();
	int getTotalNumofVipCargos();

	int getTotalNumofPromotedCargos();

	int getTotalNumofNormalTrucks();
	int getTotalNumofSpecialTrucks();
	int getTotalNumofVipTrucks();

	Time getTotalAvgTimeOfNormalTrucks();
	Time getTotalAvgTimeOfSpecialTrucks();
	Time getTotalAvgTimeOfVipTrucks();

	int getTotalTruckUtilization(Time currentSimulationTime);

	void increaseNumOfPromotedCargos();

public:
	
	//Constructor
	Company();

	//simulation
	void simulate(int);

	/*____________Events______________*/
	//add events
	bool addEvent(Event* newEvent);

	/*____________Cargos______________*/
	//search normal cargo exist
	NormalCargo* haveCargo_normal(int id);
	//promotion
	bool promoteCargo_normalTovip(NormalCargo* pr_Cargo);
	//add cargos
	bool addCargo_normal(NormalCargo* newCargo);
	bool addCargo_special(SpecialCargo* newCargo);
	bool addCargo_vip(VipCargo* newCargo);

	void increaseNumOfNormalCargos();
	void decreaseNumOfNormalCargos();

};