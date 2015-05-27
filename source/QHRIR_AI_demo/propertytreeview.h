#ifndef PROPERTYTREEVIEW_H
#define PROPERTYTREEVIEW_H

#include <propertymanager.h>
#include <QTreeView>
#include <QStandardItem>

class PropertyTreeView: public QTreeView
{
  Q_OBJECT
public:
  PropertyTreeView(QWidget* parent = 0);
  virtual ~PropertyTreeView()
  {
    delete _manager;
  }
  void setManager(PropertyManager* manager);
public slots:
  void changeValue(QStandardItem *item);
private:
  void createConnections();
private:
  PropertyManager* _manager;
};

#endif // PROPERTYTREEVIEW_H
