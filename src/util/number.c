#include "number.h"

/**
 * Makes sure that a given value stays inside of given
 * boundaries. If the given value surpasses the boundaries
 * the maximum or the minimum value is going to be returned
 */
int gated_int(int value, int min, int max)
{
  if (value >= max)
  {
    return max;
  }
  if (value <= min)
  {
    return min;
  }
  return value;
}
