#include "genetic.hpp"
#include <algorithm>


int random_integer(int start, int end)
{
    int range = (end - start) + 1;
    int random_int = start + (rand() % range);
    return random_int;
}