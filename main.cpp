#include "BattleSystem.h"

int main() {
    srand(static_cast<unsigned int>(time(0)));
    BattleSystem game;
    game.start();
    return 0;
}