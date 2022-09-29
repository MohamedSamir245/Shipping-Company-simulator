#pragma once
#include "Event.h"
#include"Time.h"
#include<fstream>
#include"Company.h"

class ReadyEvent : public Event
{
	int AutoP;
	int MaxW;
	char TYP;
	int ID;
	float DIST;
	Time LT;
	float Cost;
	
public:

	ReadyEvent(int,int,char,Time,int,float,Time,float);
	virtual void Apply(Company*c);

};

