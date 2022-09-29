#pragma once
class Time
{
	int Hour;
	int Day;

public:

	Time(int d = 1, int h = 0);
	void setHour(int h);
	void setDay(int d);
	void setTime(int d, int h);
	int getHour();
	int getDay();
	//operators
	Time operator +(Time t2);
	Time operator +(int h2);
	bool operator >(Time t2);
	bool operator <(Time t2);
	bool operator ==(Time t2);
	bool operator <=(Time t2);
	bool operator >=(Time t2);
	bool operator >=(int hours);
	Time operator /(int);
	Time operator -( Time t2 );

	~Time();
};

