#pragma once
#include"Time.h"
class Company;
class Event
{
	Time Event_Time;

public:

	Event(Time t);
	Time gettime();
	bool operator<(Event*);
	virtual void Apply(Company*) = 0;
};

