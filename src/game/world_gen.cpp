#include "world_gen.h"

namespace Generator {

    void SetSeed(unsigned int setSeed) {
        Noise::seed(setSeed);
    }

    int GetXZHeight(int x, int z) {
        float val = Noise::simplex2(x * 0.01, z * 0.01, 2, 2, 2);
        return 4 + (val * 16);
    }

    bool IsTree(int x, int z) {
        float val = Noise::simplex2(x, z, 8, 1, 1);
        if (val >= 0.998) {
            return true;
        }
        return false;
    }
}

