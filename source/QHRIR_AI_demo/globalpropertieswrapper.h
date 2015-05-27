#ifndef GLOBALPROPERTIESWRAPPER_H
#define GLOBALPROPERTIESWRAPPER_H

#include "mutationsettings.h"
#include <QObject>
class GlobalPropertiesWrapper:public QObject
{
  Q_OBJECT
  public:
  Q_PROPERTY(unsigned ElementToCompare
             READ elementToCompare
             WRITE setElementToCompare)
  Q_PROPERTY(double gaussianIncStep
             READ gaussianIncStep
             WRITE setGaussianIncStep)
  Q_PROPERTY(double gaussianDecStep
             READ gaussianDecStep
             WRITE setGaussianDecStep)
  unsigned elementToCompare() const
  { return mutation.elementToCompare(); }

  void setElementToCompare(const unsigned val)
  { mutation.setElementToCompare(val); }

  double gaussianIncStep() const
  { return mutation.gaussianIncStep(); }

  void setGaussianIncStep(const double val) const
  {
    mutation.setGaussianIncStep(val);
  }
  double gaussianDecStep() const
  { return mutation.gaussianDecStep(); }

  void setGaussianDecStep(const double val) const
  {
    mutation.setGaussianDecStep(val);
  }

  MutationSettings& mutation;
  GlobalPropertiesWrapper(MutationSettings& mutation)
    :mutation(mutation)
  {}
};
#endif // GLOBALPROPERTIESWRAPPER_H
