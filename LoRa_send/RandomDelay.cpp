#include "RandomDelay.h"
#include <Arduino.h>

///Returns a random delay in milisseconds given the lower (inclusive) and upper (exclusive) limits
ulong RandomDelay::randomDelay(ulong lowerLimit=0, ulong upperLimit=1000)
{
  ulong range = upperLimit - lowerLimit;
  return (rand() % range) + lowerLimit;
}
