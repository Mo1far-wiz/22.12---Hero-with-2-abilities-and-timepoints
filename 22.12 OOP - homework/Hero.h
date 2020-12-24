#pragma once
#include <iostream>
#include "SpellResult.h"

class Hero
{
protected:
	int _HP;
	int _MP;

public:
	Hero(int hp, int mp) : _HP(hp), _MP(mp) {}


	virtual SpellResult activeAbility(Hero* Other) = 0 {}
	virtual void passiveAbility(Hero* Other) = 0 {}
	virtual void getDamage(int damage) { _HP -= damage; }
	virtual void wasteMana(int quant) { _MP -= quant; }
};

