#include "CancellationEvent.h"
#include"Company.h"

CancellationEvent::CancellationEvent ( Time et, int id ) : Event(et )
{
	ID = id;
}

void CancellationEvent::Apply ( Company* MyCompany)
{
	NormalCargo* pCargo = nullptr;
	pCargo = MyCompany->haveCargo_normal(ID);
	if (pCargo)
	{
		MyCompany->decreaseNumOfNormalCargos();
		delete pCargo;
	}
}
