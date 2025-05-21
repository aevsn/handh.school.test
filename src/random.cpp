#include <cstdlib>
#include <ctime>
#include "random.h"

namespace random
{

void seed()
{
    std::srand(std::time(NULL));
}

int random(int a, int b)
{
    return (std::rand() % (b - a + 1)) + a;
}

};
