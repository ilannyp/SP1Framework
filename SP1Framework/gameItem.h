#pragma once
#include <string>
#include <Windows.h>

using namespace std;

class gameItem
    {
    private:
        string name;
        double  attack, luck, hp;
        COORD m_ItemLocation;
        bool  m_iActive;

    public:
        gameItem();
        gameItem(string Name, int addatk, int addl, int addhealth, int xpos, int ypos,bool Active);
        void setItemname(string itemname);
        string getItemname();
        double getAA();// getter for addattack item
        double getAL();// getter for addluck item
        double getHP();// getter for addhpitem
        void setAA(double addatk);// setter for addattack item
        void setAL(double addl);// setter for addluck item
        void setHP(double addhealth);// setter for addhp item
        int getX();
        int getY();
        bool getActivity();
        void setActivity(bool active);
        
        ~gameItem();

    };



