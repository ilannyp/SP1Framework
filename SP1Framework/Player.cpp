#include "Player.h"
Player::Player() :luck(10), guaranteedodge(true), deflect(true)
{
	health = 40;
	damage = 20;
	status = true;
}

Player::Player(string pname, double health, double damage, double luck, bool isAlive, bool gdodge, bool deflection)
{
	this->guaranteedodge = gdodge;
	this->name = pname;
	this->health = health;
	this->damage = damage;
	this->luck = luck;
	this->status = isAlive;
	this->deflect = deflection;
}

string Player::getName()
{
	return name;
}

double Player::getHealth()
{
	return health;
}

double Player::getDamage()
{
	return damage;
}

bool Player::getStatus()
{
	return status;
}

double Player::getLuck()
{
	return luck;
}
Player::~Player() {

}