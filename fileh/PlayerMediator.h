#ifndef PLAYER_MEDIATOR_H
#define PLAYER_MEDIATOR_H
#include <vector>
#include "Point.h"
#include "Road.h"
#include "Player.h"

class PlayerMediator {
private:
    std::vector <Road*> road;
    Player* player;
public:
    PlayerMediator(): road({}), player(nullptr) {};
    PlayerMediator(const std::vector<Road*> &road): road(road), player(nullptr) {};
    PlayerMediator(const PlayerMediator &other): road(other.road), player(other.player) {};
    ~PlayerMediator() {
        while(road.size()) {
            Road* back=road.back();
            road.pop_back();
            back->~Road();
        }

        player->~Player();
    }

    void addRoad(Road* src) {
        road.push_back(src);
    }

    void returnLastPos(float x, float y) {
        player->setPos(x, y);
    }
};
#endif