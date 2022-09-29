#include "UIClass.h"



UIClass::UIClass()
{
	ofstream outfile("Data.txt");

}


UIClass::~UIClass()
{
}

void UIClass::printInteger(int x)
{
	cout << x;

}

void UIClass::printString(string s)
{
	cout << s;
}

void UIClass::printEndl()
{
	cout << endl;
}



char UIClass::EnterChar()
{
	char x;;
	cin >> x;
	return x;
}

void UIClass::WaitEnterPress()
{
	cin.ignore();
}