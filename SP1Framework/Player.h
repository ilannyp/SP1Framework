#pragma once
#include <string>
#include "Entity.h"
using namespace std;
class Player :
    public Entity
{
private:
	string name;
	double health, damage, luck;
	bool status, guaranteedodge, deflect;
public:
	Player();
	~Player();
	Player(string pname, double health, double damage, double luck, bool isAlive, bool gdodge, bool deflection);
	string getName();
	double getHealth();
	double getDamage();
	bool getStatus();
	double getLuck();
};

