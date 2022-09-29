#pragma once
#include "Event.h"
#include"Time.h"

class CancellationEvent : public Event
{
	int ID;

public:

	CancellationEvent (  Time et, int id );
	virtual void Apply ( Company* MyCompany);


};

