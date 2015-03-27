#include <stdio.h>
#include <sys/stat.h>
#include "memory.h"

int loadcartridge(char * filename)
{
  struct stat st;
  stat(filename,&st);
  int size = st.st_size;
  if (size % 2048 != 0)
  {
    printf("Error: Wrong file size\n");
    return -1;
  }
  uint8 cartridge[size];
  FILE *ptr = fopen(filename,"rb");
  fread(cartridge,size*sizeof(uint8),1,ptr);
  fclose(ptr);
  int i;
  for (i=0;i<0xFFFF;i++){mem[i]=0;}
  for (i=0xF000;i<(0xF000+size-1);i++)
    {mem[i]=cartridge[i-0xF000];}
  if (size==2048)
  {
    for (i=0xF000;i<0xF7FF;i++)
    {mem[i+0x0800]=mem[i];}
  }
  return 0;
}

inline void writemem(int address, uint8 value)
{
  if (address == TIM1T)
    {TIMER = (value-1);oldinterval_t=1;interval_t = 1;}
  else if (address == TIM8T)
    {TIMER = (value-1);oldinterval_t=8;interval_t = 8;}
  else if (address == TIM64T)
    {TIMER = (value-1);oldinterval_t=64;interval_t = 64;}
  else if (address == T1024T)
    {TIMER = (value-1);oldinterval_t=1024;interval_t = 1024;}
  else if (GET(12,address) == 0)
    {
      while (address > 0x1FFF)//lower memory to 0x0000-0x1FFF range
        {address -= 0x2000;}
      while (address < 0x010000 )//write and increment by 0x2000
        {
          mem[address]=value;
          address += 0x2000;
        }
    }
}

inline uint8 readmem(int address)
{
  if (address == INTIM) {interval_t=oldinterval_t;}
  return mem[address];
}