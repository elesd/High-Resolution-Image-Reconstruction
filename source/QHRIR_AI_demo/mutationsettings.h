#ifndef MUTATIONSETTINGS_H
#define MUTATIONSETTINGS_H

extern "C"
{
#include <smart_hrir/hrir_mutations.h>
}

class MutationSettings
{
  private:
    unsigned _elementToCompare;
    double _gaussianIncStep;
    double _gaussianDecStep;
public:
    MutationSettings(): _elementToCompare(2),
                        _gaussianIncStep(0.3),
                        _gaussianDecStep(0.2)
    {}

    MutationSettings(const MutationSettings& other)
     :_elementToCompare(other._elementToCompare),
      _gaussianIncStep(other._gaussianIncStep),
      _gaussianDecStep(other._gaussianDecStep)
    {}

    MutationSettings& operator=(const MutationSettings& other)
    {
      _elementToCompare = other._elementToCompare;
      _gaussianIncStep = other._gaussianIncStep;
      _gaussianDecStep = other._gaussianDecStep;
      return *this;
    }

    virtual ~MutationSettings()
    {
    }

    void setElementToCompare(unsigned elementToCompare)
    { _elementToCompare = elementToCompare; }

    unsigned elementToCompare() const
    { return _elementToCompare; }

    void setGaussianIncStep(double gaussianIncStep)
    { _gaussianIncStep = gaussianIncStep; }

    double gaussianIncStep() const
    { return _gaussianIncStep; }

    void setGaussianDecStep(double gaussianDecStep)
    { _gaussianDecStep = gaussianDecStep; }

    double gaussianDecStep() const
    { return _gaussianDecStep; }

    void setUp() const
    {
      hrir_mutations_set_parameters(_elementToCompare,
                                    _gaussianIncStep,
                                    _gaussianDecStep);
    }

};

#endif // MUTATIONSETTINGS_H
