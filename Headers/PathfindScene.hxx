#pragma once

#include <QGraphicsScene>

class PathfindScene : public QGraphicsScene
{
public:
    explicit PathfindScene(QObject *parent = nullptr);
    //static Field FromConfig(QSettings *settings);

    void fill(const uint &rows, const uint &cols);

public slots:
    void onLeftMouseClick(const uint &x, const uint &y);
    void onRightMouseClick(const uint &x, const uint &y);
    void onGenerateButton();

protected slots:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneMouseEvent *event);


private:
    uint _rows;
    uint _columns;
    QList<QPair<uint, uint>> _blocks;
    QPair<uint, uint> _start;
    QPair<uint, uint> _end;
};
