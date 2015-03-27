#include <stdio.h>
#include "cpu.h"
#include "memory.h"
#include "common.h"
#include "pi.h"
#include "display.h"

int main(int argc, char *argv[])
{
char *help = "\
Atari Emulator\n\
Usage:main [options] file\n\
Options:\n\
  -h, --help    display this help and exit\n";

  if (argc == 1)
    {printf("Error: No input file\n");return 0;}
  else if (strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0)
    {printf("%s",help);return 0;}

  #ifdef INCLUDE_PI_H
  if (initialize_gpio() < 0) {return 0;}
  #endif
  if (initialize_sdl() < 0) {return 0;}
  if (loadcartridge(argv[1]) < 0)
    {printf("Error: Couldn't load file\n");return 0;}

  cpu * atari;
  atari = initialize_cpu();
  emulate_cpu(atari);
  SDL_FreeSurface(screen);
  SDL_Quit();
  return 0;
}