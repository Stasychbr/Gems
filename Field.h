#pragma once

#include <vector>
#include <array>
#include "Gem.h"

class Field: public QGraphicsItem {
private:
    static const int _rows = 10;
    static const int _columns = 10;
    static const int _seqLen = 3;

    std::vector<std::vector<Gem*>> _gems;
    QRectF _area;

    Gem* _selectedGem = NULL;
    std::vector<Gem*> _toDestroy;
    std::array <int, _columns> _shifted;
    enum class LastCheckedGem {
        NO_CHECK,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    void SwapGems(int row, int col);
    void CheckSequence(int i, int j, LastCheckedGem destination, QColor const& color);
    void DestroySequence();
    void CheckAbove();

    void updateGems();
public:
    Field(QRectF& area);
    ~Field();
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    int rows();
    int columns();
    void SelectGem(int row, int col);
    Gem* gemAt(int row, int column);
};

