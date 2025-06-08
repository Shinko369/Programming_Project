#pragma once
#include "Character.h"

class Monster : public Character {
public:
    Monster(string name, int hp, int mp, int atk, int def);
};
