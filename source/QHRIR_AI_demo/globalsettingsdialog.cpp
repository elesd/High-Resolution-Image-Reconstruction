#include "globalsettingsdialog.h"
#include "ui_globalsettingsdialog.h"

GlobalSettingsDialog::GlobalSettingsDialog(QWidget *parent) :
    QDialog(parent)
{
  this->setupUi(this);
  this->refreshUi();
}

GlobalSettingsDialog::~GlobalSettingsDialog()
{

}

void GlobalSettingsDialog::refreshUi()
{
  spbIterationLimit->setValue(this->);
}
