#pragma once

#include "Character.h"

class Player : public Character {
public:
    Player(string role);
    void useSkill(Character& target);
    void skillMenu(Character& target);

    string role;
    int manaRegenCooldown = 0;    // �^�]�N�o�^�X
   
};  