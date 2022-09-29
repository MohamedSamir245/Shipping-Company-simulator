#pragma once
#include "Event.h"
#include "Time.h"
#include "Company.h"
class PromotionEvent :
    public Event
{
    Time ED;
    int ID;
    int ExtraMoney;

public:

    PromotionEvent(Time t, int id, int Emoney);
    virtual void Apply(Company*);
};

