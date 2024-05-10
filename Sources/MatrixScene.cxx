#include "MatrixScene.hxx"
#include "MatrixCell.hxx"
#include "Settings.hxx"
#include <QDebug>
#include <QGraphicsSceneEvent>
#include <QGraphicsView>
#include <QPainterPath>
#include <QPen>
#include <QRandomGenerator>
#include <QtConcurrent/QtConcurrent>

MatrixScene::MatrixScene(QGraphicsView * parent) :
    QGraphicsScene(parent), _startCell(MCell::Invalid()),
    _endCell(MCell::Invalid()), _startMark(QString("A")), _endMark(QString("B"))
{
    // Read params from settings
    Settings s;
    _cellPixelSize = s.cellSize();
    QFont markFont;
    markFont.setPixelSize(s.markSize());

    // Create route item
    _routeItem.setPen(QPen(_color(QPalette::Text)));

    // Create start/end marks
    _startMark.setFont(markFont);
    _endMark.setFont(markFont);

    connect(&_routeWatcher, SIGNAL(finished()), SLOT(onRouteCalculated()));

    // Initialize tracers
    std::shared_ptr<AbstractTracer> ptr = std::make_shared<DFS>(_graph.edges());
    _tracers.insert(std::make_pair(ptr->name(), ptr));
    ptr = std::make_shared<BFS>(_graph.edges());
    _tracers.insert(std::make_pair(ptr->name(), ptr));
    _tracer = _tracers.begin();
}

void MatrixScene::redraw(const uint & cols, const uint & rows)
{
    // Stop route calculation if running
    if (_routeWatcher.isRunning())
        _routeWatcher.cancel();

    // Remove the route item if present
    _removeRoute();

    // Remove the path marks if exists
    _removeStartPoint();
    _removeEndPoint();

    // Recreate the matrix by adding missing cells and removing extras
    for (auto c = 0; c < qMax(cols, _columns); ++c) {
        for (auto r = 0; r < qMax(rows, _rows); ++r) {
            // Add new cells to the scene
            if (c >= _columns || r >= _rows) {
                addItem(new MatrixRectItem(c * _cellPixelSize,
                                           r * _cellPixelSize, _cellPixelSize,
                                           _cellPixelSize));
            }
            // Remove extra cells from the scene
            else if (c >= cols || r >= rows) {
                removeItem(rectAt(MCell(c, r)));
            }
            // Unbrush others
            else {
                rectAt(MCell(c, r))->setBrush(_color(QPalette::Base));
            }
        }
    }

    // Fit scene to items
    setSceneRect(itemsBoundingRect());

    // Refresh columns/rows number
    _columns = cols;
    _rows = rows;

    // Rebuild graph
    _graph.rebuild(_columns, _rows);
}

bool MatrixScene::isValid(const MCell & cell)
{
    return 0 <= cell.col && cell.col < _columns && 0 <= cell.row &&
           cell.row < _rows && cell.isValid();
}

void MatrixScene::setStartPoint(const MCell & cell)
{
    if (isValid(cell) && _graph.isExists(cell))
        _setStartPoint(cell);
}

void MatrixScene::setEndPoint(const MCell & cell)
{
    if (isValid(cell) && _graph.isExists(cell))
        _setEndPoint(cell);
}

void MatrixScene::setBlock(const MCell & cell)
{
    if (isValid(cell) && _graph.isExists(cell))
        _blockCell(cell);
}

MCell MatrixScene::mouse2matrix(const QPointF & pos) const
{
    const int col = pos.x() / _cellPixelSize;
    const int row = pos.y() / _cellPixelSize;
    // Return valid MCell if position inside the scene matrix
    if (0 <= col && col < _columns && 0 <= row && row < _rows)
        return MCell(static_cast<uint8_t>(col), static_cast<uint8_t>(row));
    // Return invalid MCell otherwise
    else
        return MCell::Invalid();
}

QPointF MatrixScene::matrix2mouse(const MCell & cell) const
{
    auto center = [&](const uint & n) {
        return n * _cellPixelSize + static_cast<double>(_cellPixelSize) / 2;
    };

    return QPointF(center(cell.col), center(cell.row));
}

MatrixRectItem * MatrixScene::rectAt(const MCell & cell)
{
    // Find MatrixRectItem on the cell
    for (auto & item : items(matrix2mouse(cell))) {
        if (item->type() == MatrixRectItem::Type)
            return dynamic_cast<MatrixRectItem *>(item);
    }

    throw std::out_of_range("MatrixScene::rectAt() called outside the matrix");
}

void MatrixScene::placeMark(QGraphicsTextItem * mark, const MCell & cell)
{
    const QRectF rect = mark->boundingRect();

    // Mark must be placed in the center of the cell:
    // number of full cells + half of the cell - half of the item
    auto calc = [&](const int & n, const double & w) {
        return n * _cellPixelSize + static_cast<double>(_cellPixelSize) / 2 -
               w / 2;
    };

    mark->setPos(calc(cell.col, rect.width()), calc(cell.row, rect.height()));
}

void MatrixScene::_redrawRoute(const MRoute & route)
{
    // Skip empty route
    if (route.size() > 1) {
        // Create path object, set the first route point as start
        QPainterPath path(matrix2mouse(route.front()));

        // Add lines to path iterating the route from the second cell
        auto itr = route.begin();
        for (++itr; itr != route.end(); ++itr)
            path.lineTo(matrix2mouse(*itr));

        // Create GraphicsPathItem and put into the scene
        _routeItem.setPath(path);

        // Add the item to scene if removed
        if (_routeItem.scene() != this)
            addItem(&_routeItem);
    }
}

void MatrixScene::_removeRoute()
{
    if (_routeItem.scene() == this)
        removeItem(&_routeItem);
}

void MatrixScene::startRouteCalculation()
{
    if (_startCell.isValid() && _graph.isExists(_startCell) &&
        _endCell.isValid() && _graph.isExists(_endCell)) {

        // Cancel the route calculation if running
        if (_routeWatcher.isRunning())
            _routeWatcher.cancel();

        // Run graph route calculation in a separate thread
        // and attach it to the watcher
        _routeWatcher.setFuture(QtConcurrent::run(
            CalculateRoute, _tracer->second, _startCell, _endCell));
    }
}

std::vector<std::string_view> MatrixScene::tracerNames() const
{
    std::vector<std::string_view> names;
    std::transform(_tracers.begin(), _tracers.end(), std::back_inserter(names),
                   [](const auto & pair) { return pair.first; });

    return names;
}

std::string_view MatrixScene::tracer() const { return _tracer->second->name(); }

void MatrixScene::setTracer(const std::string_view & name)
{
    const TracerMap::const_iterator itr = _tracers.find(name);

    if (itr == _tracers.end())
        throw std::runtime_error(std::format("unknown tracer name: {}", name));

    _tracer = itr;
}

void MatrixScene::_setStartPoint(const MCell & cell)
{
    // Set start cell
    _startCell = cell;

    // Move start mark to the cell
    placeMark(&_startMark, cell);

    // Add mark to the scene
    if (_startMark.scene() != this)
        addItem(&_startMark);
}

void MatrixScene::_removeStartPoint()
{
    if (_startMark.scene() == this)
        removeItem(&_startMark);
}

void MatrixScene::_setEndPoint(const MCell & cell)
{
    // Set end cell
    _endCell = cell;

    // Move end mark to the cell
    placeMark(&_endMark, cell);

    // Add mark to the scene
    if (_endMark.scene() != this)
        addItem(&_endMark);
}

void MatrixScene::_removeEndPoint()
{
    if (_endMark.scene() == this)
        removeItem(&_endMark);
}

void MatrixScene::_blockCell(const MCell & cell)
{
    _graph.remove(cell);
    rectAt(cell)->setBrush(Qt::black);
}

void MatrixScene::_unblockCell(const MCell & cell)
{
    _graph.add(cell);
    rectAt(cell)->setBrush(_color(QPalette::Base));
}

const QColor & MatrixScene::_color(QPalette::ColorRole cr) const
{
    return palette().color(cr);
}

QVector<MCell> MatrixScene::CalculateRoute(
    const std::shared_ptr<AbstractTracer> & tracer, const MCell & start,
    const MCell & end)
{
    const Route route = tracer->findRoute(start, end);

    return QVector<MCell>(route.begin(), route.end());
}

void MatrixScene::onRouteCalculated()
{
    // Get the calculated route from the watchers future and call redraw method
    _redrawRoute(_routeWatcher.future().result());
}

void MatrixScene::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    const MCell cell = mouse2matrix(event->scenePos());

    // Use mouse cursor as end cell if start cell set and end _mark_ not set
    if (_startCell.isValid() && _endMark.scene() != this && cell.isValid() &&
        _endCell != cell && _graph.isExists(cell)) {
        _endCell = cell;
        startRouteCalculation();
    }
}

void MatrixScene::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    const MCell cell = mouse2matrix(event->scenePos());

    // Handle events only inside the matrix
    if (cell.isValid()) {
        // Left click: set/reset start/end route points.
        // Works only on exist cells
        if (event->button() == Qt::MouseButton::LeftButton &&
            _graph.isExists(cell)) {

            // Set the start point if not exists
            if (_startCell.isInvalid()) {
                _setStartPoint(cell);
            }

            // Remove both marks, points and route if start cell clicked twice
            else if (_startCell == cell) {
                _removeStartPoint();
                _removeEndPoint();
                _removeRoute();
                _startCell = MCell::Invalid();
                _endCell = MCell::Invalid();
            }

            // Set the end point if not exists and start already set
            // note: _endCell may be set by moveEvent, so look at the mark
            else if (_startCell.isValid() &&
                     (_endCell.isInvalid() || _endMark.scene() != this)) {
                _setEndPoint(cell);
            }

            // Remove end mark if clicked twice (and path if exist)
            else if (_endCell == cell && _endMark.scene() == this) {
                _removeEndPoint();
                _removeRoute();
                _endCell = MCell::Invalid();
            }
        }

        // Right click: set/reset blocked cells
        // Works only on empty cells
        else if (event->button() == Qt::MouseButton::RightButton &&
                 _startCell != cell && _endCell != cell) {
            // Remove existing cell and brush it on the scene
            if (_graph.isExists(cell)) {
                _removeRoute();
                _blockCell(cell);
            }
            // Otherwise add it to the graph and unbrush
            else {
                try {
                    _removeRoute();
                    _unblockCell(cell);
                }
                catch (std::out_of_range &) {
                    emit failedToAddCell(cell);
                    qDebug() << "Got out_of_range while adding " << cell
                             << " to " << _columns << "x" << _rows << " matrix";
                }
            }
        }
    }

    // Try to start route calculation if possible
    startRouteCalculation();
}
