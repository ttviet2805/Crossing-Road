#ifndef PLAYER_MEDIATOR_H
#define PLAYER_MEDIATOR_H

#include <vector>
#include "Mediator.h"
#include "Point.h"
#include "Road.h"
#include "Player.h"
#include "PlayerStatus.h"

class PlayerMediator: public Mediator {
private:
    Road* lastPavement;
    std::vector <Road*> road;
    Player* player;
    Status* status;
public:
    PlayerMediator(): road({}), player(nullptr), lastPavement(nullptr) {};
    PlayerMediator(const std::vector<Road*> &road): road(road), player(nullptr), lastPavement(nullptr) {};
    PlayerMediator(Player* player): road({}), player(player), lastPavement(nullptr) {};
    PlayerMediator(const PlayerMediator &other): road(other.road), player(other.player), lastPavement(nullptr) {};
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

    void addStatus(Status* src) {
        this->status = src;
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
        //cout << (this->lastPavement == nullptr) << '\n';
    }

    void changeSkin() {
        //cout << "Change skin\n";
        status->changeTexture(this->player->getStaticTexturePath());
    }

    void returnLastPos() {
        auto pos = this->lastPavement->getRect().getPosition();
        player->setPos(pos.x + SCREEN_WIDTH / 2.5, pos.y - player->getSprite().getSize().y / 5);
    }

    void updateLevelText(std::string src) {
        status->setLevelString(src);
    }

    void updateHeartText(std::string src) {
        status->setHeartString(src);
    }

    void updateSpeedText(std::string src) {
        status->setSpeedString(src);
    }

    void updateScoreText(std::string src) {
        status->setScoreString(src);
    }

    void addPlayer(Player* player) {
        this->player = player;
    }

    void clear() {
        this->road.clear();
    }
};
#endif