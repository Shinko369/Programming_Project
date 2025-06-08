#pragma once
#include "Player.h"
#include "Monster.h"
#include <vector>

class BattleSystem {
private:
    Player* player;
    vector<Monster*> monsters;
public:
    BattleSystem();
    ~BattleSystem();
    void start();
    void battle(Monster* monster);
    void initMonsters();
};
