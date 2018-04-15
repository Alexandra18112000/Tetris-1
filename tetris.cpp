#include <iostream>
#include <conio.h>
#include <string>
#include <ctype.h>
#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <time.h>

const int NB_BLOCKS = 7;
const int BAR_BLOCK = 1;
const int T_BLOCK   = 2;
const int L_BLOCK   = 3;
const int LR_BLOCK  = 4;
const int BOX_BLOCK = 5;
const int Z_BLOCK = 6;
const int ZR_BLOCK = 7;
const int HORIZONTAL = 1;
const int VERTICAL = 2;
const int RIGHT = 1;
const int LEFT = 2;
const int DOWN  = 3;
const int UP = 4;

const int BOARD_COLOR   = BLACK;
const int BKGRD_COLOR   = BOARD_COLOR;
const int FILLING_COLOR = GREEN; //LIGHTGRAY;
const int FRGRD_COLOR   = 1; //CYAN; //BLUE; //GREEN; //RED; // LIGHTGRAY;
// const int FRGRD_COLOR   = BOARD_COLOR; //FILLING_COLOR;
const int GRID_COLOR    = YELLOW;
const int BORDER_COLOR  = GRID_COLOR;

const int LEVEL1_SPEED = 800;
const int LEVEL2_SPEED = 600;
const int LEVEL3_SPEED = 400;
const int LEVEL4_SPEED = 200;

const int BOARDWIDTH 	= 180;
const int BOARDHEIGHT	= 240;
const int NB_ROWS  	= 15;
const int NB_COLS  	= 10;
const int CELL_SIZE	= BOARDHEIGHT/(NB_ROWS+1); //15
const int LEFTCORNER	= (600 - (CELL_SIZE*(NB_COLS+2)))/2; //230;
const int TOPCORNER	= 120;
const int INFOAREAWIDTH	= 600;
const int INFOAREAHEIGHT= 105;
const int INFOAREALEFT	= 20;
const int INFOAREATOP	= 370;

const int LEFTARROW=75;
const int RIGHTARROW=77;
const int UPARROW=72;
const int DOWNARROW=80;
const int ENTER=13;
const int ESC=27;
const int SPACE=32;

using namespace std;

//initializes graphics driver
void initGraphEngine(){
  int gdriver = DETECT, gmode;
  initgraph(&gdriver, &gmode, (char*)"...\\BGI");
}

void displayInfo(char *msg){
  setcolor(RED);
  setfillstyle(SOLID_FILL, GREEN);
  bar(INFOAREALEFT+1,INFOAREATOP+1,INFOAREALEFT+400,INFOAREATOP+INFOAREAHEIGHT-1);
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1.5);
  outtextxy(INFOAREALEFT+30,INFOAREATOP+50,msg);
}

void clearDisplayArea(){
  setfillstyle(SOLID_FILL, BLACK);
  bar(LEFTCORNER+CELL_SIZE,0,(LEFTCORNER+BOARDWIDTH-CELL_SIZE),TOPCORNER-1);
}

void fillGrid( )
{
 int x = LEFTCORNER+CELL_SIZE,  y = TOPCORNER;
 setcolor(GRID_COLOR);
 for(int i=1;i<=NB_ROWS;i++)
 {
     for (int j=1;j<=NB_COLS;j++)
     { rectangle(x,y,x+CELL_SIZE,y+CELL_SIZE);
       x+=CELL_SIZE;
     }
     x=LEFTCORNER+CELL_SIZE;
     y+=CELL_SIZE;
 }
}

void drawBoard(){
 // Playing Board
 setfillstyle(SOLID_FILL, WHITE);
 bar(LEFTCORNER,TOPCORNER,LEFTCORNER+BOARDWIDTH,TOPCORNER+BOARDHEIGHT);
 setfillstyle(SOLID_FILL, BOARD_COLOR);
 bar(LEFTCORNER+CELL_SIZE,TOPCORNER,(LEFTCORNER+BOARDWIDTH-CELL_SIZE),(TOPCORNER+BOARDHEIGHT-CELL_SIZE));
 fillGrid();
}

void reDrawCellsGrid(int xLeft, int yTop, int nbCells, int orientation)
  { // redraw the grid of cells
      int i;
      setcolor(BORDER_COLOR);
      for (i=1; i<=nbCells; i++) {
       rectangle(xLeft, yTop, xLeft+CELL_SIZE, yTop+CELL_SIZE);
       if (orientation == HORIZONTAL)  xLeft=xLeft+CELL_SIZE;
       else yTop = yTop + CELL_SIZE;
      }
  }

//draws Bar Block
void drawBarBlock(int xLeft, int yTop, int orientation, int fillingColor)
{
     setfillstyle(SOLID_FILL, fillingColor);
     if (orientation==HORIZONTAL) {
	  bar(xLeft, yTop, xLeft+4*CELL_SIZE,yTop+CELL_SIZE);
	  reDrawCellsGrid(xLeft, yTop, 4, HORIZONTAL);
     }
     else  {// orientation is VERTICAL
	  bar(xLeft, yTop, xLeft+CELL_SIZE, yTop+4*CELL_SIZE);
	  reDrawCellsGrid(xLeft, yTop ,4, VERTICAL);
     }
}

// generates Bar block in random orientation
void generateBarBlock(int & orientation, int & xLeft, int & yTop, int & fillingColor)
{
	orientation = rand() % 2 + 1; //VERTICAL || HORIZONTAL
	fillingColor = rand() % 4 + 1; // CHOOSES COLOR FROM 1 - 4
	yTop = TOPCORNER;
	if (orientation == HORIZONTAL) xLeft  = LEFTCORNER+4*CELL_SIZE;
	else    xLeft = LEFTCORNER+5*CELL_SIZE;
	drawBarBlock(xLeft,yTop,orientation, fillingColor);
}

void drawZBlock(int xLeft, int yTop, int orientation, int fillingColor)
{
     setfillstyle(SOLID_FILL, fillingColor);
     if (orientation==HORIZONTAL) {
	  bar(xLeft, yTop+CELL_SIZE, xLeft+2*CELL_SIZE,yTop+2*CELL_SIZE);
	  reDrawCellsGrid(xLeft, yTop, 2, HORIZONTAL);
	  bar(xLeft+CELL_SIZE, yTop+CELL_SIZE, xLeft+3*CELL_SIZE, yTop+CELL_SIZE);
	  reDrawCellsGrid(xLeft, yTop+CELL_SIZE, 2, HORIZONTAL);
     }
     else  {// orientation is VERTICAL
	  bar(xLeft, yTop, xLeft+CELL_SIZE, yTop+2*CELL_SIZE);
	  reDrawCellsGrid(xLeft, yTop , 2, VERTICAL);
	  bar(xLeft+CELL_SIZE, yTop+CELL_SIZE, xLeft+2*CELL_SIZE, yTop+3*CELL_SIZE);
	  reDrawCellsGrid(xLeft+CELL_SIZE, yTop+CELL_SIZE,2, VERTICAL);
     }
}

// generates Bar block in random orientation
void generateZBlock(int & orientation, int & xLeft, int & yTop, int & fillingColor)
{
	orientation = rand() % 2 + 1; //VERTICAL || HORIZONTAL
	fillingColor = rand() % 4 + 1; // CHOOSES COLOR FROM 1 - 4
	yTop = TOPCORNER;
	if (orientation == HORIZONTAL) xLeft  = LEFTCORNER+5*CELL_SIZE;
	else    xLeft = LEFTCORNER+5*CELL_SIZE;
	drawZBlock(xLeft,yTop,orientation, fillingColor);
}

void drawZRBlock(int xLeft, int yTop, int orientation, int fillingColor)
{
     setfillstyle(SOLID_FILL, fillingColor);
     if (orientation==HORIZONTAL) {
	  bar(xLeft, yTop, xLeft+CELL_SIZE,yTop+CELL_SIZE);
	  reDrawCellsGrid(xLeft, yTop, 2, HORIZONTAL);
	  bar(xLeft+CELL_SIZE, yTop+CELL_SIZE, xLeft+3*CELL_SIZE,yTop+2*CELL_SIZE);
	  reDrawCellsGrid(xLeft+CELL_SIZE, yTop+CELL_SIZE, 2, HORIZONTAL);
     }
     else  {// orientation is VERTICAL
	  bar(xLeft+CELL_SIZE, yTop, xLeft+2*CELL_SIZE,yTop+2*CELL_SIZE);
	  reDrawCellsGrid(xLeft+CELL_SIZE, yTop, 2, VERTICAL);
	  bar(xLeft, yTop+CELL_SIZE, xLeft+CELL_SIZE,yTop+3*CELL_SIZE);
	  reDrawCellsGrid(xLeft, yTop+CELL_SIZE, 2, VERTICAL);
     }
}

// generates Bar block in random orientation
void generateZRBlock(int & orientation, int & xLeft, int & yTop, int & fillingColor)
{
	orientation = rand() % 2 + 1; //VERTICAL || HORIZONTAL
	fillingColor = rand() % 4 + 1; // CHOOSES COLOR FROM 1 - 4
	yTop = TOPCORNER;
	if (orientation == HORIZONTAL) xLeft  = LEFTCORNER+5*CELL_SIZE;
	else    xLeft = LEFTCORNER+5*CELL_SIZE;
	drawZRBlock(xLeft,yTop,orientation, fillingColor);
}

void drawBoxBlock (int xLeft, int yTop, int fillingColor)
{
    setfillstyle(SOLID_FILL, fillingColor);
    bar(xLeft, yTop, xLeft + 2*CELL_SIZE, yTop + 2*CELL_SIZE);
    reDrawCellsGrid(xLeft, yTop, 2, HORIZONTAL);
    reDrawCellsGrid(xLeft, yTop+CELL_SIZE, 2, HORIZONTAL);
}

void generateBoxBlock (int &xLeft, int &yTop, int &fillingColor)
{
    fillingColor = rand() % 4 + 1;
    yTop = TOPCORNER;
    xLeft = LEFTCORNER + 5*CELL_SIZE;
    drawBoxBlock(xLeft, yTop, fillingColor);
}

void drawTBlock(int xLeft, int yTop, int orientation, int fillingColor)
{
    switch (orientation)
    {
    case DOWN:
        setfillstyle(SOLID_FILL, fillingColor);
        bar(xLeft, yTop, xLeft+3*CELL_SIZE, yTop+CELL_SIZE);
        reDrawCellsGrid(xLeft, yTop, 3, HORIZONTAL);
        bar(xLeft+CELL_SIZE, yTop+CELL_SIZE, xLeft+2*CELL_SIZE, yTop+2*CELL_SIZE);
        reDrawCellsGrid(xLeft+CELL_SIZE, yTop+CELL_SIZE, 1, HORIZONTAL);
        break;
    case UP:
        setfillstyle(SOLID_FILL, fillingColor);
        bar(xLeft+CELL_SIZE, yTop, xLeft+2*CELL_SIZE, yTop+CELL_SIZE);
        reDrawCellsGrid(xLeft+CELL_SIZE, yTop, 1, HORIZONTAL);
        bar(xLeft, yTop+CELL_SIZE, xLeft+3*CELL_SIZE, yTop+2*CELL_SIZE);
        reDrawCellsGrid(xLeft, yTop+CELL_SIZE, 3, HORIZONTAL);
        break;
    case RIGHT:
        setfillstyle(SOLID_FILL, fillingColor);
        bar(xLeft, yTop, xLeft+CELL_SIZE, yTop+3*CELL_SIZE);
        reDrawCellsGrid(xLeft, yTop, 3, VERTICAL);
        bar(xLeft+CELL_SIZE, yTop+CELL_SIZE, xLeft+2*CELL_SIZE, yTop+2*CELL_SIZE);
        reDrawCellsGrid(xLeft, yTop+CELL_SIZE, 2, HORIZONTAL);
        break;
    case LEFT:
        setfillstyle(SOLID_FILL, fillingColor);
        bar(xLeft, yTop+CELL_SIZE, xLeft+CELL_SIZE, yTop+2*CELL_SIZE);
        reDrawCellsGrid(xLeft, yTop+CELL_SIZE, 1, VERTICAL);
        bar(xLeft+CELL_SIZE, yTop, xLeft+2*CELL_SIZE, yTop+3*CELL_SIZE);
        reDrawCellsGrid(xLeft+CELL_SIZE, yTop, 3, VERTICAL);
        break;
    }
}

void generateTBlock(int &orientation, int &xLeft, int &yTop, int &fillingColor)
{
    orientation = rand() % 4 + 1;
    fillingColor = rand() % 4 + 1;
    yTop = TOPCORNER;
    if (orientation == DOWN || orientation == UP)
    xLeft = LEFTCORNER+4*CELL_SIZE;
    else xLeft = LEFTCORNER+5*CELL_SIZE;
    drawTBlock(xLeft,yTop,orientation, fillingColor);
}

void drawLBlock(int xLeft, int yTop, int orientation, int fillingColor)
{
    setfillstyle(SOLID_FILL, fillingColor);
    switch(orientation)
    {
    case DOWN:
        bar(xLeft, yTop, xLeft+3*CELL_SIZE, yTop+CELL_SIZE);
        reDrawCellsGrid(xLeft, yTop, 3, HORIZONTAL);
        bar(xLeft, yTop+CELL_SIZE, xLeft+CELL_SIZE, yTop+2*CELL_SIZE);
        reDrawCellsGrid(xLeft, yTop+CELL_SIZE, 1, HORIZONTAL);
        break;
    case LEFT:
        bar(xLeft, yTop, xLeft+CELL_SIZE, yTop+CELL_SIZE);
        reDrawCellsGrid(xLeft, yTop, 1, HORIZONTAL);
        bar(xLeft+CELL_SIZE, yTop, xLeft+2*CELL_SIZE, yTop+3*CELL_SIZE);
        reDrawCellsGrid(xLeft+CELL_SIZE, yTop, 3, VERTICAL);
        break;
    case UP:
        bar(xLeft+2*CELL_SIZE, yTop, xLeft+3*CELL_SIZE, yTop+CELL_SIZE);
        reDrawCellsGrid(xLeft+2*CELL_SIZE, yTop, 1, VERTICAL);
        bar(xLeft, yTop+CELL_SIZE, xLeft+3*CELL_SIZE, yTop+2*CELL_SIZE);
        reDrawCellsGrid(xLeft, yTop+CELL_SIZE, 3, HORIZONTAL);
        break;
    case RIGHT:
        bar(xLeft, yTop, xLeft+CELL_SIZE, yTop+3*CELL_SIZE);
        reDrawCellsGrid(xLeft, yTop, 3, VERTICAL);
        bar(xLeft+CELL_SIZE, yTop+2*CELL_SIZE, xLeft+2*CELL_SIZE, yTop+3*CELL_SIZE);
        reDrawCellsGrid(xLeft+CELL_SIZE, yTop+2*CELL_SIZE,1,VERTICAL);
    }
}

void generateLBlock(int & orientation, int & xLeft, int & yTop, int & fillingColor)
{
    yTop = TOPCORNER;
    xLeft = LEFTCORNER+5*CELL_SIZE;
    drawLBlock(xLeft, yTop, orientation, fillingColor);
}

void drawLRBlock(int xLeft, int yTop, int orientation, int fillingColor)
{
    setfillstyle(SOLID_FILL, fillingColor);
    switch(orientation)
    {
    case DOWN:
        bar(xLeft, yTop, xLeft+3*CELL_SIZE, yTop+CELL_SIZE);
        reDrawCellsGrid(xLeft, yTop, 3, HORIZONTAL);
        bar(xLeft+CELL_SIZE*2, yTop+CELL_SIZE, xLeft+CELL_SIZE*3, yTop+2*CELL_SIZE);
        reDrawCellsGrid(xLeft+CELL_SIZE*2, yTop+CELL_SIZE, 1, HORIZONTAL);
        break;
    case LEFT:
        bar(xLeft, yTop+CELL_SIZE*2, xLeft+CELL_SIZE, yTop+CELL_SIZE*3);
        reDrawCellsGrid(xLeft, yTop+CELL_SIZE*2, 1, HORIZONTAL);
        bar(xLeft+CELL_SIZE, yTop, xLeft+2*CELL_SIZE, yTop+3*CELL_SIZE);
        reDrawCellsGrid(xLeft+CELL_SIZE, yTop, 3, VERTICAL);
        break;
    case UP:
        bar(xLeft, yTop, xLeft+CELL_SIZE, yTop+CELL_SIZE);
        reDrawCellsGrid(xLeft, yTop, 1, HORIZONTAL);
        bar(xLeft, yTop+CELL_SIZE, xLeft+3*CELL_SIZE, yTop+2*CELL_SIZE);
        reDrawCellsGrid(xLeft, yTop+CELL_SIZE, 3, HORIZONTAL);
        break;
    case RIGHT:
        bar(xLeft, yTop, xLeft+CELL_SIZE, yTop+3*CELL_SIZE);
        reDrawCellsGrid(xLeft, yTop, 3, VERTICAL);
        bar(xLeft+CELL_SIZE, yTop, xLeft+2*CELL_SIZE, yTop+CELL_SIZE);
        reDrawCellsGrid(xLeft+CELL_SIZE, yTop,1,VERTICAL);
    }
}

void generateLRBlock(int &orientation, int &xLeft, int &yTop, int &fillingColor)
{
    yTop = TOPCORNER;
    xLeft = LEFTCORNER+5*CELL_SIZE;
    drawLRBlock(xLeft, yTop, orientation, fillingColor);
}

// generates a block at random
void generateNewBlock( int * blockId, int * orientation,int * xLeft, int *yTop, int *fillingColor)
     {
       *blockId = rand() % 5 + 1; // random(NB_BLOCKS) + 1;
       switch(*blockId) {
	case T_BLOCK  : generateTBlock(*orientation, *xLeft, *yTop, *fillingColor); break;
	case L_BLOCK  : generateLBlock(*orientation, *xLeft, *yTop, *fillingColor); break;
	case LR_BLOCK : generateLRBlock(*orientation, *xLeft, *yTop, *fillingColor); break;
	case BOX_BLOCK: generateBoxBlock(*xLeft, *yTop, *fillingColor); break;
	case BAR_BLOCK: generateBarBlock(*orientation, *xLeft, *yTop, *fillingColor); break;
	case Z_BLOCK: generateZBlock(*orientation, *xLeft, *yTop, *fillingColor); break;
	case ZR_BLOCK: generateZRBlock(*orientation, *xLeft, *yTop, *fillingColor); break;
       }
     }

void checkTranslateBoxRouteLeft(int xLeft, int yTop, int &freeRoute)
{
    xLeft = xLeft - CELL_SIZE/2;
    yTop = yTop + CELL_SIZE/2;
    freeRoute = 1;
    if (getpixel(xLeft, yTop) != BOARD_COLOR || getpixel(xLeft, yTop+CELL_SIZE) != BOARD_COLOR)
    freeRoute = 0;
}

void checkTranslateBoxRouteRight(int xLeft, int yTop, int &freeRoute)
{
    xLeft = xLeft + 2*CELL_SIZE/2;
    yTop = yTop + CELL_SIZE/2;
    freeRoute = 1;
    if (getpixel(xLeft, yTop) != BOARD_COLOR || getpixel(xLeft, yTop+CELL_SIZE) != BOARD_COLOR)
    freeRoute = 0;
}

void checkTranslateBoxRouteDown(int xLeft, int yTop, int &freeRoute)
{
    xLeft = xLeft + CELL_SIZE/2;
    yTop = yTop + 2.5*CELL_SIZE;
    freeRoute = 1;
    if (getpixel(xLeft, yTop) != BOARD_COLOR || getpixel(xLeft+CELL_SIZE, yTop)!= BOARD_COLOR)
    freeRoute = 0;
}

int checkTranslateBoxRoute(int xLeft, int yTop, int direction)
{
int freeRoute = 1;
switch (direction){
    case RIGHT: checkTranslateBoxRouteRight(xLeft, yTop, freeRoute); break;
    case LEFT: checkTranslateBoxRouteLeft(xLeft, yTop, freeRoute); break;
    case DOWN: checkTranslateBoxRouteDown(xLeft, yTop, freeRoute); break;
}
return freeRoute;
}

// check if Bar block can be moved to the left
void checkTranslateBarRouteLeft(int orientation, int xLeft, int yTop, int &freeRoute)
      {      int maxNbCells;
	  // check if route is not blocked
	  yTop = yTop + CELL_SIZE/2;
	  freeRoute = 1; //route is free
	  switch (orientation) {
	    case HORIZONTAL:
	       xLeft = xLeft - CELL_SIZE/2;
	       if (getpixel(xLeft, yTop) != BOARD_COLOR) freeRoute = 0;
	       break;

	    case VERTICAL:
	       maxNbCells = 4;
	       xLeft  = xLeft - CELL_SIZE/2;
	       do
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       while ( maxNbCells >= 1 && freeRoute);
	       break;
	  }
      }

// check if Bar block can be moved to the right
void checkTranslateBarRouteRight(int orientation, int xLeft, int yTop, int &freeRoute)
      {      int maxNbCells;
	  // check if route is not blocked

	  freeRoute = 1; //route is free
	  switch (orientation) {
	    case HORIZONTAL:
	       // maxNbCells = 1;
	       yTop = yTop + CELL_SIZE/2;
	       xLeft = xLeft + 4*CELL_SIZE + CELL_SIZE/2;
	       if (getpixel(xLeft, yTop) != BOARD_COLOR)
		    freeRoute = 0;
	       break;

	    case VERTICAL:
	       maxNbCells = 4;
	       yTop = yTop + CELL_SIZE/2;
	       xLeft  = xLeft + CELL_SIZE + CELL_SIZE/2;
	       do
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       while ( maxNbCells >= 1 && freeRoute);
	       break;
	  }
      }

// check if Bar block can be moved down
void checkTranslateBarRouteDown(int orientation, int xLeft, int yTop, int &
freeRoute)
      {      int maxNbCells;
	  // check if route is not blocked
	  xLeft = xLeft + CELL_SIZE/2;
	  freeRoute = 1; //route is not blocked
	  switch(orientation) {
	   case HORIZONTAL:
	       maxNbCells = 4;
	       yTop  = yTop + CELL_SIZE + CELL_SIZE/2;
	       do
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    xLeft = xLeft + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       while ( maxNbCells >= 1 && freeRoute);
	       break;

	   case VERTICAL:
	       yTop = yTop + 4*CELL_SIZE + CELL_SIZE/2;
	       if (getpixel(xLeft, yTop) != BOARD_COLOR) freeRoute = 0;
	       break;
	  }
      }

// Invoke the appropriate checking function for Bar block depending on the direction
int checkTranslateBarRoute(int orientation, int xLeft, int yTop, int direction)
{    int maxNbCells, freeRoute = 1;
     switch (direction) {
       case RIGHT: checkTranslateBarRouteRight(orientation, xLeft, yTop,
freeRoute); break;
       case LEFT:  checkTranslateBarRouteLeft(orientation, xLeft, yTop,
freeRoute); break;
       case DOWN:  checkTranslateBarRouteDown(orientation, xLeft, yTop,
freeRoute); break;
     }
     return freeRoute;
  }

// translate the Bar block
void translateBarBlock(int orientation, int & xLeft, int & yTop, int fillingColor, int direction)
  {
     // Erase the bar at current position
     drawBarBlock(xLeft, yTop, orientation, BKGRD_COLOR);
     switch (direction) {
       case RIGHT: xLeft = xLeft + CELL_SIZE; break;
       case LEFT : xLeft = xLeft - CELL_SIZE; break;
       case DOWN : yTop = yTop + CELL_SIZE;   break;
     }
     // Now redraw the bar at the new position
     drawBarBlock(xLeft, yTop, orientation, fillingColor);
  }

void checkTranslateTRouteLeft(int orientation, int xLeft, int yTop, int &freeRoute)
{      int maxNbCells;
	  // check if route is not blocked
	  yTop = yTop + CELL_SIZE/2;
      xLeft = xLeft - CELL_SIZE/2;

	  freeRoute = 1; //route is free
	  switch (orientation) {
	    case LEFT:
            if (getpixel(xLeft, yTop)!= BOARD_COLOR || getpixel(xLeft, yTop+CELL_SIZE)!= BOARD_COLOR || getpixel(xLeft, yTop+2*CELL_SIZE)!= BOARD_COLOR)
                freeRoute=0;
        break;
	    case RIGHT:
	       maxNbCells = 3;
	       do
                if (getpixel(xLeft, yTop) == BOARD_COLOR ){
                    yTop = yTop + CELL_SIZE;
                    maxNbCells--;
                }
                else  freeRoute = 0; // route is blocked
                    while ( maxNbCells >= 1 && freeRoute);
        break;
        case DOWN:
            if(getpixel(xLeft, yTop)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE, yTop+CELL_SIZE)!=BOARD_COLOR)
                freeRoute = 0;
        break;
        case UP:
            if(getpixel(xLeft+CELL_SIZE, yTop)!=BOARD_COLOR||getpixel(xLeft, yTop+CELL_SIZE)!=BOARD_COLOR)
                freeRoute = 0;
        break;
	  }
}

// check if Bar block can be moved to the right
void checkTranslateTRouteRight(int orientation, int xLeft, int yTop, int &freeRoute)
{
    int maxNbCells;
	  // check if route is not blocked

	  freeRoute = 1; //route is free
	  switch (orientation) {
	    case LEFT:
            yTop = yTop + CELL_SIZE/2;
            xLeft = xLeft + CELL_SIZE*2.5;
            maxNbCells = 3;
	       do
                if (getpixel(xLeft, yTop) == BOARD_COLOR ){yTop = yTop + CELL_SIZE;
                    maxNbCells--;
                }
                else  freeRoute = 0; // route is blocked
                while ( maxNbCells >= 1 && freeRoute);
        break;

	    case RIGHT:
            yTop = yTop + CELL_SIZE/2;
            xLeft = xLeft + CELL_SIZE*1.5;
            if (getpixel(xLeft, yTop)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE, yTop+CELL_SIZE)!=BOARD_COLOR||getpixel(xLeft, yTop+2*CELL_SIZE)!=BOARD_COLOR)
                freeRoute = 0;
	       break;

        case DOWN:
            yTop = yTop + CELL_SIZE/2;
            xLeft = xLeft + CELL_SIZE*3.5;
            if(getpixel(xLeft, yTop)!=BOARD_COLOR||getpixel(xLeft-CELL_SIZE, yTop+CELL_SIZE)!=BOARD_COLOR)
                freeRoute = 0;
            break;

        case UP:
            yTop = yTop + CELL_SIZE/2;
            xLeft = xLeft + CELL_SIZE*2.5;
            if(getpixel(xLeft, yTop)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE, yTop+CELL_SIZE)!=BOARD_COLOR)
                freeRoute = 0;
            break;
	  }
}

// check if Bar block can be moved down
void checkTranslateTRouteDown(int orientation, int xLeft, int yTop, int &freeRoute)
{
    int maxNbCells;
	  // check if route is not blocked

	  freeRoute = 1; //route is not blocked
	  switch(orientation) {
	   case RIGHT:
            xLeft = xLeft + CELL_SIZE/2;
            yTop  = yTop +CELL_SIZE*3.5;
            if (getpixel(xLeft, yTop)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE, yTop-CELL_SIZE))
                freeRoute = 0;
	       break;

	   case LEFT:
            xLeft = xLeft + CELL_SIZE/2;
            yTop  = yTop +CELL_SIZE*2.5;
	       if (getpixel(xLeft, yTop) != BOARD_COLOR||getpixel(xLeft+CELL_SIZE, yTop+CELL_SIZE))
                freeRoute = 0;
	       break;
       case DOWN:
            xLeft = xLeft + CELL_SIZE/2;
            yTop = yTop + CELL_SIZE*1.5;
            if (getpixel(xLeft, yTop)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE, yTop+CELL_SIZE)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE*2, yTop)!=BOARD_COLOR)
                freeRoute = 0;
            break;
       case UP:
            maxNbCells = 3;
            xLeft = xLeft + CELL_SIZE/2;
            yTop = yTop + CELL_SIZE*2.5;
            do
                if (getpixel(xLeft,yTop)==BOARD_COLOR){
                    xLeft+=CELL_SIZE;
                    maxNbCells--;
                }else freeRoute = 0;
            while(maxNbCells > 0 && freeRoute);
	  }
      }

void checkTranslateLRouteDown(int orientation, int xLeft, int yTop, int &freeRoute)
{
    freeRoute = 1;
    int maxcells;
    switch(orientation)
    {
    case DOWN:
    xLeft+=CELL_SIZE/2;
    yTop+=CELL_SIZE*2.5;
    if(getpixel(xLeft, yTop)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE, yTop-CELL_SIZE)!=BOARD_COLOR||getpixel(xLeft+2*CELL_SIZE, yTop-CELL_SIZE))
        freeRoute = 0;
    break;
    case LEFT:
    xLeft+=CELL_SIZE/2;
    yTop+=CELL_SIZE*1.5;
    if(getpixel(xLeft, yTop)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE, yTop+2*CELL_SIZE)!=BOARD_COLOR)
        freeRoute = 0;
    break;
    case UP:
    xLeft+=CELL_SIZE/2;
    yTop+=CELL_SIZE*2.5;
    maxcells = 3;
    if(getpixel(xLeft,yTop)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE, yTop)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE*2, yTop)!=BOARD_COLOR)
        freeRoute = 0;
    break;
    case RIGHT:
    xLeft+=CELL_SIZE/2;
    yTop+=CELL_SIZE*3.5;
    if(getpixel(xLeft, yTop)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE, yTop))
        freeRoute = 0;
    break;
    }
}

void checkTranslateLRouteRight(int orientation, int xLeft, int yTop, int &freeRoute)
{
    int maxcells;
    freeRoute = 1;
    yTop+=CELL_SIZE/2;
    switch (orientation)
    {
    case DOWN:
        xLeft+=CELL_SIZE*3.5;
        if(getpixel(xLeft,yTop)!=BOARD_COLOR||getpixel(xLeft-CELL_SIZE*2, yTop+CELL_SIZE)!=BOARD_COLOR)
            freeRoute = 0;
            break;
    case LEFT:
    maxcells=3;
    xLeft+=CELL_SIZE*2.5;
    while(maxcells>0 && freeRoute==1)
    {
        if(getpixel(xLeft,yTop)==BOARD_COLOR)
        {
            yTop+=CELL_SIZE;
            maxcells--;
        }else freeRoute = 0;
    }
    break;
    case UP:
    xLeft+=CELL_SIZE*3.5;
    if (getpixel(xLeft,yTop)!=BOARD_COLOR||getpixel(xLeft,yTop+CELL_SIZE)!=BOARD_COLOR)
        freeRoute = 0;
    break;
    case RIGHT:
    xLeft+=CELL_SIZE*1.5;
    if (getpixel(xLeft, yTop)!=BOARD_COLOR||getpixel(xLeft, yTop+CELL_SIZE)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE, yTop+CELL_SIZE*2)!=BOARD_COLOR)
        freeRoute=0;
    break;
    }
}

void checkTranslateLRouteLeft(int orientation, int xLeft, int yTop, int &freeRoute)
{
    freeRoute = 1;
    int maxcells;
    xLeft-=CELL_SIZE/2;
    yTop+=CELL_SIZE/2;
    switch (orientation)
    {
    case DOWN:
        if(getpixel(xLeft, yTop)!=BOARD_COLOR||getpixel(xLeft, yTop+CELL_SIZE!=CELL_SIZE))
           freeRoute = 0;
        break;
    case LEFT:
        if(getpixel(xLeft, yTop)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE, yTop+CELL_SIZE)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE, yTop+CELL_SIZE*2)!=BOARD_COLOR)
            freeRoute = 0;
        break;
    case UP:
        if(getpixel(xLeft+CELL_SIZE*2, yTop)!=BOARD_COLOR||getpixel(xLeft, yTop+CELL_SIZE))
            freeRoute = 0;
        break;
    case RIGHT:
        maxcells = 3;
        while(maxcells>0 && freeRoute==1)
        {
            if(getpixel(xLeft,yTop)==BOARD_COLOR)
            {
                yTop+=CELL_SIZE;
                maxcells--;
            }
        else freeRoute = 0;
        }
    }
}

void checkTranslateLRRouteDown(int orientation, int xLeft, int yTop, int &freeRoute){
freeRoute = 1;
int maxcells;
xLeft += CELL_SIZE/2;
switch (orientation){
case LEFT:
    yTop += CELL_SIZE*3.5;
    if(getpixel(xLeft, yTop)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE, yTop)!=BOARD_COLOR)
        freeRoute = 0;
    break;
case UP:
    maxcells = 3;
    yTop += CELL_SIZE*2.5;
    while(maxcells>0 && freeRoute){
        if (getpixel(xLeft,yTop)==BOARD_COLOR){
            xLeft+=CELL_SIZE;
            maxcells--;
        }else freeRoute = 0;
    }
    break;
case RIGHT:
    yTop += CELL_SIZE*3.5;
    if (getpixel(xLeft, yTop)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE, yTop-CELL_SIZE*2))
        freeRoute = 0;
    break;
case DOWN:
    yTop += CELL_SIZE*1.5;
    if (getpixel(xLeft, yTop)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE, yTop)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE*2, yTop+CELL_SIZE))
        freeRoute = 0;
    break;
}
}

void checkTranslateLRRouteLeft(int orientation, int xLeft, int yTop, int &freeRoute){
freeRoute = 1;
int maxcells;
xLeft-=CELL_SIZE/2;
yTop+=CELL_SIZE/2;
switch(orientation){
case LEFT:
    if(getpixel(xLeft+CELL_SIZE, yTop)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE, yTop+CELL_SIZE)!=BOARD_COLOR||getpixel(xLeft, yTop+CELL_SIZE*2))
        freeRoute = 0;
    break;
case UP:
    if (getpixel(xLeft, yTop)!=BOARD_COLOR||getpixel(xLeft, yTop+CELL_SIZE)!=BOARD_COLOR)
        freeRoute = 0;
    break;
case RIGHT:
    maxcells = 3;
    while (maxcells>0 && freeRoute){
        if (getpixel(xLeft,yTop)==BOARD_COLOR){
            maxcells--;
            yTop+=CELL_SIZE;
        }else freeRoute = 0;
    }
    break;
case DOWN:
    if (getpixel(xLeft, yTop)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE*2, yTop+CELL_SIZE))
        freeRoute=0;
    break;
}
}

void checkTranslateLRRouteRight(int orientation, int xLeft, int yTop, int &freeRoute){
freeRoute = 1;
int maxcells;
yTop+=CELL_SIZE/2;
switch(orientation){
case LEFT:
    xLeft+=CELL_SIZE*2.5;
    maxcells = 3;
    while (maxcells > 0 && freeRoute){
        if (getpixel(xLeft,yTop)==BOARD_COLOR){
            yTop+=CELL_SIZE;
            maxcells--;
        }else freeRoute = 0;
    }
    break;
case UP:
    xLeft+=CELL_SIZE*1.5;
    if (getpixel(xLeft,yTop)!=BOARD_COLOR||getpixel(xLeft+CELL_SIZE*2, yTop+CELL_SIZE)!=BOARD_COLOR)
        freeRoute = 0;
    break;
case RIGHT:
    xLeft+=CELL_SIZE*1.5;
    if (getpixel(xLeft+CELL_SIZE, yTop)!=BOARD_COLOR||getpixel(xLeft, yTop+CELL_SIZE)!=BOARD_COLOR||getpixel(xLeft,yTop+CELL_SIZE*2)!=BOARD_COLOR)
        freeRoute = 0;
    break;
case DOWN:
    xLeft+=CELL_SIZE*3.5;
    maxcells = 2;
    while (maxcells>0){
        if (getpixel(xLeft, yTop)==BOARD_COLOR){
            yTop+=CELL_SIZE;
            maxcells--;
        }else freeRoute = 0;
    }
    break;
}
}

int checkTranslateTRoute(int orientation, int xLeft, int yTop, int direction)
{
    int freeRoute = 1;
    switch (direction)
    {
    case RIGHT: checkTranslateTRouteRight(orientation, xLeft, yTop, freeRoute); break;
    case LEFT:  checkTranslateTRouteLeft(orientation, xLeft, yTop, freeRoute); break;
    case DOWN:  checkTranslateTRouteDown(orientation, xLeft, yTop, freeRoute); break;
    }
     return freeRoute;
}

int checkTranslateLRoute(int orientation, int xLeft, int yTop,int direction)
{
    int freeRoute = 1;
    switch(direction)
    {
    case RIGHT:checkTranslateLRouteRight(orientation, xLeft, yTop, freeRoute); break;
    case LEFT: checkTranslateLRouteLeft(orientation, xLeft, yTop, freeRoute); break;
    case DOWN: checkTranslateLRouteDown(orientation, xLeft, yTop, freeRoute); break;
    }
    return freeRoute;
}

int checkTranslateLRRoute(int orientation, int xLeft, int yTop,int direction)
{
    int freeRoute = 1;
    switch(direction)
    {
    case RIGHT:checkTranslateLRRouteRight(orientation, xLeft, yTop, freeRoute); break;
    case LEFT: checkTranslateLRRouteLeft(orientation, xLeft, yTop, freeRoute); break;
    case DOWN: checkTranslateLRRouteDown(orientation, xLeft, yTop, freeRoute); break;
    }
    return freeRoute;
}

void translateBoxBlock(int & xLeft, int & yTop, int fillingColor, int direction)
{
     drawBoxBlock(xLeft, yTop, BKGRD_COLOR);
     switch (direction)
     {
       case RIGHT: xLeft = xLeft + CELL_SIZE; break;
       case LEFT : xLeft = xLeft - CELL_SIZE; break;
       case DOWN : yTop = yTop + CELL_SIZE; break;
     }
     drawBoxBlock(xLeft, yTop, fillingColor);
}

void translateTBlock(int orientation, int & xLeft, int & yTop, int fillingColor, int direction)
{
     drawTBlock(xLeft, yTop, orientation, BKGRD_COLOR);
     switch (direction) {
       case RIGHT: xLeft = xLeft + CELL_SIZE; break;
       case LEFT : xLeft = xLeft - CELL_SIZE; break;
       case DOWN : yTop = yTop + CELL_SIZE;   break;
     }
     drawTBlock(xLeft, yTop, orientation, fillingColor);
}

void translateLBlock(int orientation, int & xLeft, int & yTop, int fillingColor, int direction)
{
     drawLBlock(xLeft, yTop, orientation, BKGRD_COLOR);
     switch (direction)
     {
       case RIGHT: xLeft = xLeft + CELL_SIZE; break;
       case LEFT : xLeft = xLeft - CELL_SIZE; break;
       case DOWN : yTop = yTop + CELL_SIZE;   break;
     }
     drawLBlock(xLeft, yTop, orientation, fillingColor);
}

void translateLRBlock(int orientation, int & xLeft, int & yTop, int fillingColor, int direction)
{
     drawLRBlock(xLeft, yTop, orientation, BKGRD_COLOR);
     switch (direction)
     {
       case RIGHT: xLeft = xLeft + CELL_SIZE; break;
       case LEFT : xLeft = xLeft - CELL_SIZE; break;
       case DOWN : yTop = yTop + CELL_SIZE;   break;
     }
     drawLRBlock(xLeft, yTop, orientation, fillingColor);
}

int translateRouteFree(int blockId, int orientation, int xLeft, int yTop, int direction)
{
    int freeRoute;
    switch(blockId)
    {
      case T_BLOCK  : freeRoute = checkTranslateTRoute(orientation, xLeft, yTop, direction); break;
      case L_BLOCK  : freeRoute = checkTranslateLRoute(orientation, xLeft, yTop, direction); break;
      case LR_BLOCK : freeRoute = checkTranslateLRRoute(orientation, xLeft, yTop, direction); break;
      case BOX_BLOCK: freeRoute = checkTranslateBoxRoute(xLeft, yTop, direction); break;
      case BAR_BLOCK: freeRoute = checkTranslateBarRoute(orientation, xLeft, yTop, direction); break;
    }
    return freeRoute;
}

// Invoke the appropriate function for translation depending on block Id
void translateBlock(int blockId, int & orientation, int & xLeft, int & yTop, int fillingColor, int direction)
{
    switch(blockId)
    {
      case T_BLOCK  : translateTBlock(orientation, xLeft, yTop, fillingColor, direction); break;
      case L_BLOCK  : translateLBlock(orientation, xLeft, yTop, fillingColor, direction); break;
      case LR_BLOCK : translateLRBlock(orientation, xLeft, yTop, fillingColor, direction); break;
      case BOX_BLOCK: translateBoxBlock(xLeft, yTop, fillingColor, direction); break;
      case BAR_BLOCK: translateBarBlock(orientation, xLeft, yTop, fillingColor, direction); break;
    }
}

// Check if a Bar block can be rotated
int checkRotateBarRoute(int orientation, int xLeft, int yTop)
  {  int maxNbCells, x, y, freeRoute;
     switch (orientation) {
      case HORIZONTAL:
	// Checking upper three cells
	maxNbCells = 3;
	freeRoute = 1;
	x = xLeft + CELL_SIZE + CELL_SIZE/2;
	y = yTop  + CELL_SIZE + CELL_SIZE/2;
	do
	   if (getpixel(x, y) == BOARD_COLOR ){
	      x = x + CELL_SIZE;
	      maxNbCells--;
	   }
	   else  freeRoute = 0; // route is blocked
	while (maxNbCells >=1 && freeRoute);

	// Checking lower three cells
	if (freeRoute) { // if route is so far free
	   maxNbCells = 3;
	   freeRoute = 1;
	   x = xLeft + CELL_SIZE   + CELL_SIZE/2;
	   y = yTop  + 2*CELL_SIZE + CELL_SIZE/2;
	   do
	   if (getpixel(x, y) == BOARD_COLOR ){
	       x = x + CELL_SIZE;
	       maxNbCells--;
	   }
	   else  freeRoute = 0; // route is blocked
	   while (maxNbCells >=1 && freeRoute);
	}
	break;

      case VERTICAL:
	// Checking left two cells
	maxNbCells = 2;
	freeRoute = 1; // assume route is free
	x = xLeft - CELL_SIZE/2;
	y = yTop  + CELL_SIZE/2;
	do
	   if (getpixel(x, y) == BOARD_COLOR ){
	    y = y + CELL_SIZE;
	    maxNbCells--;
	   }
	   else  freeRoute = 0; // route is blocked
	while (maxNbCells > 0 && freeRoute);

	// Checking middle three cells
	if (freeRoute) { // if route is so far free
	   maxNbCells = 3;
	   freeRoute  = 1;
	   x = xLeft + CELL_SIZE + CELL_SIZE/2;
	   y = yTop  + CELL_SIZE + CELL_SIZE/2;
	   do
	  if (getpixel(x, y) == BOARD_COLOR ){
	     y = y + CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0; // route is blocked
	   while (maxNbCells > 0 && freeRoute);
	}

	// right most three cells
	if (freeRoute) { // if route is so far free
	   maxNbCells = 3;
	   freeRoute = 1;
	   x = xLeft + 2*CELL_SIZE + CELL_SIZE/2;
	   y = yTop  + CELL_SIZE   + CELL_SIZE/2;
	   do
	  if (getpixel(x, y) == BOARD_COLOR ){
	     y = y + CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0; // route is blocked
	   while (maxNbCells > 0 && freeRoute);
	}
	break;
     }
     return freeRoute;
  }

int checkRotateTBlockRoute(int orientation, int xLeft, int yTop){

    int maxNbCells, x, y, freeRoute = 0;
    switch (orientation){
    case LEFT:
        x = xLeft + CELL_SIZE/2;
        y = yTop + CELL_SIZE/2;
        if (getpixel(x, y) == BOARD_COLOR ){
            x = x + 2.5*CELL_SIZE;
            if (getpixel(x, y) == BOARD_COLOR ) {
                y += CELL_SIZE;
                if (getpixel(x, y) == BOARD_COLOR ) freeRoute = 1;
             }
        } break;
    case UP:
        x = xLeft + CELL_SIZE/2;
        y = yTop + CELL_SIZE/2;
         if (getpixel(x, y) == BOARD_COLOR ){
                y -= CELL_SIZE;
                if (getpixel(x, y) == BOARD_COLOR ){
                    x += CELL_SIZE;
                    if (getpixel(x, y) == BOARD_COLOR ){
                            y += CELL_SIZE*3;
                            if (getpixel(x, y) == BOARD_COLOR ){
                                x += CELL_SIZE;
                                if (getpixel(x, y) == BOARD_COLOR ) freeRoute = 1;
                            }
                    }
                }
         }
         break;
    case RIGHT:
        x = xLeft - CELL_SIZE/2;
        y = yTop + CELL_SIZE*1.5;
        if (getpixel(x, y) == BOARD_COLOR ){
            y += CELL_SIZE;
            if (getpixel(x, y) == BOARD_COLOR ){
                x += CELL_SIZE*2;
                y -= CELL_SIZE*2;
                if (getpixel(x, y) == BOARD_COLOR ) freeRoute = 1;
            }
        } break;
    case DOWN:
        x = xLeft + CELL_SIZE*2.5;
        y = yTop + CELL_SIZE*1.5;
        if (getpixel(x, y) == BOARD_COLOR ){
            x -= CELL_SIZE*2;
            if (getpixel(x, y) == BOARD_COLOR ){
                y -= CELL_SIZE*2;
                if (getpixel(x, y) == BOARD_COLOR ){
                    x += CELL_SIZE;
                    if (getpixel(x, y) == BOARD_COLOR ) freeRoute = 1;
                }
            }
        } break;
    }
return freeRoute;
}

int checkRotateLRoute(int orientation, int xLeft, int yTop){
int freeRoute = 0;
int maxcells;
switch (orientation){
case DOWN:
    xLeft-=CELL_SIZE/2;
    yTop+=CELL_SIZE/2;
    if( getpixel(xLeft, yTop)==BOARD_COLOR &&
        getpixel(xLeft,yTop+CELL_SIZE)==BOARD_COLOR &&
        getpixel(xLeft+CELL_SIZE*2, yTop+CELL_SIZE)==BOARD_COLOR&&
        getpixel(xLeft+CELL_SIZE*2, yTop+CELL_SIZE*2)==BOARD_COLOR
      )
        freeRoute = 1;
    break;

case LEFT:
    xLeft+=CELL_SIZE*2.5;
    yTop+=CELL_SIZE/2;
    if( getpixel(xLeft, yTop)== BOARD_COLOR &&
        getpixel(xLeft, yTop+CELL_SIZE)==BOARD_COLOR &&
        getpixel(xLeft-CELL_SIZE*2, yTop+CELL_SIZE)==BOARD_COLOR &&
        getpixel(xLeft-CELL_SIZE*2, yTop+CELL_SIZE*2)==BOARD_COLOR
      )
        freeRoute = 1;
    break;

case UP:
    xLeft+=CELL_SIZE/2;
    yTop+=CELL_SIZE/2;
    if( getpixel(xLeft, yTop)== BOARD_COLOR &&
        getpixel(xLeft+CELL_SIZE, yTop)== BOARD_COLOR &&
        getpixel(xLeft, yTop+CELL_SIZE*2)== BOARD_COLOR &&
        getpixel(xLeft+CELL_SIZE, yTop+CELL_SIZE*2)== BOARD_COLOR
      )
        freeRoute = 1;
    break;

case RIGHT:
    xLeft+=CELL_SIZE*1.5;
    yTop+=CELL_SIZE/2;
    if( getpixel(xLeft, yTop)==BOARD_COLOR &&
        getpixel(xLeft, yTop+CELL_SIZE)==BOARD_COLOR &&
        getpixel(xLeft-CELL_SIZE*2, yTop+CELL_SIZE)==BOARD_COLOR &&
        getpixel(xLeft-CELL_SIZE*2, yTop+CELL_SIZE*2)==BOARD_COLOR
      )
        freeRoute = 1;
    break;
}
return freeRoute;
}

int checkRotateLRRoute(int orientation, int xLeft, int yTop){
int freeRoute = 0;
switch(orientation){
case LEFT:
    xLeft+=CELL_SIZE/2;
    yTop+=CELL_SIZE/2;
    if (getpixel(xLeft,yTop) == BOARD_COLOR &&
        getpixel(xLeft, yTop+CELL_SIZE) == BOARD_COLOR &&
        getpixel(xLeft+CELL_SIZE*2, yTop) == BOARD_COLOR &&
        getpixel(xLeft+CELL_SIZE*2, yTop+CELL_SIZE) == BOARD_COLOR
       )
        freeRoute = 1;
    break;

case UP:
    xLeft+=CELL_SIZE*1.5;
    yTop+=CELL_SIZE/2;
    if (getpixel(xLeft, yTop) == BOARD_COLOR &&
        getpixel(xLeft+CELL_SIZE, yTop) == BOARD_COLOR &&
        getpixel(xLeft, yTop+CELL_SIZE*2) == BOARD_COLOR &&
        getpixel(xLeft+CELL_SIZE, yTop+CELL_SIZE*2) == BOARD_COLOR
       )
        freeRoute = 1;
    break;
case RIGHT:
    xLeft+=CELL_SIZE*1.5;
    yTop+=CELL_SIZE*1.5;
    if (getpixel(xLeft, yTop) == BOARD_COLOR &&
        getpixel(xLeft, yTop+CELL_SIZE) == BOARD_COLOR &&
        getpixel(xLeft-CELL_SIZE*2, yTop) == BOARD_COLOR &&
        getpixel(xLeft-CELL_SIZE*2, yTop+CELL_SIZE) == BOARD_COLOR
        )
        freeRoute = 1;
    break;
case DOWN:
    xLeft+=CELL_SIZE/2;
    yTop-=CELL_SIZE/2;
    if (getpixel(xLeft, yTop) == BOARD_COLOR &&
        getpixel(xLeft+CELL_SIZE, yTop) == BOARD_COLOR &&
        getpixel(xLeft, yTop+CELL_SIZE*2) == BOARD_COLOR &&
        getpixel(xLeft+CELL_SIZE, yTop+CELL_SIZE*2) == BOARD_COLOR
       )
        freeRoute = 1;
    break;
}
return freeRoute;
}

// Invoke the appropriate route checking function for rotation depending on block Id
int rotateRouteFree(int blockId, int orientation, int xLeft, int yTop)
   {   int freeRoute;
       switch(blockId) {
      case T_BLOCK  : freeRoute = checkRotateTBlockRoute(orientation, xLeft, yTop); break;
      case L_BLOCK  : freeRoute = checkRotateLRoute(orientation, xLeft, yTop); break;
      case LR_BLOCK : freeRoute = checkRotateLRRoute(orientation, xLeft, yTop); break;
      case BOX_BLOCK: break;
      case BAR_BLOCK: freeRoute = checkRotateBarRoute(orientation, xLeft, yTop) ;break;
       }
       return freeRoute;
  }

// Rotate the Bar block
void rotateBarBlock(int & orientation, int & xLeft, int & yTop, int fillingColor)
 {
   // Erase the bar at current position
   drawBarBlock(xLeft, yTop, orientation, BKGRD_COLOR);
   // Now compute the new location
   switch (orientation) {
     case HORIZONTAL:
       orientation = VERTICAL;
       xLeft = xLeft + CELL_SIZE;
       yTop  = yTop  - CELL_SIZE;
       break;

     case VERTICAL:
       orientation = HORIZONTAL;
       xLeft = xLeft - CELL_SIZE;
       yTop  = yTop  + CELL_SIZE;
       break;
   }
   // Now redraw the bar at the new position
   drawBarBlock(xLeft, yTop, orientation, fillingColor);
 }

void rotateTBlock(int & orientation, int & xLeft, int & yTop, int fillingColor)
{
       drawTBlock(xLeft, yTop, orientation, BKGRD_COLOR);
       switch(orientation){
       case LEFT:
        orientation = UP;
        break;
       case UP:
        orientation = RIGHT;
        yTop -= CELL_SIZE;
        xLeft += CELL_SIZE;
        break;
       case RIGHT:
        orientation = DOWN;
        yTop += CELL_SIZE;
        xLeft -= CELL_SIZE;
        break;
       case DOWN:
        orientation = LEFT;
        yTop -= CELL_SIZE;
       }
       drawTBlock(xLeft, yTop, orientation, fillingColor);
}

void rotateLBlock(int & orientation, int & xLeft, int & yTop, int fillingColor){
    drawLBlock(xLeft, yTop, orientation, BKGRD_COLOR);
    switch(orientation){
    case DOWN:
        orientation = LEFT;
        yTop-=CELL_SIZE;
        break;
    case LEFT:
        orientation = UP;
        yTop-=CELL_SIZE;
        break;
    case UP:
        orientation = RIGHT;
        xLeft+=CELL_SIZE;
        break;
    case RIGHT:
        orientation = DOWN;
        xLeft-=CELL_SIZE;
        break;
    }
    drawLBlock(xLeft, yTop, orientation, fillingColor);

}

void rotateLRBlock (int & orientation, int & xLeft, int & yTop, int fillingColor){
drawLRBlock(xLeft, yTop, orientation, BKGRD_COLOR);
switch (orientation){
case LEFT:
    orientation = UP;
    yTop-=CELL_SIZE;
    break;
case UP:
    orientation = RIGHT;
    xLeft+=CELL_SIZE;
    yTop-=CELL_SIZE;
    break;
case RIGHT:
    orientation = DOWN;
    xLeft-=CELL_SIZE;
    break;
case DOWN:
    orientation = LEFT;
    yTop-=CELL_SIZE;
    break;
}
drawLRBlock(xLeft, yTop, orientation, fillingColor);
}

// Invokes the appropriate rotating function depending on the block Id
void rotateBlock(int blockId, int & orientation, int & xLeft, int & yTop, int fillingColor)
  {
       switch(blockId) {
      case T_BLOCK  : rotateTBlock(orientation, xLeft, yTop, fillingColor) ;break;
      case L_BLOCK  : rotateLBlock(orientation, xLeft, yTop, fillingColor) ;break;
      case LR_BLOCK : rotateLRBlock(orientation, xLeft, yTop, fillingColor) ;break;
      case BOX_BLOCK: break;
      case BAR_BLOCK: rotateBarBlock(orientation, xLeft, yTop, fillingColor) ;break;
       }
  }

// Invokes the appropriate function depending on the arrow key pressed
void handleUserInput(int blockId, int & orientation,
				int & xLeft, int & yTop, int fillingColor, int key)
 {
  switch(key) {
     case LEFTARROW:
	  if (translateRouteFree(blockId,orientation, xLeft, yTop, LEFT))
	       translateBlock(blockId, orientation, xLeft, yTop, fillingColor, LEFT); break;
     case RIGHTARROW:
	  if (translateRouteFree(blockId,orientation, xLeft, yTop, RIGHT))
	       translateBlock(blockId, orientation, xLeft, yTop, fillingColor, RIGHT); break;
     case UPARROW:
	  if (rotateRouteFree(blockId, orientation, xLeft, yTop))
	  rotateBlock(blockId, orientation, xLeft, yTop, fillingColor); break;
     case DOWNARROW: delay (5);// Do you see any need for the DOWN Arrow key?
	  displayInfo((char*)"down arrow key pressed...");
	  break;
      }
 }

// checks whether or not game is over
int gameOver()
      {      int xLeft, yTop, maxNbCells, gOver;
	  // check if the top middle two/four cells are not covered
	  yTop  = TOPCORNER + CELL_SIZE /2;
	  xLeft = LEFTCORNER + 4*CELL_SIZE + CELL_SIZE/2;
	  maxNbCells = 2;  // or 4
	  gOver = 0;   // game is not over
	  while ( maxNbCells >= 1 && !gOver)
	   if (getpixel(xLeft, yTop) == BOARD_COLOR ){
	       xLeft = xLeft + CELL_SIZE;
	       maxNbCells--;
	   } else  gOver = 1; // game is over
	  return gOver;
      }

// checks confirmation of ESCAPE
int escapeConfirmed()
  {    char ans;
       displayInfo((char*)"Are you sure you want to Exit [Y/N] ?>");
       do
	 ans=toupper(char(getch()));
       while (ans != 'Y' && ans != 'N');
       if(ans == 'Y') return 1;
       else  return 0;
  }


void pullDown(int x, int y){
for(int i=1; i<=10; i++){
    setfillstyle(SOLID_FILL, getpixel(x+(0.5*CELL_SIZE), y-(0.5*CELL_SIZE)));
    bar(x,y,x+CELL_SIZE,y+CELL_SIZE);
    x+=CELL_SIZE;

}
}

int checkRow(double x, double y){
int chk = 1;
for(int i = 1; i<=10; i++){

    if(getpixel(x,y)==BOARD_COLOR)
        chk=0;
    x+=CELL_SIZE;
}
return chk;
}

int FullRowNumber(int x,int y){
    int cnt = 0;
for(int i = 0; i<15; i++){
    if(checkRow(x,y))
        cnt++;
y-=CELL_SIZE;
}
return cnt;
}

void deleteRow(int &scoreIncrease){
scoreIncrease = 0;
int ptx = LEFTCORNER+CELL_SIZE;
int pty = TOPCORNER + (14*CELL_SIZE);
int centerx = ptx+(0.5*CELL_SIZE);
int centery = pty+(0.5*CELL_SIZE);
int cnt = FullRowNumber(centerx, centery);
scoreIncrease = cnt;
int tpty = pty;
int tcentery = centery;
int j = 0;

while(cnt>0){
    for (j = 0; j<15; j++){ //to know which row
        if (checkRow(centerx,centery)){//check every row
            for (int i = 0; i <(15-j); i++){//not to pass the top limit
                    pullDown(ptx, pty-(j*CELL_SIZE));
                    pty-=CELL_SIZE;//iterate up
                }
        pty=tpty;//to redo
        }
        centery-=CELL_SIZE;
    }
    centery=tcentery;
    cnt--;
}
fillGrid();
}

// falls a block until it touches "ground"
int freeFall(int blockId, int orientation, int & xLeft, int & yTop, int fillingColor)
{
    int LEVEL = LEVEL1_SPEED;
     int fallBlocked = 0;
     if (translateRouteFree(blockId, orientation, xLeft, yTop, DOWN)) {
	translateBlock(blockId, orientation, xLeft, yTop, fillingColor, DOWN);
	delay(LEVEL); //Levels can be introduced
     } else fallBlocked = 1;
    return fallBlocked;
}

// Controls the overall logic of the game
void playGame()
  {
int currentBlock, currentOrientation, key, score = 0, level = 1;
bool oneTime = TRUE;
int xLeftCurrent, yTopCurrent, fillingColor, fallBlocked;
do {
  displayInfo((char*)"press ESC to abort the game");
  // clearKeyBoard(); // clears any key pressed
  generateNewBlock(&currentBlock, &currentOrientation, &xLeftCurrent,
	&yTopCurrent, &fillingColor);
  do {// loop as long as the current block is falling down
      int scoreIncrease;
   do
    fallBlocked = freeFall(currentBlock, currentOrientation, xLeftCurrent, yTopCurrent, fillingColor);
   while (!kbhit() && !fallBlocked);
   if (!fallBlocked) { // ie. key is pressed
    key=getch();
    switch(key) {
      case ESC:   if (!escapeConfirmed()) key = 1; break;
      case SPACE: displayInfo((char*)"space key pressed..."); break;
      case '\0' : { // Key is not int the 256 ASCII table
      key = getch();
      handleUserInput(currentBlock, currentOrientation, xLeftCurrent, yTopCurrent, fillingColor, key);
     }
   }
  }
  else if(fallBlocked)
      displayInfo((char*)"Touched Ground!!!");
      deleteRow(scoreIncrease);
      score+=scoreIncrease*10;
      if (score<50) level;
      else if (score<100) level+1;
      else level+2;
      delay(1000);
      key=0;
    }
  while (key != ESC && !fallBlocked);
 }
 while (key != ESC && !gameOver());
}

// Launches the game
int main() {
    int key;
    initGraphEngine();
    do {
     drawBoard();
     // clearKeyBoard(); // clears any previously pressed key strokes
     clearDisplayArea();
     displayInfo((char*)"press ENTER key to play or ESC to Exit");
     key=getch();
     switch(key) {
       case ESC:
	  if (!escapeConfirmed()) key = 1; // to erase ESCAPE
	  break;
       case ENTER:
	  playGame();
	  displayInfo((char*)"Game Over!!! Press any key ---> ");
	  getch();
	  break;
     } // switch
    } while (key != ESC); // this is to exit from the program
    displayInfo ((char*)"Come Again ... ");
    delay(1000);

    return 0;
}
