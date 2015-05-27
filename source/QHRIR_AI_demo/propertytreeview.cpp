#include "propertytreeview.h"

#include <loki/Typelist.h>
#include <cassert>
#include <stringconverter.h>
#include <memory>
#include <QStandardItemModel>
PropertyTreeView::PropertyTreeView(QWidget*)
{
  this->setModel(new QStandardItemModel());
}
void PropertyTreeView::setManager(PropertyManager* manager)
{
  _manager = new PropertyManager(*manager);
  QStandardItemModel* model =
      static_cast<QStandardItemModel*>(this->model());
  unsigned i = 0;
  QColor grayColor("gray");
  QBrush gray(grayColor);
  for (PropertyManager::PropertyMap::ConstIterator cit = _manager->begin();
       cit != _manager->end(); ++cit)
  {
    QList<QStandardItem*> row;
    QStandardItem* itemKey = new QStandardItem(cit.key());
    QStandardItem* itemValue = new QStandardItem(cit.value().toString());
    itemKey->setEditable(false);
    itemValue->setEditable(true);
    if (i % 2)
    {
      itemKey->setBackground(gray);
      itemValue->setBackground(gray);
    }
    row.append(itemKey);
    row.append(itemValue);
    model->appendRow(row);
    ++i;
  }
  createConnections();

}

void PropertyTreeView::createConnections()
{
  connect(static_cast<QStandardItemModel*>(this->model()),
          SIGNAL(itemChanged(QStandardItem*)),
          this,
          SLOT(changeValue(QStandardItem*)));
}


void PropertyTreeView::changeValue(QStandardItem *item)
{
#define CREATE_VARIANT_IN_CASE(QType, type)\
    case QMetaType::QType:\
      newValue.reset(new QVariant(StringConverter<type>::convert(item->text())));\
    break;
  QStandardItemModel* model =
      static_cast<QStandardItemModel*>(this->model());
  QString key = model->item(item->row())->text();
  QVariant value = _manager->value(key);
  std::auto_ptr<QVariant> newValue;
  switch(value.type())
  {
    CREATE_VARIANT_IN_CASE(Int, int);
    CREATE_VARIANT_IN_CASE(UInt, unsigned);
    CREATE_VARIANT_IN_CASE(Double, double);
    case QMetaType::Bool:
      newValue.reset(item->text().toUpper() == "TRUE" ? new QVariant(true)
                                                       : new QVariant(false));
      break;
    default:
      assert(false && "type not supported");
  }
  _manager->changeValue(key, *newValue);
#undef CREATE_VARIANT_IN_CASE
}
