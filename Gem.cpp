#include "Gem.h"
#include "Field.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QRandomGenerator>


Gem::Gem(int posX, int posY, int size, QGraphicsItem* parent) {
    _size = size;
    _posX = posX;
    _posY = posY;
    _field = (Field*)parent;
    _color = getColor();
    if (posX != 0 && posY != 0) {
        while (_field->gemAt(posY - 1, posX)->color() == _color || _field->gemAt(posY, posX - 1)->color() == _color) {
            _color = getColor();
        }
    }
    else if (posX != 0) {
        while (_field->gemAt(posY, posX - 1)->color() == _color) {
            _color = getColor();
        }
    }
    else if (posY != 0) {
        while (_field->gemAt(posY - 1, posX)->color() == _color) {
            _color = getColor();
        }
    }
    setParentItem(parent);
    //this->setPos(this->calcPos());
    slidingAnim(AnimationType::DESTROY);
}

Gem::Gem(const Gem& t) {
    _size = t._size;
    _posX = t._posX;
    _posY = t._posY;
    _color = t._color;
    _field = t._field;
    setParentItem(t.parentItem());
    this->setPos(this->calcPos());

}

Gem::~Gem() {
}

QPointF Gem::calcPos() {
    return QPointF(_size * _posX + 0.5 * _size, _size * _posY + 0.5 * _size);
}

void Gem::slidingAnim(AnimationType type) {
    QPropertyAnimation* anim = new QPropertyAnimation(this, "pos");
    if (type == AnimationType::DESTROY) {
        anim->setStartValue(calcPos() - QPointF{ 0, (double)_size });
    }
    if (type == AnimationType::SWAP) {
        anim->setEasingCurve(QEasingCurve::OutCubic);
    }
    anim->setDuration(_aniSwapLen);
    anim->setEndValue(calcPos());
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void Gem::selectAnim() {
    QPropertyAnimation* anim = new QPropertyAnimation(this, "scale");
    anim->setDuration(_aniSelLen);
    anim->setEndValue(0.8);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void Gem::unselectAnim() {
    QPropertyAnimation* anim = new QPropertyAnimation(this, "scale");
    anim->setDuration(_aniSelLen);
    anim->setEndValue(1);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

int Gem::row() {
    return _posY;
}

int Gem::column() {
    return _posX;
}

int Gem::size() {
    return _size;
}

QColor Gem::color() {
    return _color;
}

void Gem::changeRow(int row, AnimationType animType) {
    if (_posY == row) {
        return;
    }
    _posY = row;
    slidingAnim(animType);
}

void Gem::changeColumn(int col, AnimationType animType) {
    if (_posX == col) {
        return;
    }
    _posX = col;
    slidingAnim(animType);
}

void Gem::changeColor() {
    QColor newColor = getColor();
    while (_color == newColor) {
        newColor = getColor();
    }
    _color = newColor;
}

void Gem::changeColor(QColor color) {
    _color = color;
}

void Gem::select() {
    selectAnim();
}

void Gem::unselect() {
    unselectAnim();
}

void Gem::updatePos() {
    this->setPos(calcPos());
}

QColor Gem::getColor() {
    int color = QRandomGenerator::global()->bounded(0, 8);
    switch (color) {
    case 0:
        return QColor(Qt::red);
    case 1:
        return QColor(Qt::yellow);
    case 2:
        return QColor(Qt::green);
    case 3:
        return QColor(Qt::blue);
    case 4:
        return QColor(Qt::magenta);
    case 5:
        return QColor("#FC6600"); //orange
    case 6:
        return QColor(Qt::cyan);
    case 7:
        return QColor(Qt::darkMagenta);
    default:
        return QColor(Qt::black);
    }
}

QRectF Gem::boundingRect() const {
    return QRectF(-0.5 * _size, -0.5 * _size, _size, _size);
}

void Gem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(_color);
    painter->drawRect(this->boundingRect());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Gem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem* parent = parentItem();
    Field* field = (Field*)parent;
    field->SelectGem(_posY, _posX);
}
