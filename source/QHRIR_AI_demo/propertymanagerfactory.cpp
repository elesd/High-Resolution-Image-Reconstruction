#include "propertymanagerfactory.h"

#include <propertymanager.h>

PropertyManagerFactory::PropertyManagerFactory(const QMetaObject& metaObj)
{
  for (int i = metaObj.propertyOffset();
       i < metaObj.propertyCount(); ++i)
  {
    _properties.append(metaObj.property(i));
  }
}

PropertyManager
PropertyManagerFactory::createManager(QObject& object)
{
  PropertyManager ret(object);
  for (PropertyList::ConstIterator cit = _properties.begin();
       cit != _properties.end(); ++cit)
  {
    if (cit->isWritable() && cit->isReadable())
    {
      ret.registerProperty(cit->name(),
                           cit->read(&object));
    }
  }
  return ret;
}
