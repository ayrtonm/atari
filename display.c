#include "display.h"

int initialize_sdl(void)
{
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {printf("Error: failed to initialize SDL_VIDEO\n");return -1;}
  screen = SDL_SetVideoMode(HRES,VRES,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
}

inline void drawplayfield_sdl(void)
{
  SDL_Flip(screen);
}