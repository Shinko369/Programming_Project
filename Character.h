#pragma once
#include <string>
#include <iostream>

using namespace std;

class Character {
protected:
    string name;
    int hp;
    int maxHp;
    int mp;
    int maxMp;
    int attackPower;
    int defense;
public:
    int getDefense() const { return defense; }
    Character(string n, int h, int m, int atk, int def);
    virtual ~Character() {}
    virtual void attack(Character& target);
    virtual void takeDamage(int dmg);
    bool isAlive() const;
    string getName() const;
    int getHP() const;
    int getMP() const;
    int getMaxHp() const;
    int getMaxMp() const;
    void heal(int amount);
};
