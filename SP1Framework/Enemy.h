#pragma once
#include "Entity.h"
#include <string>
using namespace std;
class Enemy :
    public Entity
{

private:
	double health, damage, luck;
	bool status;
	string name;
public:
	Enemy();
	~Enemy();
	Enemy(string enemyname, double health, double damage, double luck, bool isAlive);
	string getName();
	double getHealth();
	double getDamage();
	bool getStatus();
	double getLuck();
};

