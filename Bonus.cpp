#include "Bonus.h"
#include "PaintCan.h"
#include <random>
#include <QRandomGenerator>

Gem* Bonus::target() {
    std::uniform_int_distribution<int> distribution(-_radius, _radius);
    int targetRow, targetColumn;
    do {
        targetRow = (_owner->row() + distribution(*QRandomGenerator::global())) % _field->rows();
        if (targetRow < 0) {
            targetRow = 0;
        }
        targetColumn = (_owner->column() + distribution(*QRandomGenerator::global())) % _field->rows();
        if (targetColumn < 0) {
            targetColumn = 0;
        }
    } while (targetRow == _owner->row() && targetColumn == _owner->column());
    return _field->gemAt(targetRow, targetColumn);
}

Bonus::Bonus(Field* field, Gem* owner){
    _field = field;
    _owner = owner;
}

int Bonus::totalNumber() {
    return _bonusNum;
}

/*std::shared_ptr<Bonus>*/ Bonus* Bonus::rollBonus(Field* field, Gem* owner) {
    //return std::shared_ptr<Bonus>(new PaintCan(field, owner));
    return NULL;//new PaintCan(field, owner);
}
