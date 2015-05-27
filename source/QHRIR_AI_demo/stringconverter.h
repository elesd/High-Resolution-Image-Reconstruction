#ifndef STRINGCONVERTER_H
#define STRINGCONVERTER_H

#include <loki/Typelist.h>
#include <QMetaObject>
#include <QString>

namespace StringConverter_private
{
  template<class T, T (QString::*function)(bool *, int) const>
  struct QStringConvertFunction2Param
  {
    static T convert(const QString& str)
    {
      return (str.*function)(0, 10);
    }
  };
  template<class T, T (QString::*function)(bool *) const>
  struct QStringConvertFunction1Param
  {
    static T convert(const QString& str)
    {
      return (str.*function)(0);
    }
  };
  typedef Loki::TL::MakeTypelist<int,
                                 unsigned,
                                 long,
                                 double,
                                 float,
                                 unsigned long,
                                 short>::Result StringConvertables;

  typedef Loki::TL::MakeTypelist<QStringConvertFunction2Param<int, &QString::toInt>,
                                 QStringConvertFunction2Param<unsigned, &QString::toUInt>,
                                 QStringConvertFunction2Param<long, &QString::toLong>,
                                 QStringConvertFunction1Param<double, &QString::toDouble>,
                                 QStringConvertFunction1Param<float, &QString::toFloat>,
                                 QStringConvertFunction2Param<unsigned long, &QString::toULong>,
                                 QStringConvertFunction2Param<short, &QString::toShort>
                                >::Result QStringConverters;
}


template<class T,
         bool isBaseType =
  (Loki::TL::IndexOf<StringConverter_private::StringConvertables, T>::value >= 0)>
struct StringConverter
{};

template<class T>
struct StringConverter<T, false>
{};

template<class T>
struct StringConverter<T, true>
{
  static T convert(const QString& val)
  {
    const int idx = Loki::TL::IndexOf<StringConverter_private::StringConvertables, T>::value;
    typedef typename Loki::TL::TypeAt<StringConverter_private::QStringConverters, idx>::Result
        QStringConverter;
    T retVal = QStringConverter::convert(val);
    return retVal;
  }
};

#undef TYPE_TO_STRING

#endif // STRINGCONVERTER_H
