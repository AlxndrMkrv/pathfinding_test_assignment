#pragma once

#include <QGraphicsView>

class ZoomView : public QGraphicsView {
    Q_OBJECT

public:
    using QGraphicsView::QGraphicsView;

protected:
    void wheelEvent(QWheelEvent * event) override;

private slots:
    void onTimelineStep(const qreal & value);
    void onTimelineStop();

private:
    qreal _numScheduledScalings;
};
