#pragma once
#include "Bonus.h"

class PaintCan : public Bonus {
private:
    std::shared_ptr<Gem> chooseVictim(std::shared_ptr<Gem> initiator);
public:
    PaintCan(int posX, int posY, int size, QGraphicsItem* parent);
    ~PaintCan();
    virtual void bonusAction();
    virtual void destroy();
};


