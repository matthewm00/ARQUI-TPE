#ifndef SCREENS_H
#define SCREENS_H

#include <stdint.h>
#define MAX_SCREENS 4
typedef struct
{
    int defaultBGColour;
    int defaultFontColour;
    uint32_t currentX;
    uint32_t currentY;
    uint32_t offset;
    uint32_t width;
    uint32_t height;
    // uint32_t firstLine;
    // uint32_t firstLineWidth;
} t_screen;

typedef enum
{
    SCREEN1 = 0,
    SCREEN2 = 1,
    SCREEN3 = 2,
    SCREEN4 = 3
} t_currentScreen;
#endif
