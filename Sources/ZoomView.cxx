#include "ZoomView.hxx"
#include <QTimeLine>
#include <QWheelEvent>

void ZoomView::wheelEvent(QWheelEvent * event)
{
    int numDegrees = event->angleDelta().y() / 8;
    // common mouse wheel makes a full cycle for a 24 steps
    // thus 15 degrees / step
    int numSteps = numDegrees / 15;
    _numScheduledScalings += numSteps;
    // reset scaling if wheel direction changed
    if (_numScheduledScalings * numSteps < 0)
        _numScheduledScalings = numSteps;

    QTimeLine * anim = new QTimeLine(350, this);
    anim->setUpdateInterval(20);

    connect(anim, SIGNAL(valueChanged(qreal)), SLOT(onTimelineStep(qreal)));
    connect(anim, SIGNAL(finished()), SLOT(onTimelineStop()));
    anim->start();
}

void ZoomView::onTimelineStep(const qreal & value)
{
    qreal factor = 1.0 + qreal(_numScheduledScalings) / 300.0;
    scale(factor, factor);
}

void ZoomView::onTimelineStop()
{
    _numScheduledScalings > 0 ? --_numScheduledScalings
                              : ++_numScheduledScalings;
    sender()->~QObject();
}
