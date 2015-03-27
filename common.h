#ifndef COMMON_H
#define COMMON_H
//comment if not compiling on pi
//#define INCLUDE_PI_H

typedef unsigned char uint8;

int interval_t,oldinterval_t;

//bit manipulation
#define BIT(n) ((1) << (n))
#define SET(n,x) ((x) |= (BIT(n)))
#define CLEAR(n,x) ((x) &= ~(BIT(n)))
#define TOGGLE(n,x) ((x) ^= (BIT(n)))
#define GET(n,x) (((x) & (BIT(n))) >> (n))
#define SETX(n,x,y) {if (y == 0) {CLEAR(n,x);} \
                     else {SET(n,x);} \
                    }
#define COMPLEMENT(x) (((x) ^ 0xFF)+1)

#endif