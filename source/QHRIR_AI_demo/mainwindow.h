#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <smarthrir.h>
#include <runpropertieswrapper.h>
#include <globalpropertieswrapper.h>
#include <QImage>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT
    
public:
  explicit MainWindow(QWidget *parent = 0);
  virtual ~MainWindow();
private slots:
    void on_psbRun_clicked();

    void on_btnChoose_clicked();

    void on_btnSave_clicked();

private:
private:
  SmartHrir _hrir;
  RunPropertiesWrapper* _prop;
  GlobalPropertiesWrapper* _globalProp;
  QImage _input;
  QImage _output;
};

#endif // MAINWINDOW_H
