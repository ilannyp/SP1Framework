#ifndef _GAME_H
#define _GAME_H
#include <string>
using namespace std;
#include "gameItem.h"
#include "Framework\timer.h"

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;
extern bool story;
extern bool alive;


// struct to store keyboard events
// a small subset of KEY_EVENT_RECORD
struct SKeyEvent
{
    bool keyDown;
    bool keyReleased;
};

// struct to store mouse events
// a small subset of MOUSE_EVENT_RECORD
struct SMouseEvent
{
    COORD mousePosition;
    DWORD buttonState;
    DWORD eventFlags;
};

// Enumeration to store the control keys that your game will have
enum EKEYS
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_SPACE,
    K_ENTER,
    K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_SPLASHSCREEN,
    S_GAME,
    S_GAMEOVER,
    S_COUNT
};

enum MAPSTATE
{
    lvl1,
    lvl2
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
};
struct SGameDoor
{
    COORD m_dLocation;
};
<<<<<<< HEAD


=======
>>>>>>> 53777cfccc07e16c04a952134b36728822f68857
void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void updateGame();          // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void renderInputEvents();   // renders the status of input events
void renderItem(); // render gameItems


// keyboard and mouse input event managers
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent);  // define this function for the console to call when there are keyboard events
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent);      // define this function for the console to call when there are mouse events

void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent);   // handles keyboard events for gameplay 
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent); // handles mouse events for gameplay 

<<<<<<< HEAD
void renderDoor(int x, int y);
=======
>>>>>>> 53777cfccc07e16c04a952134b36728822f68857
void loadlvl1();
void lvl1TXT();
void lvl1TXTclear();
void loadlvl2();

void gameOver();
void triggerGameOver();
void selectQuit();
#endif // _GAME_H
