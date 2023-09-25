#include "Definitions.h"

time operator ""_h(unsigned long long timeInHours)
{
    return (time)(timeInHours * HOURS_TO_TIME);
}

time operator ""_h(long double timeInHours)
{
    return (time)(timeInHours * HOURS_TO_TIME);
}