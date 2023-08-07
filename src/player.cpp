#include "../include/mediator.hpp"
#include "../include/mob.hpp"
#include "../include/player.hpp"

void Player::reload() {
    for(auto& pair: this->mobs){
        pair.second->velocity = pair.second->maxVelocity;
    }
    if(buildedMob!= nullptr){
    if (buildedMob->buildTime > 0) {
        this->buildedMob->buildTime -= 1;
        if (this->buildedMob->buildTime == 0) {
            this->base->product = B;
            this->mobs.insert(std::make_pair(this->buildedMob->getID(), this->buildedMob));
        }
    }
    }
}

void Player::dig(std::vector<coordinates> mines) {
    for (auto& pair : this->mobs) {
        std::shared_ptr<Mob> mob = pair.second;
        if (mob->type != W) {
            continue;
        }
        for (auto& coord : mines) {
            if (mob->x == coord.x && mob->y == coord.y) {
                this->money += 50;
                continue;
            }
        }
    }
}

std::shared_ptr<Mob> Player::findPlayerMobOnCoordinates(int x, int y) {
    for (auto& pair : this->mobs) {
        std::shared_ptr<Mob> mob = pair.second;
        if (mob->x == x && mob->y == y) {
            return mob;
        }
    }
    Mob* emptyMob = new Mob();
    std::shared_ptr<Mob> emptyMobPtr(emptyMob);
    return emptyMobPtr;
};