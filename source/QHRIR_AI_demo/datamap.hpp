#ifndef DATAMAP_HPP
#define DATAMAP_HPP

#include <QImage>
#include <stdexcept>
#include <cmath>
#include <limits>
#include <loki/Typelist.h>

typedef Loki::TL::MakeTypelist<int, unsigned,
                               short, unsigned short,
                               char, unsigned char>::Result StorageDataTypes;

template<class T,
         bool NeedScaling,
         bool isStorageType = (Loki::TL::IndexOf<StorageDataTypes, T>::value >= 0)>
class DataMap;

template<class T, bool NeedScaling>
class DataMap<T, NeedScaling, false>
{
};

template<class T,
         bool NeedScaling>
class DataMap<T, NeedScaling, true>
{
  private:
    T* _data;
    unsigned _width;
    unsigned _height;
  public:
    DataMap(const unsigned width,
            const unsigned height,
            T* data = 0)
      :_data((data == 0) ? new T[width * height]
                         : data),
       _width(width),
       _height(height)
    {
    }

    explicit DataMap(const QImage& img);

    DataMap()
      : _data(0),
        _width(0),
        _height(0)
    {
    }

    DataMap(const DataMap& other);

    DataMap& operator=(const DataMap& other);

    ~DataMap()
    {
      destroy();
    }

    void destroy()
    {
      delete[] _data;
    }

    unsigned width() const
    {
      return _width;
    }

    unsigned height() const
    {
      return _height;
    }

    DataMap<T, NeedScaling>& operator++()
    {
      _data++;
      return *this;
    }

    DataMap<T, NeedScaling> operator++(int)
    {
      DataMap<T, NeedScaling> ret(*this);
      _data++;
      return ret;
    }

    DataMap<T, NeedScaling>& operator--()
    {
      _data--;
      return *this;
    }

    DataMap<T, NeedScaling> operator--(int)
    {
      DataMap<T, NeedScaling> ret(*this);
      _data--;
      return ret;
    }

    operator T*()
    {
      return _data;
    }

    operator T*() const;

    operator QImage() const;

    T& operator[](const unsigned i)
    {
      return _data[i];
    }

    const T& operator[](const unsigned i) const
    {
      return _data[i];
    }

    const T& operator()(const unsigned i, const unsigned j) const
    {
      return _data[_width * i + j];
    }

    T& operator()(const unsigned i, const unsigned j)
    {
      return _data[_width * i + j];
    }

    DataMap<T, NeedScaling>& operator+=(const unsigned& i)
    {
      _data += i;
      return *this;
    }

    DataMap<T, NeedScaling>& operator+=(const DataMap<T, NeedScaling>& other)
    {
      if (other.width() != width()
          || other.height() != height())
        throw std::invalid_argument();
      for (unsigned i = 0; i < width() * height(); ++i)
        _data[i] = std::max(other._data[i] + _data[i],
                            std::numeric_limits<T>::max());
      return *this;
    }

    DataMap<T, NeedScaling>& operator-=(const unsigned& i)
    {
      _data -= i;
      return *this;
    }

    friend DataMap<T, NeedScaling> operator+ (const DataMap<T, NeedScaling>& m, const unsigned i)
    {
      return DataMap<T, NeedScaling>(m._width, m._height, m._data + i);
    }

    friend DataMap<T, NeedScaling> operator- (const DataMap<T, NeedScaling>& m, const unsigned i)
    {
      return DataMap<T, NeedScaling>(m._width, m._height, m._data - i);
    }

#define GEN_BOOL_OP(op)\
    friend bool operator op (const DataMap<T, NeedScaling>& a, const DataMap<T, NeedScaling>& b)\
    {\
      return a._data op b._data;\
    }
    GEN_BOOL_OP(==)
    GEN_BOOL_OP(!=)
    GEN_BOOL_OP(<)
    GEN_BOOL_OP(>)
    GEN_BOOL_OP(<=)
    GEN_BOOL_OP(>=)
#undef GEN_BOOL_OP

};

/***************************** BODY *******************************************/
#include <cstring>
#include <QColor>
#include <cmath>
#include <iostream>

template<class T, bool NeedScaling>
DataMap<T, NeedScaling, true>::DataMap(const QImage& img)
  :_data(new T[img.width() * img.height()]),
   _width(img.width()),
   _height(img.height())
{
  const QImage cimg = img.convertToFormat(QImage::Format_Indexed8, Qt::MonoOnly);
  for (unsigned i = 0; i < _height; ++i)
    for (unsigned j = 0; j < _width; ++j)
      _data[i * _width + j] = cimg.bits()[i * cimg.bytesPerLine() + j];
}

template<class T, bool NeedScaling>
DataMap<T, NeedScaling, true>::DataMap(const DataMap& other)
  : _data(new T[other._width * other._height]),
    _width(other._width),
    _height(other._height)
{
  memcpy(_data, other._data, _width * _height);
}

template<class T, bool NeedScaling>
DataMap<T, NeedScaling, true>& DataMap<T, NeedScaling, true>::operator=
  (const DataMap<T, NeedScaling, true>& other)
{
  destroy();
  _width = other._width;
  _height = other._height;
  _data = new T[_width * _height];
  memcpy(_data, other._data, _width * _height);
  return *this;
}

template<class T, bool NeedScaling>
DataMap<T, NeedScaling, true>::operator T*() const
{
  T* ret = 0;
  if (_width != 0
      && _height !=0)
  {
    ret = new T[_width * _height];
    memcpy(ret, _data, _width * _height);
  }
  return ret;
}

template<class T, bool NeedScaling>
DataMap<T, NeedScaling, true>::operator QImage() const
{
  unsigned expandedWidth = ((_width + 3) / 4) * 4;
  if (_data != 0)
  {
    // TODO memory leak
    uchar* convertedData = new uchar[expandedWidth * _height];
    if (NeedScaling)
    {
      T max = _data[0];
      T min = max;
      for (unsigned i = 1; i < _width * _height; ++i)
      {
        if (_data[i] > max)
          max = _data[i];
        if (_data[i] < min)
          min = _data[i];
      }
      T d = max - min;
      for (unsigned i = 0; i < _height; ++i)
      {
        for (unsigned j = 0; j < expandedWidth; ++j)
        {
          convertedData[i * expandedWidth + j] = j < _width ?
               (_data[i * _width + j] - min) / (double)(d) * 255
              : 0;
        }
      }
    }
    else
    {
      for (unsigned i = 0; i < _height; ++i)
      {
        for (unsigned j = 0; j < expandedWidth; ++j)
        {
          convertedData[i * expandedWidth + j] = j < _width ?
               _data[i * _width + j]
              : 0;
        }
      }
    }
    QImage ret(convertedData, _width, _height,
               QImage::Format_Indexed8);

    QVector<QRgb> colorTable;
    for (int i = 0; i < 256; i++)
      colorTable.push_back(QColor(i, i, i).rgb());
    ret.setColorTable(colorTable);
    return ret;
  }
  return QImage();

}

#endif // GRADIENTMAP_HPP

