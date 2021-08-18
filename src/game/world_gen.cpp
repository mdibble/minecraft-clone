#include "world_gen.h"

namespace Generator {

    void SetSeed(unsigned int setSeed) {
        Noise::seed(setSeed);
    }

    int GetXZHeight(int x, int z) {
        float val = Noise::simplex2(x * 0.015, z * 0.015, 1, 8, 10);
        return 4 + (val * 12);
    }

}

