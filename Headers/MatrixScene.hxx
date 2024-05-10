#pragma once

#include "Graph.hxx"
#include "MatrixCell.hxx"
#include "MatrixRectItem.hxx"
#include "Tracer.hxx"
#include <QElapsedTimer>
#include <QFutureWatcher>
#include <QGraphicsPathItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QHash>
#include <QPair>
#include <QPalette>
#include <memory>

#ifndef KNOW_WHAT_TO_DO
#error "This class supposes implicit restriction of columns and rows number \
equal to 255"
#endif

using MCell = MatrixCell;
using MRoute = QVector<MCell>;

class MatrixScene : public QGraphicsScene {
    Q_OBJECT

    using TracerMap =
        std::map<std::string_view, std::shared_ptr<AbstractTracer>>;

public: /* Public methods to call from MainWindow */
    explicit MatrixScene(QGraphicsView * parent);

    void redraw(const uint & cols, const uint & rows);

    void setStartPoint(const MCell & cell);
    void setEndPoint(const MCell & cell);
    void setBlock(const MCell & cell);
    void startRouteCalculation();

    std::vector<std::string_view> tracerNames() const;
    std::string_view tracer() const;
    void setTracer(const std::string_view & name);

private:
    bool isValid(const MCell & cell);
    MCell mouse2matrix(const QPointF & pos) const;
    QPointF matrix2mouse(const MCell & cell) const;
    MatrixRectItem * rectAt(const MCell & cell);
    void placeMark(QGraphicsTextItem * mark, const MCell & cell);

    void _redrawRoute(const MRoute & route);
    void _removeRoute();

    void _setStartPoint(const MCell & cell);
    void _removeStartPoint();
    void _setEndPoint(const MCell & cell);
    void _removeEndPoint();
    void _blockCell(const MCell & cell);
    void _unblockCell(const MCell & cell);

    const QColor & _color(QPalette::ColorRole cr) const;

    static MRoute CalculateRoute(const std::shared_ptr<AbstractTracer> & tracer,
                                 const MCell & start, const MCell & end);

signals:
    void failedToAddCell(MatrixCell cell);

public slots:
    void onRouteCalculated();

protected slots:
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

private:
    uint _columns = 0;
    uint _rows = 0;
    uint _cellPixelSize = 0;

    MCell _startCell;
    MCell _endCell;

    QGraphicsPathItem _routeItem;
    QGraphicsTextItem _startMark;
    QGraphicsTextItem _endMark;

    Graph _graph;
    TracerMap _tracers;
    TracerMap::const_iterator _tracer;

    QFutureWatcher<MRoute> _routeWatcher;
};
