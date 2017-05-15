#include "math_util.h"

int clamp(int n, int minValue, int maxValue)
{
	if (n >= minValue && n <= maxValue)
		return n;
	else if (n < minValue)
		return minValue;
	else
		return maxValue;
}
