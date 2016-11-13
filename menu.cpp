
#include "menu.h"

Menu::Menu()
{
	selectedItem = -1;	//nothing return


	menuHeading ="Primo Victoria";
	menuItem1 = "Play Game";
	menuItem2 = "Level Select";
	menuItem3 = "Options";
}

Menu::Menu(std::string s)
{
	menuHeading = "Levels";
	menuItem1 = "Level 1";
	menuItem2 = "Level 2";
	menuItem3 = "Level 3";
}


void Menu::initialize(Graphics *g, Input *i)
{

	highlightColor = graphicsNS::RED;
	normalColor = graphicsNS::WHITE;
	menuAnchor = D3DXVECTOR2(270,10);
	input = i;
	verticalOffset = 30;
	linePtr = 0;
	selectedItem = -1;
	graphics = g;
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
	menuItemFontHighlight = new TextDX();
	if(menuItemFont->initialize(graphics, 15, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuItemFontHighlight->initialize(graphics, 18, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuHeadingFont->initialize(graphics, 25, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuHeading font"));
	menuHeadingFont->setFontColor(normalColor);
	menuItemFont->setFontColor(normalColor);
	menuItemFontHighlight->setFontColor(highlightColor);
	upDepressedLastFrame = false;
	downDepressedLastFrame = false;
	enterDepressedLastFrame = false;
}

void Menu::update()
{
	
	if (input->isKeyDown(VK_UP))
	{
		upDepressedLastFrame = true;
	}
	if (input->isKeyDown(VK_DOWN))
	{
		downDepressedLastFrame = true;
	}
	if (!input->isKeyDown(VK_UP) && upDepressedLastFrame){
		linePtr--;
		upDepressedLastFrame = false;
	}
	if (!input->isKeyDown(VK_DOWN) && downDepressedLastFrame){
		linePtr++;
		downDepressedLastFrame = false;
	}
	if (linePtr > 2) linePtr = 0;
	if (linePtr < 0) linePtr = 2;

	if(input->isKeyDown(VK_RETURN)){
		enterDepressedLastFrame = true;
	}
	if (!input->isKeyDown(VK_RETURN) && enterDepressedLastFrame){
		selectedItem = linePtr;
		enterDepressedLastFrame = false;
	}
	else selectedItem = -1;
}

void Menu::displayMenu()
{
	menuHeadingFont->print(menuHeading, menuAnchor.x, menuAnchor.y);
	if (linePtr==0)
		menuItemFontHighlight->print(menuItem1, menuAnchor.x, menuAnchor.y+verticalOffset);
	else
		menuItemFont->print(menuItem1, menuAnchor.x, menuAnchor.y+verticalOffset);
	int foo = 2*verticalOffset;
	if (linePtr==1)
		menuItemFontHighlight->print(menuItem2, menuAnchor.x, menuAnchor.y+foo);
	else
		menuItemFont->print(menuItem2, menuAnchor.x, menuAnchor.y+foo);
	foo = 3*verticalOffset;
	if (linePtr==2)
		menuItemFontHighlight->print(menuItem3, menuAnchor.x, menuAnchor.y+foo);
	else
		menuItemFont->print(menuItem3, menuAnchor.x, menuAnchor.y+foo);
}