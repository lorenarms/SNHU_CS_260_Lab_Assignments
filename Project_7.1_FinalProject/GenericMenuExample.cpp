/*
This a modular, designed to be dropped into any program I write that needs an interactive menu

This displays a menu in the center of the console, allows users to use arrow keys and
enter to select the desired item, and can be customized for any menu size, position, and color
scheme

*/


#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>

#include "MenuDriver.h"
#include "AppMenus.h"

using namespace std;

int MainMenu(MenuDriver mainMenu, MenuDriver newCursor) {
	int selection = 0;
	bool run = true;
	vector <string> menu = { "Selection 1", "Short", "This is long Selection 3" , "this", "new selection", "Quit", "Continue" };
	int m = mainMenu.MenuModifier(menu);
	int w = newCursor.GetWindowWidth();		//also called 'columnToDraw'

	w /= 2;
	w -= (m / 2);

	newCursor.HideCursorBlink();

	while (run) {
		mainMenu.RunMenu(menu, selection, w);
		switch (selection) {
		case 1:
			system("cls");
			cout << "Selection 1..." << endl;
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			system("cls");
			run = false;
			break;
		case 7:
			newCursor.SetNewCursor(10, 0);
			cout << "Continuing..." << endl;
			break;
		default:
			break;
		}
	}


	return selection;
}

int New() {

	//declare your objects
	MenuDriver newMenu;
	MenuDriver newCursor;
	AppMenus mainMenu;

	
	//mainMenu.Menu(newMenu, newCursor);



	return 0;
}

