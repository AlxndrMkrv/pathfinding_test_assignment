#include "Settings.hxx"

QPoint Settings::applicationPosition() const
{
    bool success;
    uint x = value("Application/x").toUInt(&success);
    x = success ? x : 0;

    uint y = value("Application/y").toUInt(&success);
    y = success ? y : 0;
    return QPoint(x, y);
}

void Settings::storeApplicationPosition(const QPoint & pos)
{
    setValue("Application/x", pos.x());
    setValue("Application/y", pos.y());
}

uint Settings::cellSize() const
{
    bool success;
    uint size = value("Application/cell_size").toUInt(&success);
    size = success ? size : 20;
    return size;
}

uint Settings::markSize() const
{
    bool success;
    uint size = value("Application/mark_size").toUInt(&success);
    size = success ? size : 17;
    return size;
}
