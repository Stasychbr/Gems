#include "Bonus.h"
#include "PaintCan.h"
#include "Field.h"
#include <random>
#include <QRandomGenerator>

Gem* Bonus::target() {
    std::uniform_int_distribution<int> distribution(-_radius, _radius);
    int targetRow, targetColumn;
    do {
        targetRow = (row() + distribution(*QRandomGenerator::global())) % _field->rows();
        if (targetRow < 0) {
            targetRow = 0;
        }
        targetColumn = (column() + distribution(*QRandomGenerator::global())) % _field->rows();
        if (targetColumn < 0) {
            targetColumn = 0;
        }
    } while (targetRow == row() && targetColumn == column());
    return _field->gemAt(targetRow, targetColumn);
}

Bonus::Bonus(int posX, int posY, int size, QGraphicsItem* parent) : Gem(posX, posY, size, parent) {
    _bonusAnim = new QPropertyAnimation(this, "rotation");
    _bonusAnim->setStartValue(0);
    _bonusAnim->setEndValue(0);
    _bonusAnim->setDuration(_bonusAniLen);
    _bonusAnim->setKeyValueAt(0.25, 5);
    _bonusAnim->setKeyValueAt(0.75, -5);
    _bonusAnim->setLoopCount(-1);
    _bonusAnim->start();
}

Bonus::~Bonus() {
    delete _bonusAnim;
}

//int Bonus::totalNumber() {
//    return _bonusNum;
//}

