#include "propertymanager.h"

#include <cassert>

PropertyManager::PropertyManager(QObject& obj)
 :_obj(obj)
{
}

PropertyManager::PropertyManager(const PropertyManager& o)
  :QObject(), _obj(o._obj),_propertyMap(o._propertyMap)
{
}

void PropertyManager::registerProperty(const QString& property,
                                       const QVariant& value)
{
  assert(_propertyMap.find(property) == _propertyMap.end());
  _propertyMap.insert(property, value);
}

void PropertyManager::changeValue(const QString& property,
                                  const QVariant& value)
{
  assert(_propertyMap.find(property) != _propertyMap.end());
  assert(_propertyMap[property].type() == value.type());
  _propertyMap[property] = value;
  _obj.setProperty(property.toStdString().c_str(), value);
}

QVariant PropertyManager::value(const QString& property) const
{
  assert(_propertyMap.find(property) != _propertyMap.end());
  return _propertyMap[property];
}

PropertyManager::PropertyMap::ConstIterator
PropertyManager::begin() const
{
  return _propertyMap.begin();
}

PropertyManager::PropertyMap::ConstIterator
PropertyManager::end() const
{
  return _propertyMap.end();
}
