#include "smarthrir.h"

extern "C"
{
#include <smart_hrir/smart_hrir.h>
#include <hrir/image_filter.h>
}

#include <QImage>
#include <datamap.hpp>
#include <limits>
#include <cassert>

SmartHrir::SmartHrir():
  _globalSettings(),
  _settings()
{
  _settings.keepCounter = 5;
  _settings.redundancy = 2;
  _settings.iterationLimit = 1;
  _settings.iterationPerLevel = std::numeric_limits<unsigned>::max();
  _settings.targetRank = std::numeric_limits<int>::max();
}

QImage SmartHrir::reconstruct(const QImage &input)
{
  typedef DataMap<unsigned char, false> ImageData_t;

  ImageData_t data(input);
  image_filter_IMG img = {data.width(),
                          data.height(),
                          data};
  _globalSettings.setUp();
  smart_hrir_SETTINGS settings;

  settings.keep_counter = _settings.keepCounter;
  settings.redundancy = _settings.redundancy;
  settings.iteration_limit = _settings.iterationLimit;
  settings.iteration_per_level = _settings.iterationPerLevel;
  settings.target_rank = _settings.targetRank;

  image_filter_IMG result =
      smart_hrir_start_algorithm(&img,
        &settings,
        &_details.reachedIteration,
        &_details.reachedRank);
  ImageData_t ret(result.width, result.height, result.content);
  return ret;
}

void SmartHrir::setUnlimitedMode()
{
  assert(_settings.targetRank !=
           std::numeric_limits<int>::max());
  _settings.iterationLimit =
      std::numeric_limits<unsigned>::max();
}

void SmartHrir::setUnreachableTarget()
{
  assert(_settings.iterationLimit !=
           std::numeric_limits<unsigned>::max());
  _settings.targetRank =
      std::numeric_limits<int>::max();
}
