#include "MainWindow.hxx"
#include "Settings.hxx"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Try to load i18n file
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

    // Create main window and move to saved position
    MainWindow w;
    w.move(Settings().applicationPosition());

    // Show window
    w.show();
    return app.exec();
}
