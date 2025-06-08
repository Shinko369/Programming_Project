#include "Player.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Player::Player(string r) : Character("", 0, 0, 0, 0), role(r) {
    
    if (role == "Knight") {
        name = "�M�h";
        hp = maxHp = 120;
        mp = maxMp = 10;
        attackPower = 15;
        defense = 10;
    }
    else if (role == "Archer") {
        name = "�}�b��";
        hp = maxHp = 90;
        mp = maxMp = 10;
        attackPower = 20;
        defense = 5;
    }
    else if (role == "Mage") {
        name = "�k�v";
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
        cout << "1. ���q����\n2. �����]�p�ˮ` + �w�t�^\n3. �W�O��(��h�ˮ`) \n";
        int choice;
        cin >> choice;
        if (choice == 2) {
            cout << name << " �ϥά����I\n";
            int dmg = 8;
            target.takeDamage(dmg);
            cout << "�y�� " << dmg << " �ˮ`�A�ĤH�i��|�Q�w�t�I\n";
        }
        if (choice == 3) {
            cout << name << " �ϥλW�O�١I\n";
            int dmg = 10;
            target.takeDamage(dmg);
            cout << "�y�� " << dmg << " �ˮ`\n";
        }
        else { 
            attack(target);
        }
    }
    else if (role == "Archer") {
        cout << "1. ���q����\n2. �����g���]1.5���ˮ`�^\n3. �����g���]�����⦸�A�C����b�^\n";
        int choice;
        cin >> choice;
        if (choice == 2) {
            int dmg = static_cast<int>(attackPower * 1.5) - target.getDefense();
            if (dmg < 1) dmg = 1;
            target.takeDamage(dmg);
            cout << name << " �ϥζ����g���y�� " << dmg << " �ˮ`�I\n";
        }
        else if (choice == 3) {
            cout << name << " �ϥ������g���I\n";
            for (int i = 1; i <= 2; ++i) {
                int dmg = static_cast<int>(attackPower * 0.5) - target.getDefense();
                if (dmg < 1) dmg = 1;
                target.takeDamage(dmg);
                cout << "�� " << i << " �o�b�y�� " << dmg << " �ˮ`�I\n";
            }
        }
        else {
            attack(target);
        }
    }
    else if (role == "Mage") {
        cout << "1. �]�k�u�]��5MP�^\n2. ���y�N�]��10MP�^\n3. �v¡�N�]��8MP�^\n4. �^�]�N�]�[5MP�^\n";
        int choice;
        cin >> choice;
        if (choice == 2 && mp >= 10) {
            mp -= 10;
            int dmg = 25 - target.getDefense();  // ��� getDefense()
            if (dmg < 1) dmg = 1;
            target.takeDamage(dmg);
            cout << name << " �ϥΤ��y�N�y�� " << dmg << " �ˮ`�I\n";
        }
        else if (choice == 3 && mp >= 8) {
            if (hp == maxHp) {
                cout << " �A�� HP �w�g�O�����A�L�k�v¡�I\n";
                return;
            }
            mp -= 8;
            heal(20);
            cout << name << " �ϥΪv¡�N��_ 20 HP�I\n";
        }
        else if (choice == 4) {
            if (manaRegenCooldown > 0) {
                cout << "�^�]�N�٦b�N�o���A�Ѿl " << manaRegenCooldown << " �^�X�I\n";
            }
            else {
                mp += 5;
                if (mp > maxMp) mp = maxMp; // ���W�L�W��
                manaRegenCooldown = 2; // �]�w�N�o�� 2 �^�X
                cout << name << " �ϥΦ^�]�N�A��_ 5 MP�I\n";
            }
        }
        else {
            if (mp >= 5) {
                mp -= 5;
                int dmg = attackPower + 5 - target.getDefense();
                if (dmg < 1) dmg = 1;
                target.takeDamage(dmg);
                cout << name << " �I��u�]�k�u�v�y�� " << dmg << " �I�]�k�ˮ`�I�]���� 5 MP�^\n";
            }
            else {
                cout << name << " MP �����A��Ϊ��z�����I\n";
                attack(target);
            }
        }
    }
}