#ifndef PROPERTYEDITORFACTORY_H
#define PROPERTYEDITORFACTORY_H

#include <QObject>
#include <QMetaProperty>
#include <QMetaObject>
#include <QList>
class PropertyManager;

class PropertyManagerFactory: public QObject
{

  Q_OBJECT
private:
  typedef QList<QMetaProperty> PropertyList;

public:
    explicit PropertyManagerFactory(const QMetaObject& metaObj);

    PropertyManager createManager(QObject& object);
private:

    PropertyList _properties;
};

#endif // PROPERTYEDITORFACTORY_H
