#include "Time.h"

Time::Time(int d, int h)
{
	setHour(h);
	Day = d;
}

void Time::setHour(int h)
{
	if (h < 24 && h >= 0)
		Hour = h;
}

void Time::setDay(int d)
{
	if (d >= 0)
		Day = d;
}

void Time::setTime(int d, int h)
{
	setHour(h);
	setDay(d);
}

int Time::getHour()
{
	return Hour;
}

int Time::getDay()
{
	return Day;
}

Time Time::operator+(Time t2)
{
	int h = Hour + t2.Hour;
	int d = Day + t2.Day;
	if (h > 23)
	{
		d=d+1;
		h = h - 24;
	}
	return Time(d,h);
}

Time Time::operator+(int h2)
{
	int h = Hour + h2;
	int d = Day;
	while (h > 23)
	{
		d = d + 1;
		h = h - 24;
	}
	return Time(d,h);
}

bool Time::operator>(Time t2)
{
	if (Day > t2.Day)
		return true;
	else if (Day == t2.Day && Hour > t2.Hour)
		return true;
	else
		return false;
}

bool Time::operator<(Time t2)
{
	if (Day < t2.Day)
		return true;
	else if (Day == t2.Day && Hour < t2.Hour)
		return true;
	else
		return false;
}

bool Time::operator==(Time t2)
{
	if (Day == t2.Day && Hour == t2.Hour)
		return true;
	else
		return false;
}

bool Time::operator<=(Time t2)
{
	if (*this < t2 || *this == t2)
		return true;
	return false;
}

bool Time::operator>=(Time t2)
{
	if (*this > t2 || *this == t2)
		return true;
	return false;
}

bool Time::operator>=(int hours)
{
	int curr = Day * 24 + Hour;
	if (curr>=hours)
		return true;
	return false;
}

Time Time::operator/(int t)
{
	Time temp ( 0, 0 );
	if ( t != 0 )
	{
		int x = this->getDay ( ) * 24 + this->getHour ( );
		x = x / t;

		temp.setHour ( x % 24 );
		temp.setDay ( x / 24 );

		return temp;
	}
	return temp;

}

Time Time::operator-( Time t2 )
{
	int h = Hour - t2.Hour;
	int d = Day - t2.Day;
	if ( h < 0 )
	{
		d = d - 1;
		h = h + 24;
	}

	return Time ( d, h );
}

Time::~Time()
{
}
