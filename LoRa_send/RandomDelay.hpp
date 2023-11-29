#pragma once

#include <sys/types.h>

class RandomDelay
{
private:

  RandomDelay() { }
  static void swap(u_long & value1, u_long & value2);

public:

  static u_long randomDelay(u_long lowerLimit, u_long upperLimit);

};