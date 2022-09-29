#include<iostream>
#include<Windows.h>
#include"Company.h"

using namespace std;



int main()
{

	system("color a");
	static CONSOLE_FONT_INFOEX  fontex;
	fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(hOut, 0, &fontex);
	fontex.FontWeight = 600;
	fontex.dwFontSize.X = 24;
	fontex.dwFontSize.Y = 24;
	SetCurrentConsoleFontEx(hOut, NULL, &fontex);


Company c;

cout << "For Active Mode:       enter 1" << endl << "For Step-By-Step Mode: enter 2" << endl << "For Silent Mode:       enter 3" << endl;
int x;
cin >> x;
c.simulate(x);	
return 0;
}