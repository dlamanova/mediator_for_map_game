#include "../include/include.hpp"
#include "../include/mob.hpp"


void Mob::move(int x, int y, std::vector < std::vector<char>> map) {
    int d = abs(x - this->x) + abs(y - this->y);
    if (d > this->velocity) {
        cout << "error";
        exit(-1);
    }
    this->x = x;
    this->y = y;
    this->velocity -= d;
}

void Mob::attack(std::shared_ptr<Mob> enemy) {
    int d = abs(enemy->x - this->x) + abs(enemy->y - this->y);
    if (d > this->attackRange) {
        cout << "error";
        exit(-1);
    }
    this->velocity -= d;
    enemy->hitPoint -= this->getAttack(enemy->type);
}