#ifndef MEMORY_H
#define MEMORY_H
#include "common.h"

//#define READMEM(address) (mem[address])

uint8 mem[0x010000];

#define STACK	(_S+0x0100)
//IO ports
#define SWCHA	(0x0280)
#define SWACNT	(0x0281)
#define SWCHB	(0x0282)
#define SWBCNT	(0x0283)
#define INPT0	(0x38)
#define INPT1	(0x39)
#define INPT2	(0x3A)
#define INPT3	(0x3B)
#define INPT4	(0x3C)
#define INPT5	(0x3D)

//timer
#define INTIM	(0x0284)
#define INSTAT	(0x0285)
#define TIM1T	(0x0294)
#define TIM8T	(0x0295)
#define TIM64T	(0x0296)
#define T1024T	(0x0297)
#define TIMER mem[INTIM]

//video
#define COLUP0	(0x06)
#define COLUP1	(0x07)
#define COLUPF	(0x08)
#define COLUBK	(0x09)


extern int loadcartridge(char *);
extern inline void writemem(int,uint8);
extern inline uint8 readmem(int);

#endif