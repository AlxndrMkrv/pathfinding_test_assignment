#pragma once

#include "MatrixCell.hxx"
#include <QCloseEvent>
#include <QMainWindow>
#include <QMap>
#include <QPair>
#include <QShowEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = nullptr);
    ~MainWindow();

    QPair<uint, uint> matrixSize() const;

public slots:
    void onMatrixSizeChanged();
    void onFailedToAddCell(const MatrixCell & cell);

protected:
    virtual void showEvent(QShowEvent * event);

protected slots:
    void onGenerateButton();
    void onTracerChanged();
    virtual void closeEvent(QCloseEvent * event);

private:
    void redrawScene(const uint & cols, const uint & rows);

private:
    Ui::MainWindow * ui;
};
