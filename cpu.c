#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "memory.h"
#include "pi.h"

cpu * initialize_cpu(void)
{
  static cpu * A;
  A = calloc(sizeof(A),1);
  _S = 0xFF;
  _PC = mem[0xFFFC]+(mem[0xFFFD]<<8);
  A->running = 1;
  return A;
}

int emulate_cpu(cpu * A)
{
  int t;
  int temp16 = 0;
  uint8 temp8 = 0;
  uint8 crossing = 0;
  int period = 256;//not real period
  _CLK = period;
  for(;;)
  {
    crossing = 0;
    uint8 opcode = mem[_PC];
    if ((_PC & 0x00FF) == 0xFF) {crossing = 1;}
    _PC++;
    t = interval_t;
    switch(opcode)
    {
      #include "opcodes.h"
    }
    _CLK -= cycles[opcode];
    t -= cycles[opcode];
    while (t <= 0 && TIMER > 0)
      {TIMER -= 1;t+=interval_t;}
    if (TIMER == 0)
      {TIMER = 0xFF;oldinterval_t=interval_t;interval_t=1;}
    if(_CLK <= 0 || opcode == 0x00)
    {
      #ifdef INCLUDE_PI_H
      if (readmem(SWACNT)==0x00)
      {
        if (read_gpio(0)) {CLEAR(4,mem[SWCHA]);} else {SET(4,mem[SWCHA]);}//up
        if (read_gpio(1)) {CLEAR(5,mem[SWCHA]);} else {SET(5,mem[SWCHA]);}//down
        if (read_gpio(2)) {CLEAR(6,mem[SWCHA]);} else {SET(6,mem[SWCHA]);}//left
        if (read_gpio(3)) {CLEAR(7,mem[SWCHA]);} else {SET(7,mem[SWCHA]);}//right
        if (read_gpio(4)) {CLEAR(7,mem[INPT4]);} else {SET(7,mem[INPT4]);}//button
      }
      #endif
      _CLK += period;
      if (A->running == 0) {break;}
    }
  }
  return 0;
}