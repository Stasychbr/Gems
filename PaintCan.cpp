//#include "PaintCan.h"
//#include <random>
//#include <QRandomGenerator>
//
//Gem* PaintCan::chooseVictim(Gem* initiator) {
//    std::uniform_int_distribution<int> distRows(0, _field->rows() - 1);
//    std::uniform_int_distribution<int> distColumns(0, _field->columns() - 1);
//    int victimRow, victimColumn;
//    do {
//        victimRow = distRows(*QRandomGenerator::global());
//        victimColumn = distColumns(*QRandomGenerator::global());
//    } while (abs(victimRow - initiator->row()) <= 1 && abs(victimColumn - initiator->column()) <= 1);
//    return _field->gemAt(victimRow, victimColumn);
//}
//
//PaintCan::PaintCan(Field* field, Gem* gem) : Bonus(field, gem) {
//}
//
//void PaintCan::effect() {
//    Gem* mainTarget = target();
//    Gem* victim1 = chooseVictim(mainTarget);
//    Gem* victim2 = chooseVictim(mainTarget);
//    mainTarget->changeColor(_gem->color());
//    victim1->changeColor(_gem->color());
//    victim2->changeColor(_gem->color());
//}
