#include "mainwindow.h"
#include "propertymanagerfactory.h"

#include "mutationsettings.h"
#include <QFileDialog>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    _globalProp = new GlobalPropertiesWrapper(_hrir.globalSettings());
    _prop = new RunPropertiesWrapper(_hrir.settings());
    PropertyManagerFactory factoryForGlobals(
          *_globalProp->metaObject());
    PropertyManagerFactory factoryForLocals(
          *_prop->metaObject());
    PropertyManager managerForGlobals =
        factoryForGlobals.createManager(*_globalProp);
    PropertyManager managerForLocals =
        factoryForLocals.createManager(*_prop);
    globalProperties->setManager(
          &managerForGlobals);
    runProperties->setManager(
          &managerForLocals);

    inputLabel->setBackgroundRole(QPalette::Base);
    inputLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    inputLabel->setScaledContents(true);
    inputArea->setBackgroundRole(QPalette::Dark);
    outputLabel->setBackgroundRole(QPalette::Base);
    outputLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    outputLabel->setScaledContents(true);
    outputArea->setBackgroundRole(QPalette::Dark);
}

MainWindow::~MainWindow()
{
  delete _prop;
  delete _globalProp;
}

void MainWindow::on_psbRun_clicked()
{
  if (!_input.isNull())
  {
    btnSave->setEnabled(false);
    _output = _hrir.reconstruct(_input);
    outputLabel->setPixmap(QPixmap::fromImage(_output));
    outputLabel->resize(_output.width(), _output.height());
    outputArea->horizontalScrollBar()->setValue(
          2 * outputArea->horizontalScrollBar()->value()
          + outputArea->horizontalScrollBar()->pageStep()/2);
    outputArea->verticalScrollBar()->setValue(
          2 * outputArea->verticalScrollBar()->value()
          + outputArea->verticalScrollBar()->pageStep()/2);
    btnSave->setEnabled(true);
    QMainWindow::statusBar()->showMessage("Iteration: "
                             + QString::number(_hrir.details().reachedIteration)
                             + " Rank: "
                             + QString::number(_hrir.details().reachedRank));
  }
}

void MainWindow::on_btnChoose_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath());
  if (!fileName.isEmpty())
  {
    _input = QImage(fileName);
    inputLabel->setPixmap(QPixmap::fromImage(_input));
    inputLabel->resize(_input.width(), _input.height());
  }
}

void MainWindow::on_btnSave_clicked()
{
  QString fileName = QFileDialog::getSaveFileName(this, "Save File", QDir::currentPath());
  if (!fileName.isEmpty())
  {
    _output.save(fileName);
  }
}
