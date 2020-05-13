#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Game.h"
#include "Field.h"

class Game : public QMainWindow
{
    Q_OBJECT

public:
    Game(QWidget *parent = Q_NULLPTR);
    ~Game();
private:
    const int _vertSize = 600;
    const int _horSize = 800;

    QGraphicsView* _centralWidget = NULL;
    QGraphicsScene* _scene;
    Field* _gemsField;
    Ui::GameClass ui;
};
