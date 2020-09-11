#include <iostream> //v 0.9
#include <string>
#include<cwchar>
#include <Windows.h>
#include <conio.h>
#include <chrono>
#include <thread>
using namespace std;

// COLORS
#define FOREGROUND_WHITE		(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)
#define BACKGROUND_WHITE		(BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN)

#define FOREGROUND_CYAN		        (FOREGROUND_BLUE | FOREGROUND_GREEN)
#define BACKGROUND_CYAN		        (BACKGROUND_BLUE | BACKGROUND_GREEN)

#define FOREGROUND_MAGENTA	        (FOREGROUND_RED | FOREGROUND_BLUE)
#define BACKGROUND_MAGENTA	        (BACKGROUND_RED | BACKGROUND_BLUE)

#define BACKGROUND_INTENSE_MAGENTA	(BACKGROUND_MAGENTA | BACKGROUND_INTENSITY)
#define FOREGROUND_INTENSE_MAGENTA	(FOREGROUND_MAGENTA | FOREGROUND_INTENSITY)

#define BACKGROUND_YELLOW	        (BACKGROUND_RED | BACKGROUND_GREEN)
#define FOREGROUND_YELLOW       	(FOREGROUND_RED | FOREGROUND_GREEN)
#define BACKGROUND_INTENSE_YELLOW   (BACKGROUND_YELLOW | BACKGROUND_INTENSITY)
//

int DR();
int UP();
int DOWN();
int LEFT();
int RIGHT();
int TeIDUP(); //TempID update
int DRI();

int counter, test, code, x, y, cyclecount;
char ch;
int InD, DirtA, StoneA, TempID, BlockSelector;

bool TestOn;
const unsigned int DIM1 = 10;
const unsigned int DIM2 = 20;
int World[DIM1][DIM2] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,6,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,4,4,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
};
int Intro[DIM1][DIM2] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,},
	{0,0,0,0,1,1,1,0,1,0,1,0,0,1,1,1,0,0,0,0,},
	{0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,},
	{0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,1,0,0,0,0,},
	{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,},
	{0,0,0,0,0,0,1,0,1,0,0,1,0,1,1,1,0,0,0,0,},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
};
int main()
{
	// DISPLAY SETTINGS
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD crd = { 20, 10 }; // Window parameters
	SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
	SetConsoleWindowInfo(out_handle, true, &src);
	SetConsoleScreenBufferSize(out_handle, crd);
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 60;                   // Width of each character in the font
	cfi.dwFontSize.Y = 60;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Courier");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	x = 6;
	y = 5;
	World[y][x] = 1;
	InD = 1;
	DirtA = 0;
	StoneA = 0;
	TestOn = false;
	for (int i = 6; i < 7; i++) {
		for (int j = 0; j < DIM2; j++) {
			World[i][j] = 4;
		}
	}
	for (int i = 7; i < DIM1; i++) {
		for (int j = 0; j < DIM2; j++) {
			World[i][j] = 3;
		}
	}
		DRI();
		using namespace this_thread;
		using namespace chrono;
		sleep_for(seconds(3));
	DR();
	do {
		
		code = 0;
		if (_kbhit()) { ch = _getch(); code = static_cast<int>(ch); }

		// Player controls
		/* W */	if (GetAsyncKeyState(119) == false and code == 119 and y > 1 and (World[y - 1][x] == 0 or World[y - 1][x] == 2) and (World[y + 1][x] != 0)) {
			TeIDUP();
			World[y][x] = 0;
			y--;
			World[y][x] = 1;

			TempID = 0;
			DR();
		}

		/* A */	if (GetAsyncKeyState(97) == false and code == 97 and x > 0 and ((World[y][x - 1] == 0) or (World[y][x - 1] == 2))) {
			TeIDUP();
			World[y][x] = 0;
			x--;
			World[y][x] = 1;

			TempID = 0;
			DR();
		}


		/* D */	if (GetAsyncKeyState(100) == false and code == 100 and x < 19 and ((World[y][x + 1] == 0) or (World[y][x + 1] == 2))) {

			TeIDUP();
			World[y][x] = 0;
			x++;
			World[y][x] = 1;

			TempID = 0;
			DR();
		}

		/* Q */	if (GetAsyncKeyState(113) == false && code == 113) {
			if (TempID == 3 and StoneA < 9) {
				StoneA++; if (World[y - 1][x] == 2) World[y - 1][x] = 0;
				if (World[y][x + 1] == 2) World[y][x + 1] = 0;
				if (World[y][x - 1] == 2) World[y][x - 1] = 0;
				if (World[y + 1][x] == 2) World[y + 1][x] = 0;
				TempID = 0;
			}
			if (TempID == 4 and DirtA < 9) {
				DirtA++; if (World[y - 1][x] == 2) World[y - 1][x] = 0;
				if (World[y][x + 1] == 2) World[y][x + 1] = 0;
				if (World[y][x - 1] == 2) World[y][x - 1] = 0;
				if (World[y + 1][x] == 2) World[y + 1][x] = 0;
				TempID = 0;
			}

			DR();
		} // BREAK

		/* E */	if (GetAsyncKeyState(101) == false && code == 101) {
			if (TempID == 0 and BlockSelector == 1 and StoneA > 0) {
				if (World[y - 1][x] == 2) World[y - 1][x] = 3;
				if (World[y][x + 1] == 2) World[y][x + 1] = 3;
				if (World[y][x - 1] == 2) World[y][x - 1] = 3;
				if (World[y + 1][x] == 2) World[y + 1][x] = 3;
				StoneA--;
				DR();
			}
			if (TempID == 0 and BlockSelector == 0 and DirtA > 0) {
				if (World[y - 1][x] == 2) World[y - 1][x] = 4;
				if (World[y][x + 1] == 2) World[y][x + 1] = 4;
				if (World[y][x - 1] == 2) World[y][x - 1] = 4;
				if (World[y + 1][x] == 2) World[y + 1][x] = 4;
				DirtA--;
				DR();
			}
		} // PUT 

		/* F */	if (GetAsyncKeyState(102) == false && code == 102) { if (BlockSelector == 0) { BlockSelector = 1; } else if (BlockSelector == 1) { BlockSelector = 0; } DR(); }

		/* UP */	if (GetAsyncKeyState(72) == false && code == 72) { UP(); }
		/* RIGHT */	if (GetAsyncKeyState(77) == false && code == 77) { RIGHT(); }
		/* DOWN */	if (GetAsyncKeyState(80) == false && code == 80) { DOWN(); }
		/* LEFT */	if (GetAsyncKeyState(75) == false && code == 75) { LEFT(); }
		using namespace this_thread;
		using namespace chrono;
		cyclecount += 1;

		/*Gravity*/	if (((World[y + 1][x] == 0 or World[y + 1][x] == 2) and ((InD == 3 and TempID == 0) or (InD != 3))) and (cyclecount == 2)) {
			TeIDUP();

			TempID = 0;
			World[y][x] = 0; y++;  World[y][x] = 1; cyclecount = 0; DR();
		}
		if (cyclecount == 5) { cyclecount = 0; }
		sleep_for(milliseconds(100));

	} while (1);
}
int DR() {
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//system("cls");
	for (int i = 0; i < DIM1; i++) {
		for (int j = 0; j < DIM2; j++) {
			counter++;

			if (World[i][j] == 0) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_CYAN | BACKGROUND_CYAN); cout << "0"; }
			if (World[i][j] == 1 and TestOn == false) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_RED | BACKGROUND_RED); cout << "0"; }
			if (World[i][j] == 1 and TestOn == true) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_WHITE | BACKGROUND_RED); cout << TempID; }
			if (World[i][j] == 2 and TempID == 3) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_INTENSE_MAGENTA | BACKGROUND_WHITE); cout << "+"; }
			if (World[i][j] == 2 and TempID == 4) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_INTENSE_MAGENTA | BACKGROUND_GREEN); cout << "+"; }
			if (World[i][j] == 2 and TempID == 0) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_INTENSE_MAGENTA | BACKGROUND_CYAN); cout << "+"; }
			if (World[i][j] == 3) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_WHITE | BACKGROUND_WHITE); cout << "0"; }
			if (World[i][j] == 4) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN | BACKGROUND_GREEN); cout << "0"; }

			if (World[i][j] == 5 and BlockSelector == 0) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_RED | BACKGROUND_GREEN); cout << DirtA; }
			if (World[i][j] == 5 and BlockSelector == 1) { SetConsoleTextAttribute(hConsoleHandle, 0 | BACKGROUND_GREEN); cout << DirtA; }

			if (World[i][j] == 6 and BlockSelector == 1) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_RED | BACKGROUND_WHITE); cout << StoneA; }
			if (World[i][j] == 5 and BlockSelector == 0) { SetConsoleTextAttribute(hConsoleHandle, 0 | BACKGROUND_WHITE); cout << StoneA; }

			if (counter == 20) { cout << endl; counter = 0; }
		}
	}
	return 0;
}
int DRI() {
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < DIM1; i++) {
		for (int j = 0; j < DIM2; j++) {
			if (Intro[i][j] == 0) { SetConsoleTextAttribute(hConsoleHandle, 0 | 0); cout << "0"; }
			if (Intro[i][j] == 1 ) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_WHITE | BACKGROUND_WHITE); cout << "0"; }
			if (Intro[i][j] == 2) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_MAGENTA | BACKGROUND_WHITE); cout << "C"; }
			if (Intro[i][j] == 3) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_MAGENTA | BACKGROUND_WHITE); cout << "u"; }
			if (Intro[i][j] == 4) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_MAGENTA | BACKGROUND_WHITE); cout << "b"; }
			if (Intro[i][j] == 5) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_MAGENTA | BACKGROUND_WHITE); cout << "a"; }
			if (Intro[i][j] == 6) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_MAGENTA | BACKGROUND_WHITE); cout << "n"; }
			if (Intro[i][j] == 7) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_MAGENTA | BACKGROUND_WHITE); cout << "o"; }
			if (Intro[i][j] == 8) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_MAGENTA | BACKGROUND_WHITE); cout << "i"; }
			if (Intro[i][j] == 9) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_MAGENTA | BACKGROUND_WHITE); cout << "d"; }
			if (Intro[i][j] == 10) { SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_MAGENTA | BACKGROUND_WHITE); cout << "s"; }
		}
	}

	return 0;
}

int UP() {
	InD = 1;
	TeIDUP();

	TempID = World[y - 1][x]; World[y - 1][x] = 2;
	DR();
	return 0;
}

int DOWN() {
	InD = 3;
	TeIDUP();

	TempID = World[y + 1][x]; World[y + 1][x] = 2;
	DR();
	return 0;
}
int LEFT() {
	InD = 4;
	TeIDUP();

	TempID = World[y][x - 1]; World[y][x - 1] = 2;
	DR();
	return 0;
}
int RIGHT() {
	InD = 2;
	TeIDUP();

	TempID = World[y][x + 1]; World[y][x + 1] = 2;
	DR();
	return 0;
}
int TeIDUP() { //TempID update
	if (World[y - 1][x] == 2) World[y - 1][x] = TempID;
	if (World[y][x + 1] == 2) World[y][x + 1] = TempID;
	if (World[y][x - 1] == 2) World[y][x - 1] = TempID;
	if (World[y + 1][x] == 2) World[y + 1][x] = TempID;
	return 0;
}
/* S */	/*if ((GetAsyncKeyState(115) == false and code == 115) and (y < 9) and ((World[y + 1][x] == 0) or (World[y + 1][x] == 2))) {

	if (World[y - 1][x] == 2) World[y - 1][x] = TempID;
	if (World[y][x + 1] == 2) World[y][x + 1] = TempID;
	if (World[y][x - 1] == 2) World[y][x - 1] = TempID;
	if (World[y + 1][x] == 2) World[y + 1][x] = TempID;
	World[y][x] = 0;
	y++;
	World[y][x] = 1;

	TempID = 0;
	DR();

			cout << endl << endl << endl << endl << "     ";
		SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_MAGENTA | BACKGROUND_WHITE);
		cout << "Cubanoids"; SetConsoleTextAttribute(hConsoleHandle, 0 | 0);
		//cout << endl << endl << endl << "   Now with even" << endl <<  "   more flashing!";
		cout << endl << endl << endl << endl << endl << "                ";	SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_MAGENTA | 0);	cout << "v0.8";

			/*for (int i = 0; i < DIM1; i++) {
		for (int j = 0; j < DIM2; j++) {
			Intro[i][j] = 9;
		}
	*/
