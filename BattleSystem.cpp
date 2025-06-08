#include "BattleSystem.h"
#include "Character.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

BattleSystem::BattleSystem() {
    srand(time(0));
    cout << "選擇你的角色：\n1. 騎士\n2. 弓箭手\n3. 法師\n";
    int choice;
    cin >> choice;
    if (choice == 1) player = new Player("Knight");
    else if (choice == 2) player = new Player("Archer");
    else player = new Player("Mage");

    initMonsters();
}

void BattleSystem::initMonsters() {
    monsters.push_back(new Monster("史萊姆", 50, 0, 10, 2));
    monsters.push_back(new Monster("哥布林", 60, 0, 12, 4));
    monsters.push_back(new Monster("骷髏兵", 80, 5, 15, 3));
}

BattleSystem::~BattleSystem() {
    delete player;
    for (auto m : monsters) delete m;
    monsters.clear();
}

void BattleSystem::start() {
    int monsterCount = monsters.size();

    for (int i = 0; i < monsterCount; ++i) {
        int index = rand() % monsters.size();
        Monster* monster = monsters[index];
        monsters.erase(monsters.begin() + index);  // 移除這隻怪

        battle(monster);

        delete monster; // 戰鬥後刪除
        if (!player->isAlive()) {
            cout << "你被打敗了！遊戲結束。\n";
            return;
        }
    }

    cout << "你擊敗了所有怪物！勝利！\n";
}

void BattleSystem::battle(Monster* monster) {
    cout << "遇到怪物：" << monster->getName() << "\n";
    while (player->isAlive() && monster->isAlive()) {
        cout << "\n" << player->getName() << " HP: " << player->getHP() << "/" << player->getMaxHp()
            << " MP: " << player->getMP()<<"/"<<player->getMaxMp() << " | "
            << monster->getName() << " HP: " << monster->getHP() << "\n";
        player->useSkill(*monster);
        if (monster->isAlive()) monster->attack(*player);
    }
}