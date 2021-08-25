#include "gameItem.h"
gameItem::gameItem() :attack(0), hp(0), luck(0), m_iActive(true)
{
	m_ItemLocation.X = 0;
	m_ItemLocation.Y = 0;

}

gameItem::gameItem(string Name, int addatk, int addl, int addhealth, int x, int y, bool Active)
{
	m_ItemLocation.X = x;
	m_ItemLocation.Y = y;
	this->name = Name;
	this->attack = addatk;
	this->luck = addl;
	this->hp = addhealth;
	this->m_iActive = Active;
	

}

gameItem::~gameItem()
{
}

void gameItem::setItemname(std::string itemname)
{
	name = itemname;
}

std::string gameItem::getItemname()
{
	return name;
}

double gameItem::getAA()
{
	return attack;
}

double gameItem::getAL()
{
	return luck;
}

double gameItem::getHP()
{
	return hp;
}

void gameItem::setAA(double addatk)
{
	attack = addatk;

}

void gameItem::setAL(double addl)
{
	luck = addl;
}

void gameItem::setHP(double addhealth)
{
	hp = addhealth;
}

int gameItem::getX()
{
	return m_ItemLocation.X;
}

int gameItem::getY()
{
	return m_ItemLocation.Y;
}

bool gameItem::getActivity()
{
	return m_iActive;
}

void gameItem::setActivity(bool active)
{
	this->m_iActive = active;
}

	


