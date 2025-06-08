#include "Character.h"

Character::Character(string n, int h, int m, int atk, int def)
    : name(n), hp(h), maxHp(h), mp(m), maxMp(m), attackPower(atk), defense(def) {
}

void Character::attack(Character& target) {
    int damage = attackPower - target.defense;
    if (damage < 1) damage = 1;
    target.takeDamage(damage);
    cout << name << " 對 " << target.getName() << " 造成了 " << damage << " 點傷害！\n";
}

void Character::takeDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) hp = 0;
}

bool Character::isAlive() const {
    return hp > 0;
}

string Character::getName() const {
    return name;
}

int Character::getHP() const {
    return hp;
}

int Character::getMP() const {
    return mp;
}

int Character::getMaxHp() const {
    return maxHp;
}
int Character::getMaxMp() const {
    return maxMp;
}

void Character::heal(int amount) {
    hp += amount;
    if (hp > maxHp) hp = maxHp;
}