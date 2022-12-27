#ifndef PLAYER_MEDIATOR_H
#define PLAYER_MEDIATOR_H

#include <vector>
#include "Mediator.h"
#include "Point.h"
#include "Road.h"
#include "Player.h"

class PlayerMediator: public Mediator {
private:
    Road* lastPavement;
    std::vector <Road*> road;
    Player* player;
public:
    PlayerMediator(): road({}), player(nullptr) {};
    PlayerMediator(const std::vector<Road*> &road): road(road), player(nullptr) {};
    PlayerMediator(Player* player): road({}), player(player) {};
    PlayerMediator(const PlayerMediator &other): road(other.road), player(other.player) {};
    ~PlayerMediator() {
        /*while(road.size()) {
            Road* back=road.back();
            road.pop_back();
            back->~Road();
        }

        player->~Player();*/
    }

    void addRoad(Road* src) {
        this->road.push_back(src);
    }

    void addRoad(const vector <Road> &lstRoad) {
        Road *ptr=nullptr;
        for(auto &i: lstRoad) {
            ptr=const_cast<Road*>(&i);
            this->addRoad(ptr);
        }

        ptr=nullptr;
    }

    void updateLastPavement(int pos) {
        //cout << "Update pavement " << pos << '\n';
        this->lastPavement = this->road[pos];
    }

    void returnLastPos() {
        auto pos = this->lastPavement->getRect().getPosition();
        player->setPos(pos.x + SCREEN_WIDTH / 2, pos.y + player->getSprite().getSize().y);
    }
};
#endif