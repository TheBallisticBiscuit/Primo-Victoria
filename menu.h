
// file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#ifndef MENU_H                 // Prevent multiple definitions if this 
#define MENU_H 

class Menu;

#include <string>
#include "graphics.h"
#include "constants.h"
#include "textDX.h"
#include <string>
#include <sstream>
#include "input.h"

namespace menuNS
{ }

// inherits from Entity class3
class Menu
{
private:

	TextDX *menuItemFont;
	TextDX *menuItemFontHighlight;
	TextDX *menuHeadingFont;

	Input   *input;         // pointer to the input system
	Graphics *graphics;

	int selectedItem;
	std::string menuHeading;
	std::string menuItem1;
	std::string menuItem2;
	std::string menuItem3;
	D3DXVECTOR2 menuAnchor;
	int verticalOffset;
	int linePtr;
	COLOR_ARGB highlightColor ;
	COLOR_ARGB normalColor;
	bool upDepressedLastFrame;
	bool downDepressedLastFrame;
	bool enterDepressedLastFrame;

public:
	// constructor
	Menu();
	Menu(std::string);
	
	void initialize(Graphics *g, Input *i);
	void update();
	int getSelectedItem() {return selectedItem;}
	void displayMenu();
	void setMenuHeading(std::string newHeading){menuHeading = newHeading;}
	void setMenuItem1(std::string newItem){menuItem1 = newItem;}
	void setMenuItem2(std::string newItem){menuItem2 = newItem;}
	void setMenuItem3(std::string newItem){menuItem3 = newItem;}

};
#endif

