#include "MatrixCell.hxx"
#include "MatrixScene.hxx"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

MatrixCell::MatrixCell(const uint &x, const uint &y) :
    _x(x), _y(y)
{
    connect(this, SIGNAL(leftClick()), scene(), SLOT(onCellClicked()));
    connect(this, SIGNAL(rightClick()), scene(), SLOT(onCellClicked()));
}

void MatrixCell::clear()
{
}

void MatrixCell::block()
{

}

void MatrixCell::setRoute(const Direction &d)
{
}

void MatrixCell::setStart()
{

}

void MatrixCell::setEnd()
{

}

uint MatrixCell::size() const
{
    return dynamic_cast<MatrixScene *>(scene())->cellSize();
}

QRectF MatrixCell::boundingRect() const
{
    return QRectF(_x, _y, size(), size());
}

void MatrixCell::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    painter->drawRect(_x, _y, size(), size());
}

void MatrixCell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton)
        emit leftClick();
    else if (event->button() == Qt::MouseButton::RightButton)
        emit rightClick();
}
