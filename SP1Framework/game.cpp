// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

double  g_dElapsedTime;
double  g_dDeltaTime;
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;

// Game specific variables here
SGameChar   g_sChar;
endDoor g_endDoor;
EGAMESTATES g_eGameState = S_SPLASHSCREEN; // initial state

// Console object
Console g_Console(80, 25, "SP1 Framework");

char map[300][300];

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;    

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
    /*
    if (Map2 == true)
    {
        g_sChar.m_cLocation.X = 0;
        g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
    }
    */
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

    // remember to set your keyboard handler, so that your functions can be notified of input events
    g_Console.setKeyboardHandler(keyboardHandler);
    g_Console.setMouseHandler(mouseHandler);

    g_endDoor.location.X = 12;
    g_endDoor.location.Y = 12;
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Get all the console input events
//            This function sets up the keyboard and mouse input from the console.
//            We will need to reset all the keyboard status, because no events will be sent if no keys are pressed.
//
//            Remember to set the handlers for keyboard and mouse events.
//            The function prototype of the handler is a function that takes in a const reference to the event struct
//            and returns nothing. 
//            void pfKeyboardHandler(const KEY_EVENT_RECORD&);
//            void pfMouseHandlerconst MOUSE_EVENT_RECORD&);
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{
    // resets all the keyboard events
    memset(g_skKeyEvent, 0, K_COUNT * sizeof(*g_skKeyEvent));
    // then call the console to detect input from user
    g_Console.readConsoleInput();    
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the keyboard input. Whenever there is a keyboard event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            The KEY_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any keyboard event in the Splashscreen state
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent - reference to a key event struct
// Output   : void
//--------------------------------------------------------------
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent)
{    
    /*
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: // don't handle anything for the splash screen
        break;
    case S_GAME: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
        break;
    }
    */
    gameplayKBHandler(keyboardEvent);
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the mouse input. Whenever there is a mouse event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            For the mouse event, if the mouse is not moved, no event will be sent, hence you should not reset the mouse status.
//            However, if the mouse goes out of the window, you would not be able to know either. 
//
//            The MOUSE_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any mouse event in the Splashscreen state
//            
// Input    : const MOUSE_EVENT_RECORD& mouseEvent - reference to a mouse event struct
// Output   : void
//--------------------------------------------------------------
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{    
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: // don't handle anything for the splash screen
        break;
    case S_GAME: gameplayMouseHandler(mouseEvent); // handle gameplay mouse event
        break;
    }
}

//--------------------------------------------------------------
// Purpose  : This is the keyboard handler in the game state. Whenever there is a keyboard event in the game state, this function will be called.
//            
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent)
{
    // here, we map the key to our enums
    EKEYS key = K_COUNT;
    switch (keyboardEvent.wVirtualKeyCode)
    {
    case VK_UP: key = K_UP; break;
    case VK_DOWN: key = K_DOWN; break;
    case VK_LEFT: key = K_LEFT; break; 
    case VK_RIGHT: key = K_RIGHT; break; 
    case VK_SPACE: key = K_SPACE; break;
    case VK_RETURN: key = K_ENTER; break;
    case VK_ESCAPE: key = K_ESCAPE; break; 
    }
    // a key pressed event would be one with bKeyDown == true
    // a key released event would be one with bKeyDown == false
    // if no key is pressed, no event would be fired.
    // so we are tracking if a key is either pressed, or released
    if (key != K_COUNT)
    {
        g_skKeyEvent[key].keyDown = keyboardEvent.bKeyDown;
        g_skKeyEvent[key].keyReleased = !keyboardEvent.bKeyDown;
    }    
}

//--------------------------------------------------------------
// Purpose  : This is the mouse handler in the game state. Whenever there is a mouse event in the game state, this function will be called.
//            
//            If mouse clicks are detected, the corresponding bit for that mouse button will be set.
//            mouse wheel, 
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{
    if (mouseEvent.dwEventFlags & MOUSE_MOVED) // update the mouse position if there are no events
    {
        g_mouseEvent.mousePosition = mouseEvent.dwMousePosition;
    }
    g_mouseEvent.buttonState = mouseEvent.dwButtonState;
    g_mouseEvent.eventFlags = mouseEvent.dwEventFlags;
}

void renderEndDoor()
{
    WORD colour = 0x1A;
    g_Console.writeToBuffer(g_endDoor.location, (char)1, colour);
}

/*void renderMap2()
{

}
*/

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        case S_GAME: updateGame(); // gameplay logic when we are in the game
            break;
    }
}


void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_skKeyEvent[K_ENTER].keyReleased)
        g_eGameState = S_GAME;
}

void updateGame()       // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void moveCharacter()
{    
    // Updating the location of the character based on the key release

    
    
    if (g_skKeyEvent[K_UP].keyDown && g_sChar.m_cLocation.Y > 0)
    {
        if (map[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != '#')
        {
            g_sChar.m_cLocation.Y--;
        }
    }
    if (g_skKeyEvent[K_LEFT].keyDown && g_sChar.m_cLocation.X > 0)
    {
        if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != '#')
        {
            g_sChar.m_cLocation.X--;
        }
    }
    if (g_skKeyEvent[K_DOWN].keyDown && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
    {
        if (map[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != '#')
        {
            g_sChar.m_cLocation.Y++;
        }
    }
    if (g_skKeyEvent[K_RIGHT].keyDown && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
    {
        if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != '#')
        {
            g_sChar.m_cLocation.X++;
        }
    }
    if (g_skKeyEvent[K_SPACE].keyReleased)
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;        
    }

   
}
void processUserInput()
{
    /*if (g_skKeyEvent[K_SPACE].keyReleased && g_sChar.m_cLocation.X == g_endDoor.location.X && g_sChar.m_cLocation.Y == g_endDoor.location.Y)
    {
        Map2 = true;
    }
    */
    // quits the game if player hits the escape key
    if (g_skKeyEvent[K_ESCAPE].keyReleased)
        g_bQuitGame = true;    
}

//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: renderSplashScreen();
        break;
    case S_GAME: renderGame();
        break;
    }
    renderFramerate();      // renders debug information, frame rate, elapsed time, etc
    renderInputEvents();    // renders status of input events
    renderToScreen();       // dump the contents of the buffer to the screen, one frame worth of game
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x1F);
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void renderSplashScreen()  // renders the splash screen
{
    std::fstream inFile;
    inFile.open("titlescreen.txt");
    if (inFile.fail())
    {
        std::cerr << "Error";
        exit(1);
    }
    std::string elem;
    char title[128][128];
    int y = 0;
    while (getline(inFile, elem)) //get file by string
    {
        for (unsigned i = 0; i < elem.length(); ++i)
        {
            title[y][i] = elem.at(i); //read each string character
     
        }
        y++;
    }
    for (int y = 0; y < 7; y++)
    {
        for (int x = 0; x < 128; x++)
        {
            if (title[y][x] == '|')
            {
                g_Console.writeToBuffer(x, y, '|',BACKGROUND_BLUE | FOREGROUND_RED);
            }
            if (title[y][x] == '_')
            {
                g_Console.writeToBuffer(x, y, '_', BACKGROUND_BLUE | FOREGROUND_RED);
            }
            if (title[y][x] == '/')
            {
                g_Console.writeToBuffer(x, y, '/', BACKGROUND_BLUE | FOREGROUND_RED);
            }
            if (title[y][x] == '.')
            {
                g_Console.writeToBuffer(x, y, '.', BACKGROUND_BLUE | FOREGROUND_RED);
            }
            if (title[y][x] == '>')
            {
                g_Console.writeToBuffer(x, y, '>', BACKGROUND_BLUE | FOREGROUND_RED);
            }
            if (title[y][x] == '(')
            {
                g_Console.writeToBuffer(x, y, '(', BACKGROUND_BLUE | FOREGROUND_RED);
            }
        }
    }
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 5;
    g_Console.writeToBuffer(c, "Start", 0x03);
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
    renderEndDoor();    // renders the door to next stage
}

void loadlvl1()
{
    std::fstream inFile;
    inFile.open("lvl1");

    //Error check
    if (inFile.fail())
    {
        std::cerr << "Error";
        exit(1);
    }

    std::string elem;
    // Init and store Map
    
    int x = 0;
    while (getline(inFile, elem)) //get file by string
    {
        for (unsigned i = 0; i < elem.length(); ++i)
        {
            map[x][i] = elem.at(i); //read each string character

        }
        x++;
    }
    for (int x = 0; x < 300; x++)
    {
        for (int y = 0; y < 300; y++)
        {
            if (map[x][y] == '.')
            {
                g_Console.writeToBuffer(y, x, ' ', BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else if (map[x][y] == '#')
            {
                g_Console.writeToBuffer(y, x , '#', 0 | 0);
            }
            else if (map[x][y] == '?')
            {
                g_Console.writeToBuffer(y, x, '?', 0 | 0);
            }
            else if (map[x][y] == '!')
            {
                g_Console.writeToBuffer(y, x, '!', FOREGROUND_RED | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
            }
            else if (map[x][y] == '+')
            {
                g_Console.writeToBuffer(y, x, '+', FOREGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
            }
        }
    }
}

void gameOver()
{
    clearScreen();
    
    
}

void loadlvl2()
{
    std::fstream inFile;
    inFile.open("lvl2");

    //Error check
    if (inFile.fail())
    {
        std::cerr << "Error";
        exit(1);
    }

    std::string elem;
    // Init and store Map
    int x = 0;
    while (getline(inFile, elem)) //get file by string
    {
        for (unsigned i = 0; i < elem.length(); ++i)
        {
            map[x][i] = elem.at(i); //read each string character

        }
        x++;

    }
    for (int x = 0; x < 300; x++)
    {
        for (int y = 0; y < 300; y++)
        {
            if (map[x][y] == '.')
            {
                g_Console.writeToBuffer(y, x, ' ', BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else if (map[x][y] == '#')
            {
                g_Console.writeToBuffer(y, x, '#', 0 | 0);
            }
            else if (map[x][y] == '?')
            {
                g_Console.writeToBuffer(y, x, '?', 0 | 0);
            }
            else if (map[x][y] == '!')
            {
                g_Console.writeToBuffer(y, x, '!', FOREGROUND_RED | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
            }
            else if (map[x][y] == '+')
            {
                g_Console.writeToBuffer(y, x, '+', FOREGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
            }
        }
    }
}

void renderMap()
{
    if (!Map2)
    {
        loadlvl1();
    }
    else if (Map2)
    {
        loadlvl2();
    }
}
            
        
        

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    /*if (Map2 = true)
    {
        g_sChar.m_cLocation.X = 0;
        g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
    }
    */
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor); 
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
}

// this is an example of how you would use the input events
void renderInputEvents()
{
    // keyboard events
    std::ostringstream ss;

    // mouse events    
    ss.str("");
    ss << "Mouse position (" << g_mouseEvent.mousePosition.X << ", " << g_mouseEvent.mousePosition.Y << ")";
    g_Console.writeToBuffer(g_mouseEvent.mousePosition, ss.str(), 0x59);
 
    
}



