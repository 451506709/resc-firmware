#include "config.h"
#include "ch.h"
#include "hal.h"

static volatile Config config;

void config_init(void)
{
    config.encoderType = AS5x47P;
    config.commInterface = NUNCHUK;
    config.zsmMode = SINUSOIDAL;
    config.polePairs = 7;
    config.encoderZero = 221.0f;
    config.pwmFrequency = 20000.0;
    config.currentKp = 0.1;
    config.currentKi = 50.0;
    config.maxDuty = 0.5;
}

Config* config_get_configuration(void)
{
    return &config;
}
