#ifndef PLAYER_OBSERVER_H
#define PLAYER_OBSERVER_H
#include "Road.h"

class PlayerObserver {
private:
    vector <Road*> road;
public:
    PlayerObserver(): road({}) {};
    PlayerObserver(const vector<Road*> &road): road(road) {};
    PlayerObserver(const PlayerObserver &other): road(other.road) {};
    ~PlayerObserver() {
        while(road.size()) {
            Road* back=road.back();
            road.pop_back();
            back->~Road();
        }
    }
    void notify(Point &curPos);
};
#endif