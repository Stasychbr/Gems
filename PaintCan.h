#pragma once
#include "Bonus.h"

class PaintCan : public Bonus {
private:
    Gem* chooseVictim(Gem* initiator);
public:
    PaintCan(int posX, int posY, int size, QGraphicsItem* parent);
    ~PaintCan();
    virtual void bonusAction();
};


