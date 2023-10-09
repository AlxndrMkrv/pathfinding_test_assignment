#include <QMessageBox>
#include <QRandomGenerator>

#include "MainWindow.hxx"
#include "UI/ui_MainWindow.h"
#include "ZoomView.hxx"
#include "MatrixScene.hxx"
#include "CellsNumberValidator.hxx"
#include "Settings.hxx"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // Initialize UI
    ui->setupUi(this);

    // Restore application position
    move(Settings().applicationPosition());

    // Set scene
    ui->view->setScene(new MatrixScene(ui->view));

    // Set validators for "W"/"H" line edits
    ui->widthLineEdit->setValidator(new CellsNumberValidator(2, 255));
    ui->heightLineEdit->setValidator(new CellsNumberValidator(2, 255));

    // Connect "W"/"H" line edits finish signals
    connect(ui->widthLineEdit, SIGNAL(editingFinished()),
            SLOT(onMatrixSizeChanged()));
    connect(ui->heightLineEdit, SIGNAL(editingFinished()),
            SLOT(onMatrixSizeChanged()));

    // Connect "Generate" button signal
    connect(ui->generateButton, SIGNAL(clicked(bool)),
            SLOT(onGenerateButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPair<uint, uint> MainWindow::matrixSize() const
{
    bool colsSuccess;
    int cols = ui->widthLineEdit->text().toInt(&colsSuccess);
    bool rowsSuccess;
    int rows = ui->heightLineEdit->text().toInt(&rowsSuccess);

    // return matrix size if conversion succeed
    if(colsSuccess && rowsSuccess &&
        2 <= cols && cols <= 255 &&
        2 <= rows && rows <= 255)
        return qMakePair<uint, uint>(cols, rows);
    // show error and return (0, 0) if conversion failed
    else if (!colsSuccess || cols < 2 || 255 < cols)
        QMessageBox::critical(nullptr, tr("Invalid matrix size"),
                              tr("Invalid width cells number"));
    else if (!rowsSuccess || rows < 2 || 255 < rows)
        QMessageBox::critical(nullptr, tr("Invalid matrix size"),
                              tr("Invalid height cells number"));
    return qMakePair(0, 0);
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    onMatrixSizeChanged();
}

void MainWindow::redrawScene(const uint &cols, const uint &rows)
{
    // Call Scene redraw method
    MatrixScene * scene = dynamic_cast<MatrixScene *>(ui->view->scene());
    scene->redraw(cols, rows);

    // Fit Scene in View
    ui->view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::onMatrixSizeChanged()
{
    auto cr = matrixSize();
    redrawScene(cr.first, cr.second);
}

void MainWindow::onGenerateButton()
{
    QRandomGenerator * random = QRandomGenerator::global();
    MatrixScene * scene = dynamic_cast<MatrixScene *>(ui->view->scene());

    // Generate matrix size
    const uint matrixSize = random->bounded(5, 20);

    // Change matrix size input lines
    ui->widthLineEdit->setText(QString::number(matrixSize));
    ui->heightLineEdit->setText(QString::number(matrixSize));

    // Redraw the scene
    redrawScene(matrixSize, matrixSize);


    // Randomly pick cells to block and start/end points
    const uint totalCells = matrixSize * matrixSize;
    const double blockRate = static_cast<double>(random->bounded(5, 20)) / 100;

    // number of cells to randomly pick:
    // total cells * block rate + start/end points
    const uint cellsToPick = totalCells * blockRate + 2;

    // use set to store indices of cells to be changed
    QSet<uint> cellsToModify;
    // fill the set until required number of cells is reached
    while (cellsToModify.size() < cellsToPick)
        cellsToModify.insert(random->bounded(totalCells));

    // lambda to convert cell index to Pair<CR, CR> for the scene
    auto num2point = [matrixSize](const uint &num){
        return MCell(num / matrixSize, num % matrixSize); };

    // change the picked cells on the scene
    uint blockCounter = 0;
    for (auto cell : cellsToModify) {
        switch (blockCounter++) {
        case 0:
            scene->setStartPoint(num2point(cell));
            break;
        case 1:
            scene->setEndPoint(num2point(cell));
            break;
        default:
            scene->setBlock(num2point(cell));
        }
    }

    // Start route calculation
    scene->startRouteCalculation();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Settings().storeApplicationPosition(pos());
}
