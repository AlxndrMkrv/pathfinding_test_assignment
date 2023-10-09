#include "MainWindow.hxx"
#include "Settings.hxx"

#include <QApplication>
#include <QScreen>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "pathfinding_test_assignment_" +
                                 QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    w.move(Settings().applicationPosition());
    w.show();
    return app.exec();
}
