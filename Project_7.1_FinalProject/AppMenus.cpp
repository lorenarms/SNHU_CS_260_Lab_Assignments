#include <iostream>
#include <string>
#include <vector>

#include "MenuDriver.h"
#include "AppMenus.h"

using namespace std;

//
// This is a sample of a 'main menu' to be used at the start of a program
//

int AppMenus::Menu(MenuDriver newMenu, MenuDriver newCursor) {
	
		
	int selection = 0;		// this is the var for the switch below; this var is returned when a user presses a 'selection' key (see 'menuDriver/checkKeyPress)
	bool run = true;		// for the 'while' loop below

	// this is the vector of strings for the menu
	vector <string> menu = { "Selection 1", "Short", "This is long Selection 3" , "this", "new selection", "Quit", "Continue" };
	
	// modifiy the above vector, and return the max width of the menu
	int m = newMenu.MenuModifier(menu);

	// get the width of the window that the console is running in
	int w = newCursor.GetWindowWidth();		

	// get the center and set the window column at which the menu starts to draw
	w /= 2;
	w -= (m / 2);

	// turn off the cursor
	newCursor.HideCursorBlink();

	while (run) {

		// draw the menu and listen for key presses
		// sends 'selection' as a reference so 'MenuDriver' class can modify and return
		// (makes the selection process faster)
		newMenu.RunMenu(menu, selection, w);
		
		// can add more menus here for each selection
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