#include <sys/types.h>
#include "RandomDelay.hpp"
#include <Arduino.h>

/// Returns a random delay in milisseconds given the lower (inclusive) and upper (exclusive) limits
/// lowerLimit has the default value of 0, while upperLimit has 1000 as default
u_long RandomDelay::randomDelay(u_long lowerLimit=0, u_long upperLimit=1000)
{
  u_long range = upperLimit - lowerLimit;
  return (rand() % range) + lowerLimit;
}

