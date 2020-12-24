#pragma once
//Всем привет, презентую вам свой чудесный код
//Коментирии для пояснение того, что и зачем я делал
//моя личная и огромная благодарность https://stackoverflow.com/questions/31255486/c-how-do-i-convert-a-stdchronotime-point-to-long-and-back
//осковные куски кода оттуда
#include <iostream>
#include <thread>
#include <ctime>
#include <chrono>
#include "SpellResult.h"
#include "Hero.h"
using namespace std;
using namespace std::chrono;

//template <class Clock, class Duration = typename Clock::duration> class time_point; //просто что б было, можно удалить, работает и без этого
//template<class Rep, class Period = std::ratio<1>> class duration;// тоже самое

class Eidos :
    public Hero
{
protected:
    long _duration_now; //специальная переменна что б сохранить знаение времени для проверки каста
    long _duration_cast;//то же самое, непосредственно момент каста

public:
    Eidos() : Hero(75, 150) { //дальнейшие строчки (27 - 29) нужны для коректной работы каста
        //нам нужно что б программа сначала проверяла кулдаун (далее кд), а потом при надобности ману
        auto cast = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()); //сохраняем поинт времени
        auto tmp_cast = cast.time_since_epoch();// насколько я понял тут оно переводит его в время от начала отсчета (по факту копию)
        _duration_cast = tmp_cast.count();//записываем цыферками в лонг
    }

    virtual void getDamage(int damage) { this->_HP -= damage; }
    virtual void wasteMana(int quant) { this->_MP -= quant; }

    SpellResult activeAbility(Hero* Other) override { //ShadowKnife
        auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());//все как в конструкторе
        auto tmp_now = now.time_since_epoch();
        _duration_now = tmp_now.count();

        if (_duration_now - _duration_cast < 4000) { // вот и проверка кд, для баланса кд - 4 секунды (4000 миллисекунд)
            std::cout << "Spell in cooldown" << std::endl;
            return SpellResult::Cooldown;
        }
        else if (this->_MP >= 30) {
            wasteMana(30);
            Other->getDamage(20);
            std::cout << "Shadow Knife was casted" << std::endl;
            auto cast = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
            auto tmp_cast = cast.time_since_epoch();
            _duration_cast = tmp_cast.count();
            return SpellResult::Casted;
        }
        else if (this->_MP < 30) {
            std::cout << "Lack of Mana" << std::endl;
            return SpellResult::NoMana;
        }
    }
    void passiveAbility(Hero* Other) override { //ManaSteal
        for (;;) {
            Other->wasteMana(1);
            this->_MP += 1;
            std::cout << "You steal 1 MP" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1500)); //месно е кд, высасывает 1 ману в 1,5 секунды
        }
    }
};

