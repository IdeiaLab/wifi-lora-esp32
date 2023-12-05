#pragma once

#include <sys/types.h>

namespace RandomDelay
{
  u_long randomDelay(u_long lowerLimit, u_long upperLimit);
}