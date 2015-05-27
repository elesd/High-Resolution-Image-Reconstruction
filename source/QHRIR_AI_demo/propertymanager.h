#ifndef PROPERTYEDITORMANAGER_H
#define PROPERTYEDITORMANAGER_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QVariant>

class PropertyManager : public QObject
{
  Q_OBJECT
public:
  typedef QMap<QString, QVariant>  PropertyMap;
  friend class PropertyManagerFactory;
public:
  PropertyManager(const PropertyManager& o);
  virtual ~PropertyManager()
  {}
  PropertyMap::ConstIterator begin() const;
  PropertyMap::ConstIterator end() const;
  QVariant value(const QString& property) const;
public slots:
  void changeValue(const QString& property, const QVariant& value);

private:
  explicit PropertyManager(QObject& obj);
  PropertyManager& operator=(const PropertyManager& o);

  void registerProperty(const QString& property, const QVariant& value);
private:
  QObject& _obj;
  PropertyMap _propertyMap;
};

#endif // PROPERTYEDITORMANAGER_H
