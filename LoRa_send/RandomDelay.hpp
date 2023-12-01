#pragma once

#include <sys/types.h>

class RandomDelay
{
public:
  static u_long randomDelay(u_long lowerLimit, u_long upperLimit);

private:
  RandomDelay() { }
};