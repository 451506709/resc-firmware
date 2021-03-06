#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif
#include "utils.h"
#include "ch.h"
#include "hal.h"
#include <math.h>

/*
 * Fast approximation of sin and cos. Input is in degrees.
 */
void utils_sincos(float angle, float *sin, float *cos) {
    angle *= M_PI / 180.0;
    //always wrap input angle to -PI..PI
    while (angle < -M_PI) {
        angle += 2.0 * M_PI;
    }

    while (angle >  M_PI) {
        angle -= 2.0 * M_PI;
    }

    //compute sine
    if (angle < 0.0) {
        *sin = 1.27323954 * angle + 0.405284735 * angle * angle;

        if (*sin < 0.0) {
            *sin = 0.225 * (*sin * -*sin - *sin) + *sin;
        } else {
            *sin = 0.225 * (*sin * *sin - *sin) + *sin;
        }
    } else {
        *sin = 1.27323954 * angle - 0.405284735 * angle * angle;

        if (*sin < 0.0) {
            *sin = 0.225 * (*sin * -*sin - *sin) + *sin;
        } else {
            *sin = 0.225 * (*sin * *sin - *sin) + *sin;
        }
    }

    // compute cosine: sin(x + PI/2) = cos(x)
    angle += 0.5 * M_PI;
    if (angle >  M_PI) {
        angle -= 2.0 * M_PI;
    }

    if (angle < 0.0) {
        *cos = 1.27323954 * angle + 0.405284735 * angle * angle;

        if (*cos < 0.0) {
            *cos = 0.225 * (*cos * -*cos - *cos) + *cos;
        } else {
            *cos = 0.225 * (*cos * *cos - *cos) + *cos;
        }
    } else {
        *cos = 1.27323954 * angle - 0.405284735 * angle * angle;

        if (*cos < 0.0) {
            *cos = 0.225 * (*cos * -*cos - *cos) + *cos;
        } else {
            *cos = 0.225 * (*cos * *cos - *cos) + *cos;
        }
    }
}

bool utils_saturate_vector_2d(float *x, float *y, float max) {
    bool retval = false;
    float mag = sqrtf(*x * *x + *y * *y);
    max = fabsf(max);

    if (mag < 1e-10) {
        mag = 1e-10;
    }

    if (mag > max) {
        const float f = max / mag;
        *x *= f;
        *y *= f;
        retval = true;
    }

    return retval;
}
