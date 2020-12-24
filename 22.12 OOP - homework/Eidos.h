#pragma once
//���� ������, ��������� ��� ���� �������� ���
//���������� ��� ��������� ����, ��� � ����� � �����
//��� ������ � �������� ������������� https://stackoverflow.com/questions/31255486/c-how-do-i-convert-a-stdchronotime-point-to-long-and-back
//�������� ����� ���� ������
#include <iostream>
#include <thread>
#include <ctime>
#include <chrono>
#include "SpellResult.h"
#include "Hero.h"
using namespace std;
using namespace std::chrono;

//template <class Clock, class Duration = typename Clock::duration> class time_point; //������ ��� � ����, ����� �������, �������� � ��� �����
//template<class Rep, class Period = std::ratio<1>> class duration;// ���� �����

class Eidos :
    public Hero
{
protected:
    long _duration_now; //����������� ��������� ��� � ��������� ������� ������� ��� �������� �����
    long _duration_cast;//�� �� �����, ��������������� ������ �����

public:
    Eidos() : Hero(75, 150) { //���������� ������� (27 - 29) ����� ��� ��������� ������ �����
        //��� ����� ��� � ��������� ������� ��������� ������� (����� ��), � ����� ��� ���������� ����
        auto cast = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()); //��������� ����� �������
        auto tmp_cast = cast.time_since_epoch();// ��������� � ����� ��� ��� ��������� ��� � ����� �� ������ ������� (�� ����� �����)
        _duration_cast = tmp_cast.count();//���������� ��������� � ����
    }

    virtual void getDamage(int damage) { this->_HP -= damage; }
    virtual void wasteMana(int quant) { this->_MP -= quant; }

    SpellResult activeAbility(Hero* Other) override { //ShadowKnife
        auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());//��� ��� � ������������
        auto tmp_now = now.time_since_epoch();
        _duration_now = tmp_now.count();

        if (_duration_now - _duration_cast < 4000) { // ��� � �������� ��, ��� ������� �� - 4 ������� (4000 �����������)
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
            std::this_thread::sleep_for(std::chrono::milliseconds(1500)); //����� � ��, ���������� 1 ���� � 1,5 �������
        }
    }
};

