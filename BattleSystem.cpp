#include "BattleSystem.h"
#include "Character.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

BattleSystem::BattleSystem() {
    srand(time(0));
    cout << "��ܧA������G\n1. �M�h\n2. �}�b��\n3. �k�v\n";
    int choice;
    cin >> choice;
    if (choice == 1) player = new Player("Knight");
    else if (choice == 2) player = new Player("Archer");
    else player = new Player("Mage");

    initMonsters();
}

void BattleSystem::initMonsters() {
    monsters.push_back(new Monster("�v�ܩi", 50, 0, 10, 2));
    monsters.push_back(new Monster("�����L", 60, 0, 12, 4));
    monsters.push_back(new Monster("�u�\�L", 80, 5, 15, 3));
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
        monsters.erase(monsters.begin() + index);  // �����o����

        battle(monster);

        delete monster; // �԰���R��
        if (!player->isAlive()) {
            cout << "�A�Q���ѤF�I�C�������C\n";
            return;
        }
    }

    cout << "�A���ѤF�Ҧ��Ǫ��I�ӧQ�I\n";
}

void BattleSystem::battle(Monster* monster) {
    cout << "�J��Ǫ��G" << monster->getName() << "\n";
    while (player->isAlive() && monster->isAlive()) {
        cout << "\n" << player->getName() << " HP: " << player->getHP() << "/" << player->getMaxHp()
            << " MP: " << player->getMP()<<"/"<<player->getMaxMp() << " | "
            << monster->getName() << " HP: " << monster->getHP() << "\n";
        player->useSkill(*monster);
        if (monster->isAlive()) monster->attack(*player);
    }
}