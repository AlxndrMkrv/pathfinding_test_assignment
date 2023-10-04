#include "PathfindScene.hxx"
#include <QDebug>
#include <QGraphicsSceneEvent>
#include <QRandomGenerator>
#include <QPen>

PathfindScene::PathfindScene(QObject *parent)
    : QGraphicsScene{parent} {}

void PathfindScene::fill(const uint &rows, const uint &cols)
{
    addLine(0, 0, 0, width(), QPen(Qt::black, 3));
}

void PathfindScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "mouseMoveEvent: " << event->scenePos();
}

void PathfindScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "mousePressEvent: " << event->button() << " on " << event->scenePos();
    fill(0, 0);
    qDebug() << "width:" << width();

}


