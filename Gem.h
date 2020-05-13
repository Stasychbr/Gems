#pragma once
#include <QtWidgets/QWidget>
#include <QGraphicsObject>
#include <QGraphicsWidget>
#include <QPropertyAnimation>
#include <memory>

class Field;

class Gem: public QGraphicsObject {
public:
    enum class AnimationType {
        DESTROY,
        MOVE,
        SWAP,
    };
private:
    static const int _aniSwapLen = 400;
    static const int _aniSelLen = 150;
    static const int _aniDesLen = 200;
    int _size = 0;
    int _posX = 0;
    int _posY = 0;
    QColor _color = Qt::white;
   
    QColor getColor();
    QPointF calcPos();

    void slidingAnim(AnimationType type = AnimationType::MOVE);
    void selectAnim();
    void unselectAnim();
    //void destroyAnim();

protected:
    Field* _field = NULL;

public:
    Gem(int posX, int posY, int size, QGraphicsItem* parent);
    Gem(const Gem& t);
    virtual ~Gem();

    int row();
    int column();
    int size();
    QColor color();

    void changeRow(int row, AnimationType animType = AnimationType::MOVE);
    void changeColumn(int col, AnimationType animType = AnimationType::MOVE);
    void changeColor();
    void changeColor(QColor color);
    void select();
    void unselect();
    virtual void destroy();

    void updatePos();

    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

