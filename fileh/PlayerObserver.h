#ifndef PLAYER_OBSERVER_H
#define PLAYER_OBSERVER_H
#include <vector>
#include "Point.h"
#include "Road.h"


class PlayerObserver {
private:
    std::vector <Road*> road;
public:
    PlayerObserver(): road({}) {};
    PlayerObserver(const std::vector<Road*> &road): road(road) {};
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