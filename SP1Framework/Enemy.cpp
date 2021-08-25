#include "Enemy.h"
Enemy::Enemy():luck(10)
{
	health = 20;
	damage = 20;
	status = true;
}

Enemy::Enemy(string enemyname, double health, double damage, double luck, bool isAlive)
{
	
	this->name = enemyname;
	this->health = health;
	this->damage = damage;
	this->luck = luck;
	this->status = isAlive;
}

string Enemy::getName()
{
	return name;
}

double Enemy::getHealth()
{
	return health;
}

double Enemy::getDamage()
{
	return damage;
}

bool Enemy::getStatus()
{
	return status;
}
double Enemy::getLuck()
{
	return luck;
}


Enemy::~Enemy()
{
}