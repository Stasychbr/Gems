#include "PaintCan.h"
#include "Field.h"
#include <random>
#include <QRandomGenerator>


Gem* PaintCan::chooseVictim(Gem* initiator) {
    std::uniform_int_distribution<int> distRows(0, Gem::_field->rows() - 1);
    std::uniform_int_distribution<int> distColumns(0, Gem::_field->columns() - 1);
    int victimRow, victimColumn;
    do {
        victimRow = distRows(*QRandomGenerator::global());
        victimColumn = distColumns(*QRandomGenerator::global());
    } while (abs(victimRow - initiator->row()) <= 1 && abs(victimColumn - initiator->column()) <= 1);
    return Gem::_field->gemAt(victimRow, victimColumn);
}

PaintCan::PaintCan(int posX, int posY, int size, QGraphicsItem* parent) : Bonus(posX, posY, size, parent) {
}

PaintCan::~PaintCan() {
    bonusAction();
}

void PaintCan::bonusAction() {
    Gem* mainTarget = target();
    Gem* victim1 = chooseVictim(mainTarget);
    Gem* victim2 = chooseVictim(mainTarget);
    mainTarget->changeColor(color());
    victim1->changeColor(color());
    victim2->changeColor(color());
}


