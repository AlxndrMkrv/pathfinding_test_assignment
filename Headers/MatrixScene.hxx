#pragma once

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsPathItem>
#include <QFutureWatcher>
#include <QElapsedTimer>
#include <QHash>
#include <QPair>
#include <memory>
#include "MatrixCell.hxx"
#include "MatrixRectItem.hxx"
#include "Graph.hxx"

#ifndef KNOW_WHAT_TO_DO
#error "This class supposes implicit restriction of columns and rows number equal to 255"
#endif

using MCell = MatrixCell;
using MRoute = QVector<MCell>;

class MatrixScene : public QGraphicsScene
{
    Q_OBJECT

public: /* Public methods to call from MainWindow */
    explicit MatrixScene(QGraphicsView *parent);

    void redraw(const uint &cols, const uint &rows);

    void setStartPoint(const MCell &cell);
    void setEndPoint(const MCell &cell);
    void setBlock(const MCell &cell);
    void startRouteCalculation();

private:
    bool isValid(const MCell &cell);
    MCell mouse2matrix (const QPointF &pos) const;
    QPointF matrix2mouse (const MCell &cell) const;
    MatrixRectItem * rectAt(const MCell &cell);
    void placeMark(QGraphicsTextItem * mark, const MCell &cell);


    void _redrawRoute(const MRoute &route);
    void _removeRoute();


    void _setStartPoint(const MCell &cell);
    void _removeStartPoint();
    void _setEndPoint(const MCell &cell);
    void _removeEndPoint();
    void _blockCell(const MCell &cell);
    void _unblockCell(const MCell &cell);

    static MRoute CalculateRoute(const DFS &graph,
                                 const MCell &start, const MCell &end);


public slots:
    void onRouteCalculated();

protected slots:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


private:
    uint _columns;
    uint _rows;
    uint _cellPixelSize;

    MCell _startCell;
    MCell _endCell;

    QGraphicsPathItem _routeItem;
    QGraphicsTextItem _startMark;
    QGraphicsTextItem _endMark;

    DFS _graph;
    QFutureWatcher<MRoute> _routeWatcher;
};
