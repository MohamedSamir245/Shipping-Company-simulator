#pragma once
#include <iostream>
#include<string>
#include<fstream>
using namespace std;
class UIClass
{
	ofstream outfile;

public:

	UIClass();

	~UIClass();

	void printInteger(int x);
	void printString(string s);
	void printEndl();
	char EnterChar();
	void WaitEnterPress();

};