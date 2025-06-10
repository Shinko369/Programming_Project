#include "Player.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Player::Player(string r) : Character("", 0, 0, 0, 0), role(r) {
    
    if (role == "Knight") {
        name = "騎士";
        hp = maxHp = 120;
        mp = maxMp = 10;
        attackPower = 15;
        defense = 10;
    }
    else if (role == "Archer") {
        name = "弓箭手";
        hp = maxHp = 90;
        mp = maxMp = 10;
        attackPower = 20;
        defense = 5;
    }
    else if (role == "Mage") {
        name = "法師";
        hp  = maxHp = 70;
        mp = maxMp = 30;
        attackPower = 10;
        defense = 3;
    }
}

void Player::useSkill(Character& target) {
    skillMenu(target);
    if (manaRegenCooldown > 0) --manaRegenCooldown;
}

void Player::skillMenu(Character& target) {
    if (role == "Knight") {
        cout << "1. 普通攻擊\n2. 盾擊（小傷害 + 暈眩）\n3. 蓄力斬(更多傷害) \n";
        int choice;
        cin >> choice;
        if (choice == 2) {
            cout << name << " 使用盾擊！\n";
            int dmg = 8;
            target.takeDamage(dmg);
            cout << "造成 " << dmg << " 傷害，敵人可能會被暈眩！\n";
        }
        if (choice == 3) {
            cout << name << " 使用蓄力斬！\n";
            int dmg = 10;
            target.takeDamage(dmg);
            cout << "造成 " << dmg << " 傷害\n";
        }
        else { 
            attack(target);
        }
    }
    else if (role == "Archer") {
        cout << "1. 普通攻擊\n2. 集中射擊（1.5倍傷害）\n3. 雙重射擊（攻擊兩次，每次減半）\n";
        int choice;
        cin >> choice;
        if (choice == 2) {
            int dmg = static_cast<int>(attackPower * 1.5) - target.getDefense();
            if (dmg < 1) dmg = 1;
            target.takeDamage(dmg);
            cout << name << " 使用集中射擊造成 " << dmg << " 傷害！\n";
        }
        else if (choice == 3) {
            cout << name << " 使用雙重射擊！\n";
            for (int i = 1; i <= 2; ++i) {
                int dmg = static_cast<int>(attackPower * 0.5) - target.getDefense();
                if (dmg < 1) dmg = 1;
                target.takeDamage(dmg);
                cout << "第 " << i << " 發箭造成 " << dmg << " 傷害！\n";
            }
        }
        else {
            attack(target);
        }
    }
    else if (role == "Mage") {
        cout << "1. 魔法彈（耗5MP）\n2. 火球術（耗10MP）\n3. 治癒術（耗8MP）\n4. 回魔術（加5MP）\n";
        int choice;
        cin >> choice;
        if (choice == 2 && mp >= 10) {
            mp -= 10;
            int dmg = 25 - target.getDefense();  // 改用 getDefense()
            if (dmg < 1) dmg = 1;
            target.takeDamage(dmg);
            cout << name << " 使用火球術造成 " << dmg << " 傷害！\n";
        }
        else if (choice == 3 && mp >= 8) {
            if (hp == maxHp) {
                cout << " 你的 HP 已經是滿的，無法治癒！\n";
                return;
            }
            mp -= 8;
            heal(20);
            cout << name << " 使用治癒術恢復 20 HP！\n";
        }
        else if (choice == 4) {
            if (mp >= maxMp) {
                cout << "MP已滿，無法回魔！\n";
            }
            else if (manaRegenCooldown > 0) {
                cout << "回魔術還在冷卻中，剩餘 " << manaRegenCooldown << " 回合！\n";
            }
            else {
                mp += 5;
                if (mp > maxMp) mp = maxMp; // 不超過上限
                manaRegenCooldown = 2; // 設定冷卻為 2 回合
                cout << name << " 使用回魔術，恢復 5 MP！\n";
            }
        }
        else {
            if (mp >= 5) {
                mp -= 5;
                int dmg = attackPower + 5 - target.getDefense();
                if (dmg < 1) dmg = 1;
                target.takeDamage(dmg);
                cout << name << " 施放「魔法彈」造成 " << dmg << " 點魔法傷害！（消耗 5 MP）\n";
            }
            else {
                cout << name << " MP 不足，改用物理攻擊！\n";
                attack(target);
            }
        }
    }
}
