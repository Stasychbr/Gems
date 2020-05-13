#pragma once
#include "Gem.h"

class Bonus: public Gem {
private:
    static const int _radius = 3;
    static const int _bonusAniLen = 150;
    QPropertyAnimation* _bonusAnim = NULL;
protected:
    std::shared_ptr<Gem> target();
public:
    Bonus(int posX, int posY, int size, QGraphicsItem* parent);
    ~Bonus();
    virtual void bonusAction() = 0;
};

