#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>
#include "Hero.h"
#include "SpellResult.h"
#include "Eidos.h"

int main() {
	Hero* Eid = new Eidos();
	Hero* Eid2 = new Eidos();
	/*Eid->activeAbility(Eid2);
	std::this_thread::sleep_for(std::chrono::milliseconds(4500));
	Eid->activeAbility(Eid2);*/

	//std::thread t(&Hero::passiveAbility, Eid); //видимо из-за того, что моя пассивка не совсем обычная - ошибка

	for (;;)
	{
		char c = _getch();

		if (c == 'q')
			Eid->activeAbility(Eid2);
	}
}