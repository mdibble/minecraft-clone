#include "world_gen.h"

namespace Generator {

    void SetSeed(unsigned int setSeed) {
        Noise::seed(setSeed);
    }

    int GetXZHeight(int x, int z) {
        float val = Noise::simplex2(x * 0.01f, z * 0.01f, 2, 2, 2);
        return 4 + (int)(val * 16);
    }

    bool IsTree(int x, int z) {
        float val = Noise::simplex2((float)x, (float)z, 8, 1, 1);
        if (val >= 0.998) {
            return true;
        }
        return false;
    }
}

