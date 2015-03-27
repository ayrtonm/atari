#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL/SDL.h>

#define HRES			160	//scanlines
#define VRES			192	//scanlines

//colors
#define WHITE			0x00
#define GOLD			0x01
#define ORANGE			0x02
#define BRIGHT_ORANGE	0x03
#define PINK			0x04
#define PURPLE			0x05
#define PURPLE_BLUE		0x06
#define BLUE_1			0x07
#define BLUE_2			0x08
#define LIGHT_BLUE		0x09
#define TURQ			0x0A
#define GREEN_BLUE		0x0B
#define GREEN			0x0C
#define YELLOW_GREEN	0x0D
#define ORANGE_GREEN	0x0E
#define LIGHT_ORANGE	0x0F

//luminance
#define BLACK_L			0x00
#define DARK_GREY_L		0x01
#define GREY_L			0x03
#define LIGHT_GREY_L	0x06
#define WHITE_L			0x07

SDL_Surface *screen;
extern int initialize_sdl(void);
extern inline void drawplayfield_sdl(void);

#endif