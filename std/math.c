#include "libc/math.h"

// TODO: sin, cos, tan, sqrt, abs functions implementation

int abs(int x) {
    return (x < 0) ? -x : x;
}