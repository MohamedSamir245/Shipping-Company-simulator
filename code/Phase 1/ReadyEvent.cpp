#include "ReadyEvent.h"
#include"NormalCargo.h"
#include"SpecialCargo.h"
#include"VipCargo.h"
#include<fstream>
#include <iostream>
#include<istream>
#include"Event.h"
#include"Time.h"
using namespace std;

istream& operator>>(istream& in, Time& t)
{
	int d, h;
	in >> d;
	in.ignore();
	in >> h;
	t.setDay(d);
	t.setHour(h);
	return in;
}

ReadyEvent::ReadyEvent(int autop,int Mw,char type, Time et, int id, float dist, Time lt, float cost):Event(et)
{
	AutoP = autop;
	TYP = type;
	ID = id;
	DIST = dist;
	LT = lt;
	Cost = cost;
	MaxW = Mw;
}

void ReadyEvent::Apply(Company*c)
{

	switch (TYP)
	{
		case'N':
		{
			NormalCargo *n=new NormalCargo(AutoP,MaxW,ID,-1,LT,this->gettime(), DIST, Cost);
			n->SetType(Normal);
			//add in company
			c->addCargo_normal(n);
			c->increaseNumOfNormalCargos ( );
			break;
		}
		case'V':
		{
			float Priority;
			Priority = (12/this->gettime().getDay()) + 25/(this->gettime().getHour()) + (50/DIST) + (6*Cost);
			VipCargo*v=new VipCargo(MaxW,ID, -1,Priority, LT, this->gettime(), DIST, Cost);
			v->SetType(Vip);
			//add in company
			c->addCargo_vip(v);

			break;
		}
		case'S':
		{
			SpecialCargo*s=new SpecialCargo(MaxW,ID, -1, LT, this->gettime(), DIST, Cost);
			s->SetType(Special);
			//add in company
			c->addCargo_special(s);
			break;
		}
	}
}
