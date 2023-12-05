#include <sys/types.h>
#include <time.h>
#include <Arduino.h>

#include "RandomDelay.hpp"

/// Retorna um long sem sinal pseudo-aleatório dados os limites inferior (incluindo) e superior (excluindo),
/// os argumentos são opcionais e têm valor padrão de 0 e 1000 respectivamente
u_long RandomDelay::randomDelay(u_long lowerLimit=0, u_long upperLimit=1000)
{
  u_long range = upperLimit - lowerLimit;
  return random(range) + lowerLimit;
}