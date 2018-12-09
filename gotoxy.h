#ifndef GOTOXY_H_INCLUDED
#define GOTOXY_H_INCLUDED
#include <iostream>
#include <windows.h>
#include <ctime>
#include <vector>

using namespace std;

void gotoxy( int x, int y ){
  COORD coord;
  coord.X = x;
  coord.Y = y;

  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
	);
	ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
}

#endif GOTOXY_H_INCLUDED
