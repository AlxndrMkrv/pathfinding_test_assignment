#pragma once

#include <QSettings>
#include <QString>
#include <QPoint>
#include <string>

class Settings : QSettings
{
    static constexpr char SettingsFile [] = "./settings.ini";
public:
    explicit Settings() : QSettings(SettingsFile, QSettings::IniFormat) {}

    QPoint applicationPosition() const;
    void storeApplicationPosition(const QPoint &pos);

    uint cellSize() const;
    uint markSize() const;
};
