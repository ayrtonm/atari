#include <stdio.h>
#include "pi.h"

int initialize_gpio(void)
{
  if (wiringPiSetup(void) == -1)
    {printf("Error: wiringPiSetup() failed\n");return -1;}
  int i = 0;
  while(i<8)
  {pinMode(i,INPUT);i++}
}

inline uint8 read_gpio(uint8 pin)
{
  uint8 x = digitalRead(pin);
  return x;
}