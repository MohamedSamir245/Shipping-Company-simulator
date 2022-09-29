#include "PromotionEvent.h"

PromotionEvent::PromotionEvent(Time t, int id, int Emoney) :Event(t)
{
	ED = t; 
	ID = id; 
	ExtraMoney = Emoney;
}

void PromotionEvent::Apply(Company* C) 
{
	NormalCargo* pCargo=nullptr;
	pCargo = C->haveCargo_normal(ID);
	if (pCargo)
	{
		C->promoteCargo_normalTovip(pCargo);
	}
}
