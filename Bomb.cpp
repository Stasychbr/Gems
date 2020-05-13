#include "Bomb.h"
#include "Field.h"
#include <random>
#include <QRandomGenerator>

void Bomb::chooseVictims() {
    std::uniform_int_distribution<int> distRows(0, Gem::_field->rows() - 1);
    std::uniform_int_distribution<int> distColumns(0, Gem::_field->columns() - 1);
    int victimRow, victimColumn;
    do {
        for (int i = 0; i < _explodeNum; i++) {
            _toExplode[i] = std::make_pair(distRows(*QRandomGenerator::global()), distColumns(*QRandomGenerator::global()));
        }
    } while (sameInArray());
}

bool Bomb::sameInArray() {
    for (int i = 0; i < _explodeNum; i++) {
        for (int j = i + 1; j < _explodeNum; j++) {
            if (_toExplode[i] == _toExplode[j]) {
                return true;
            }
        }
    }
    return false;
}

Bomb::Bomb(int posX, int posY, int size, QGraphicsItem* parent):Bonus(posX, posY, size, parent) {
}

Bomb::~Bomb() {
}

void Bomb::bonusAction() {
    _field->DestroyLater(target());
    chooseVictims();
    for (int i = 0; i < _explodeNum; i++) {
        _field->DestroyLater(_field->gemAt(_toExplode[i].first, _toExplode[i].second));
    }
}

void Bomb::destroy() {
    bonusAction();
}
