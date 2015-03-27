#ifdef INCLUDE_PI_H
#ifndef PI_H
#define PI_H
#include <wiringPi.h>
#include "common.h"

extern int initialize_gpio(void);
extern inline uint8 read_gpio(uint8);

#endif
#endif