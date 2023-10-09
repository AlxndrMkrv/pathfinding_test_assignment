#pragma once

#include <QMainWindow>
#include <QCloseEvent>
#include <QShowEvent>
#include <QPair>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPair<uint, uint> matrixSize () const;

public slots:
    void onMatrixSizeChanged();

protected:
    virtual void showEvent(QShowEvent *event);

protected slots:
    void onGenerateButton();
    virtual void closeEvent(QCloseEvent *event);

private:
    void redrawScene(const uint &cols, const uint &rows);

private:
    Ui::MainWindow *ui;
};
