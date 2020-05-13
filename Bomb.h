#pragma once
#include "Bonus.h"
#include <array>
#include <utility>

class Bomb : public Bonus {
private:
    static const int _explodeNum = 4;
    void chooseVictims();
    std::array<std::pair<int, int>, _explodeNum> _toExplode;
    bool sameInArray();
public:
    Bomb(int posX, int posY, int size, QGraphicsItem* parent);
    ~Bomb();
    virtual void bonusAction();
    virtual void destroy();
};

