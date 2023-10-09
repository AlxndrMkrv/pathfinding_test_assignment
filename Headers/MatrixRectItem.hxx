#pragma once

#include <QGraphicsRectItem>


class MatrixRectItem : public QGraphicsRectItem
{
public:
    enum {Type = QGraphicsRectItem::UserType + 1};

    using QGraphicsRectItem::QGraphicsRectItem;

    int type () const override {
        return Type;
    }
};
