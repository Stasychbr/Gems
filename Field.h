#pragma once

#include <vector>
#include <array>
#include <memory>
#include "Gem.h"

class Field: public QGraphicsItem {
private:
    static const int _rows = 10;
    static const int _columns = 10;
    static const int _seqLen = 3;
    static const int _bonusChance = 10; // chance = 1/n
    static const int _bonusNum = 2;

    std::vector<std::vector<std::shared_ptr<Gem>>> _gems;
    QRectF _area;

    std::shared_ptr<Gem> _selectedGem = NULL;
    std::vector<std::shared_ptr<Gem>> _toDestroy;
    std::vector<std::shared_ptr<Gem>> _checkQuery;
    std::vector<std::shared_ptr<Gem>> _destroyQuery;
    std::array <int, _columns> _shifted;

    enum class LastCheckedGem {
        NO_CHECK,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    std::shared_ptr<Gem> generateGem(int row, int column, int size);

    void SwapGems(int row, int col);
    void CheckSequence(int i, int j, LastCheckedGem destination, QColor const& color);
    void CheckGem(int row, int col);
    void DestroySequence();
    void CheckAbove();
    void CheckWholeField();

    void execCheckQuery();
    void execDestroyQuery();
public:
    Field(QRectF& area);
    ~Field();
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    int rows();
    int columns();
    void CheckLater(std::shared_ptr<Gem> gem);
    void DestroyLater(std::shared_ptr<Gem> gem);
    void SelectGem(int row, int col);
    std::shared_ptr<Gem> gemAt(int row, int column);
};

