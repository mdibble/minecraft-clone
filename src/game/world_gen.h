#pragma once

#include <noise/noise.h>

namespace Generator {

    void SetSeed(unsigned int seedVal);
    int GetXZHeight(int x, int z);
    bool IsTree(int x, int z);

}
