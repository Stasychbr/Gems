#include "Game.h"
#include "Field.h"
#include <QGraphicsView>

Game::Game(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);
    ui.mainToolBar->close();
    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    _centralWidget = new QGraphicsView;
    _centralWidget->setFixedSize({ _horSize, _vertSize });
    setFixedSize({ _horSize, _vertSize });
    setCentralWidget(_centralWidget);
    _centralWidget->setFrameStyle(0);


    _scene = new QGraphicsScene();
    _centralWidget->setRenderHint(QPainter::Antialiasing);
    _scene->setSceneRect(0, 0, _horSize, _vertSize);
    
    QRectF area(-_horSize, -_vertSize, _horSize, _vertSize);
    Field* gemsField = new Field(area);
    _gemsField = gemsField;
    _scene->addItem(_gemsField);
    _centralWidget->setScene(_scene);

}

Game::~Game() {
    delete _scene;
}