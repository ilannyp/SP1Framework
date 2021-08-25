#pragma once
#include <string>
using namespace std;
class Entity
{
public:
	virtual double getHealth() = 0;
	virtual double getDamage() = 0;
	virtual bool getStatus() = 0;
	virtual string getName() = 0;
	virtual double getLuck() = 0;
};

