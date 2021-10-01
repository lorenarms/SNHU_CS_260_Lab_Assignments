#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>

#include "MenuDriver.h"


using namespace std;

void MenuDriver::SetRow(int row) {
	this->row = row;
}

//
// Checks for key presses to draw the menu properly, returns the key that's pressed
//
int MenuDriver::CheckKeyPress() {
	if ((GetAsyncKeyState(0x51) & 0x01)) {			// 'q' key for 'quit'
		
		return 1;
	}
	else if ((GetAsyncKeyState(0x0D) & 0x01)) {		// enter
		
		return 2;
	}
	else if ((GetAsyncKeyState(0x28) & 0x01)) {		//down arrow
		
		return 3;
	}
	else if ((GetAsyncKeyState(0x26) & 0x01)) {		//up arrow
		
		return 4;
	}
	else {									// nada, keep going
		return 0;
	}
}

//https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

//
// Changes the colors of the items that are / are not selected as user navigates menu
//
void MenuDriver::DrawMenu(vector<string> menu, int selection, int columnToDraw) {
	//use these to change the menu colors
	int selected = 240;
	int unselected = 15;
	for (int i = 0; i < menu.size(); i++) {
		SetNewCursor(i + row, columnToDraw);
		SetColor(unselected);
		if (i == selection - 1) {
			SetColor(selected);
		}
		cout << menu.at(i) << endl;
		//resets the color
		SetColor(unselected);
	}
}

//
// Menu logic; checks the selection var when enter is pressed, quits menu when 'q' is pressed
//
void MenuDriver::RunMenu(vector<string> menu, int& selection, int columnToDraw) {
	bool i = true;
	int j = 0;
	DrawMenu(menu, selection, columnToDraw);
	while (i) {
		j = CheckKeyPress();
		if (j == 3) {				//down
			selection++;
			if (selection > menu.size()) {
				selection = 1;
			}
		}
		else if (j == 4) {		//up
			selection--;
			if (selection < 1) {
				selection = menu.size();
			}

		}
		else if (j == 1) {		//quit
			i = false;

		}
		else if (j == 2) {		//enter
			
			return;
		}
		DrawMenu(menu, selection, columnToDraw);
	}
}

//
// Sets the cursor position
//
void MenuDriver::SetNewCursor(int row, int col) {

	//sets cursor position before printing clock
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout.flush();
	COORD coord = { (SHORT)col, (SHORT)row };
	SetConsoleCursorPosition(hOut, coord);
}

//
// Hides the cursor
//
void MenuDriver::HideCursorBlink() {
	//hide the blinking cursor
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

//
// Shows cursor again; use this when user must enter input
//
void MenuDriver::ShowCursorBlink() {
	//show the blinking cursor
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = TRUE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

//
// Permanetly modifies the menu vector for size and justification (center is default)
//
int MenuDriver::MenuModifier(vector<string>& menu) {
	int maximum = 0;
	int min = 0;
	int spaces = 0;
	string temp = "";
	string space = "";
	for (int i = 0; i < menu.size(); i++) {
		if (menu.at(i).length() > maximum) {
			maximum = menu.at(i).length();
		}
	}
	maximum += 10;				// modify this value to change how wide the menu will be
							// value is amount of spaces added to each side of longest item
	for (int i = 0; i < menu.size(); i++) {
		if (menu.at(i).length() % 2 != 0) {			// if the menu item is not an even number of characters, add one space at the end
													// to make it divisible by 2
			menu.at(i) += " ";
		}
		min = maximum - menu.at(i).length();
		min /= 2;
		for (int j = 0; j < min; j++) {
			space += " ";
		}
		menu.at(i) = space + menu.at(i) + space;
		space = "";

	}
	for (int i = 0; i < menu.size(); i++) {
		if (menu.at(i).length() < maximum) {
			menu.at(i) + " ";
		}
	}

	return maximum;
}

//
// Sets the size of the window that the console app runs in
// pass width, height
//
void MenuDriver::SetWindowSize(int w, int h) {
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);

	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, w, h, TRUE);
}

//
// returns the width of the window, so displayed items can be centered if necessary
//
int MenuDriver::GetWindowWidth() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	return columns;
}

//
// changes the color of whatever is called
//
void MenuDriver::SetColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

