#pragma once
#include "Gem.h"
#include "Field.h"
#include <memory>

class Bonus {
private:
    static const int _radius = 3;
    static const int _bonusNum = 1;
protected:
    Field* _field = NULL;
    Gem* _owner = NULL;
    Gem* target();
public:
    Bonus(Field* field, Gem* gem);
    virtual void effect() = 0;
    static int totalNumber();
    static /*std::shared_ptr <Bonus>*/ Bonus* rollBonus(Field* field, Gem* owner);
};

