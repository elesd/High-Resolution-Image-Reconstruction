#ifndef RUNPROPERTIESWRAPPER_H
#define RUNPROPERTIESWRAPPER_H

#include <smarthrir.h>
#include <QObject>

class RunPropertiesWrapper:public QObject
{
  Q_OBJECT
  public:

  Q_PROPERTY(unsigned KeepCounter
             READ getKeepCounter
             WRITE setKeepCounter)

  Q_PROPERTY(unsigned IterationPerLevel
             READ getIterationPerLevel
             WRITE setIterationPerLevel)

  Q_PROPERTY(unsigned Redundancy
             READ getRedundancy
             WRITE setRedundancy)

  Q_PROPERTY(unsigned IterationLimit
             READ getIterationLimit
             WRITE setIterationLimit)

  Q_PROPERTY(int targetRank
             READ getTargetRank
             WRITE setTargetRank)

  unsigned getKeepCounter() const
  { return settings.keepCounter; }

  unsigned getIterationPerLevel() const
  { return settings.iterationPerLevel; }

  unsigned getRedundancy() const
  { return settings.redundancy; }

  unsigned getIterationLimit() const
  { return settings.iterationLimit; }

  int getTargetRank() const
  { return settings.targetRank; }

  void setTargetRank(const unsigned& targetRank)
  {
    settings.targetRank = targetRank;
  }

  void setIterationLimit(const unsigned& iterationLimit)
  {
    settings.iterationLimit = iterationLimit;
  }

  void setRedundancy(const unsigned& redundancy)
  {
    settings.redundancy = redundancy;
  }

  void setKeepCounter(const unsigned& keepCounter)
  {
    settings.keepCounter = keepCounter;
  }

  void setIterationPerLevel(const unsigned& val)
  {
    settings.iterationPerLevel = val;
  }
  SmartHrir::Settings& settings;
  RunPropertiesWrapper(SmartHrir::Settings& settings)
    :settings(settings)
  {}
};
#endif // RUNPROPERTIESWRAPPER_H
