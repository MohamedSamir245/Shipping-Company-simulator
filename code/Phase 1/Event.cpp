#include "Event.h"
#include "Company.h"


Event::Event(Time t)
{
	Event_Time = t;
}

Time Event::gettime()
{
	return Event_Time;
}

bool Event::operator<(Event* e)
{
	if (this->Event_Time < e->Event_Time)
		return true;
	return false;
}