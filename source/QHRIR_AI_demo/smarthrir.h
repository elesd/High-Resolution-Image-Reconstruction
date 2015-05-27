#ifndef SMARTHRIR_H
#define SMARTHRIR_H

#include <mutationsettings.h>
class QImage;

class SmartHrir
{
public:
    struct Settings
    {
      unsigned keepCounter;
      unsigned iterationPerLevel;
      unsigned redundancy;
      unsigned iterationLimit;
      int targetRank;
    };
    struct ResultDetails
    {
      unsigned reachedIteration;
      int reachedRank;
    };
public:
    SmartHrir();

    QImage reconstruct(const QImage& input);

    MutationSettings& globalSettings()
    {
      return _globalSettings;
    }

    const MutationSettings& globalSettings() const
    {
      return _globalSettings;
    }

    Settings& settings()
    {
      return _settings;
    }

    const Settings& settings() const
    {
      return _settings;
    }

    void setUnreachableTarget();

    void setUnlimitedMode();

    const ResultDetails& details() const
    {
      return _details;
    }

private:
    MutationSettings _globalSettings;
    Settings _settings;
    ResultDetails _details;

};

#endif // SMARTHRIR_H
