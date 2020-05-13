#pragma once
#include <QtWidgets/QWidget>
#include <QGraphicsObject>
#include <QGraphicsWidget>
#include <QPropertyAnimation>
#include <memory>
//#include "Bonus.h"

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
    static const int _aniShakeLen = 150;
    static const int _bonusChance = 10; // chance = 1/n
    int _size = 0;
    int _posX = 0;
    int _posY = 0;
    bool _hasBonus = false;
   // /*std::shared_ptr<Bonus>*/ Bonus* _bonus = NULL;
    QColor _color = Qt::white;
    QPropertyAnimation* _bonusAnim = NULL;
   
    QColor getColor();
    QPointF calcPos();

    bool isBonus();
    //void bonusManagement();

    void slidingAnim(AnimationType type = AnimationType::MOVE);
    void selectAnim();
    void unselectAnim();
    void bonusAnim();

public:
    Gem(int posX, int posY, int size, QGraphicsItem* parent, QColor* leftColor = NULL, QColor* upColor = NULL);
    Gem(const Gem& t);
    ~Gem();

    int row();
    int column();
    QColor color();

    void changeRow(int row, AnimationType animType = AnimationType::MOVE);
    void changeColumn(int col, AnimationType animType = AnimationType::MOVE);
    void changeColor();
    void changeColor(QColor color);
    void select();
    void unselect();

    void updatePos();
    void destroy();
    

    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

