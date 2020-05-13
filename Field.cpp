#include "Field.h"
#include <cmath>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <array>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <random>
#include "PaintCan.h"

Field::Field(QRectF& area) {
    int size = (int)(fmin<double, double>(area.width(), area.height()) / fmax<int, int>(_rows, _columns));
    _gems.resize(_rows);
    _shifted.fill(-1);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            _gems[i].push_back(generateGem(i, j, size));
        }
    }
    _area = area;
}

Field::~Field() {
    /*for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            delete _gems[i][j];
        }
    }*/
}

QRectF Field::boundingRect() const {
    return _area;
}

void Field::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

int Field::rows() {
    return _rows;
}

int Field::columns() {
    return _columns;
}

std::shared_ptr<Gem> Field::gemAt(int row, int column) {
    if (row < 0 || row >= _rows || column < 0 || column >= _columns) {
        return NULL;
    }
    return _gems[row][column];
}

void Field::SelectGem(int row, int col) {
    if (!_selectedGem) {
        _selectedGem = _gems[row][col];
        _selectedGem->select();
    }
    else {
        _selectedGem->unselect();
        int tmpRow = _selectedGem->row(); //!
        int tmpCol = _selectedGem->column(); //!
        if (abs(tmpRow - row) == 1 && tmpCol == col || abs(tmpCol - col) == 1 && tmpRow == row) {
            SwapGems(row, col);
            CheckSequence(row, col, LastCheckedGem::NO_CHECK, _gems[row][col]->color());
            DestroySequence();
            CheckAbove();
            CheckSequence(tmpRow, tmpCol, LastCheckedGem::NO_CHECK, _gems[tmpRow][tmpCol]->color());
            DestroySequence();
            CheckAbove();
        }
        _selectedGem = NULL;
        //updateGems();
    }
}

std::shared_ptr<Gem> Field::generateGem(int row, int column, int size) {
    std::uniform_int_distribution<int> distribution(0, _bonusChance);
    if (distribution(*QRandomGenerator::global()) == 0) {
        std::uniform_int_distribution<int> bonusChoice(1, _bonusNum);
        switch (bonusChoice(*QRandomGenerator::global())) {
        case 1:
            return std::shared_ptr<Gem>((Gem*)new PaintCan(column, row, size, this));
        default:
            return std::shared_ptr<Gem> (new Gem(column, row, size, this));
        }
    }
    else {
        return std::shared_ptr<Gem> (new Gem(column, row, size, this));
    }
}

void Field::SwapGems(int row, int col) {
    _gems[_selectedGem->row()][_selectedGem->column()] = _gems[row][col];
    _gems[row][col]->changeRow(_selectedGem->row(), Gem::AnimationType::SWAP);
    _gems[row][col]->changeColumn(_selectedGem->column(), Gem::AnimationType::SWAP);

    _gems[row][col] = _selectedGem;
    _selectedGem->changeRow(row, Gem::AnimationType::SWAP);
    _selectedGem->changeColumn(col, Gem::AnimationType::SWAP);
}

void Field::CheckSequence(int i, int j, LastCheckedGem destination, QColor const& color) {
    if (i < 0 || i >= _rows || j < 0 || j >= _columns) {
        return;
    }
    if (color == _gems[i][j]->color()) {
        _toDestroy.push_back(_gems[i][j]);
        if (destination != LastCheckedGem::LEFT) {
            CheckSequence(i - 1, j, LastCheckedGem::RIGHT, color);
        }
        if (destination != LastCheckedGem::RIGHT) {
            CheckSequence(i + 1, j, LastCheckedGem::LEFT, color);
        }
        if (destination != LastCheckedGem::DOWN) {
            CheckSequence(i, j - 1, LastCheckedGem::UP, color);
        }
        if (destination != LastCheckedGem::UP) {
            CheckSequence(i, j + 1, LastCheckedGem::DOWN, color);
        }
    }
}

void Field::DestroySequence() {
    if (_toDestroy.size() >= _seqLen) {
        for (auto gem: _toDestroy) {
            _shifted[gem->column()] = std::max(_shifted[gem->column()], gem->row());
            for (int i = gem->row(); i > 0; i--) {
                _gems[i][gem->column()] = _gems[i - 1][gem->column()];
                _gems[i][gem->column()]->changeRow(i);
            }
            _gems[0][gem->column()] = generateGem(0, gem->column(), gem->size());
            gem->destroy();
        }

    }
    _toDestroy.clear();
}

void Field::CheckAbove() {
    for (int i = 0; i < _columns; i++) {
        for (int j = _shifted[i]; j >= 0; j--) {
            CheckSequence(j, i, LastCheckedGem::NO_CHECK, _gems[j][i]->color());
            DestroySequence();
        }
    }
    _shifted.fill(-1);
}

void Field::updateGems() {
    for (auto& row : _gems) {
        for (auto gem: row) {
            gem->update();
        }
    }
}