#include <videoDriver.h>
#include <stdint.h>
#include <font.h>
#include <screens.h>
#include <lib.h>
unsigned int WIDTH = 1024;
unsigned int HEIGHT = 768;
unsigned int PIXEL_SIZE = 3; // bytes por pixel
unsigned int DEFAULT_BG_COLOUR = 0X000000;
unsigned int DEFAULT_FONT_COLOUR = 0XFFFFFF;

// cursor basado en codigo de ayudante en practica
// codigo basado de https://wiki.osdev.org/User:Omarrx024/VESA_Tutorial

struct vbe_mode_info_structure
{
    uint16_t attributes;  // deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
    uint8_t window_a;     // deprecated
    uint8_t window_b;     // deprecated
    uint16_t granularity; // deprecated; used while calculating bank numbers
    uint16_t window_size;
    uint16_t segment_a;
    uint16_t segment_b;
    uint32_t win_func_ptr; // deprecated; used to switch banks from protected mode without returning to real mode
    uint16_t pitch;        // number of bytes per horizontal line
    uint16_t width;        // width in pixels
    uint16_t height;       // height in pixels
    uint8_t w_char;        // unused...
    uint8_t y_char;        // ...
    uint8_t planes;
    uint8_t bpp;   // bits per pixel in this mode
    uint8_t banks; // deprecated; total number of banks in this mode
    uint8_t memory_model;
    uint8_t bank_size; // deprecated; size of a bank, almost always 64 KB but may be 16 KB...
    uint8_t image_pages;
    uint8_t reserved0;

    uint8_t red_mask;
    uint8_t red_position;
    uint8_t green_mask;
    uint8_t green_position;
    uint8_t blue_mask;
    uint8_t blue_position;
    uint8_t reserved_mask;
    uint8_t reserved_position;
    uint8_t direct_color_attributes;

    uint32_t framebuffer; // puntero al buffer de la memoria de video physical address of the linear frame buffer; write here to draw to the screen
    uint32_t off_screen_mem_off;
    uint16_t off_screen_mem_size; // size of memory in the framebuffer but not being displayed on the screen
    uint8_t reserved1[206];
} __attribute__((packed));

static int getPixData(uint32_t x, uint32_t y);

static struct vbe_mode_info_structure *screenData = (void *)0x5C00; // direccion de memoria donde esta la informacion de modo video

static t_screen screens[MAX_SCREENS];
static t_screen *currentScreen;

void initializeVideo()
{
    WIDTH = screenData->width;
    HEIGHT = screenData->height;

    t_screen sc1;
    sc1.defaultBGColour = DEFAULT_BG_COLOUR;
    sc1.defaultFontColour = DEFAULT_FONT_COLOUR;
    sc1.currentX = 0;
    sc1.offset = 0;
    sc1.currentY = 0;
    sc1.width = WIDTH;
    sc1.height = HEIGHT;

    screens[SCREEN1] = sc1;
    currentScreen = &screens[SCREEN1];
}

void changeCurrentScreen(int screen_number)
{
    stopCursor();
    currentScreen = &screens[screen_number];
}

void drawPixel(int x, int y, int colour)
{
    char *currentFrame = (char *)((uint64_t)screenData->framebuffer);
    int offset = getPixData(x, y);

    currentFrame[offset] = colour & 0x0000FF;             // azul
    currentFrame[offset + 1] = (colour >> 8) & 0x0000FF;  // verde
    currentFrame[offset + 2] = (colour >> 16) & 0x0000FF; // rojo
}

static int getPixData(uint32_t x, uint32_t y)
{
    return (x + y * WIDTH) * PIXEL_SIZE;
}

void divideScreen(t_color color)
{
    for (int x = (WIDTH / 2); x < (WIDTH / 2) + CHAR_WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            drawPixel(x, y, color);
        }
    }
}
void printChar(char c, t_color fontColor, t_color bgColor, int next)
{
    unsigned char *map = charBitmap(c);

    uint32_t x = currentScreen->currentX + currentScreen->offset;
    uint32_t y = currentScreen->currentY;

    if (x + (2 * CHAR_WIDTH) - currentScreen->offset >= currentScreen->width)
    {

        y += CHAR_HEIGHT;
        newLine();
    }
    if (c == '\n')
    {
        newLine();
        return;
    }
    if (c == '\b')
    {
        deleteChar();
        return;
    }

    for (int i = 0; i < CHAR_HEIGHT; i++)
    {
        for (int j = 0; j < CHAR_WIDTH; j++)
        {
            int8_t isFont = (map[i] >> (CHAR_WIDTH - j - 1)) & 0x01; //-1 para no romper el decalaje, primera vez tengo q decalar 7
            if (isFont)
            {
                drawPixel(x, y, fontColor);
            }
            else
            {
                drawPixel(x, y, bgColor);
            }
            x++;
        }
        x = currentScreen->currentX + currentScreen->offset;
        y++;
    }

    if (next)
    {
        currentScreen->currentX += CHAR_WIDTH;
    }
}

void newLine()
{
    if (currentScreen->height - currentScreen->currentY <= CHAR_HEIGHT)
    {
        currentScreen->currentY -= CHAR_HEIGHT;

        scrollDown();
    }
    else
    {
        currentScreen->currentY += CHAR_HEIGHT;
    }

    currentScreen->currentX = 0;
}

// funcion para limpiar la pantalla
void clearScreen()
{
    for (int i = 0; i < currentScreen->height; i++)
    {
        for (int j = 0; j < currentScreen->width - 2 * CHAR_WIDTH; j++)
        {
            drawPixel(j + currentScreen->offset, i, BLACK);
        }
    }
    currentScreen->currentX = 0;
    currentScreen->currentY = 0;
}

void deleteChar()
{
    if (currentScreen->currentX == 0)
    {
        if (currentScreen->currentY == 0)
        {
            return;
        }
        currentScreen->currentY -= CHAR_HEIGHT;
        currentScreen->currentX = currentScreen->width - (2 * CHAR_WIDTH);
    }
    currentScreen->currentX -= CHAR_WIDTH;
    printChar(' ', BLACK, BLACK, 0);
}

void scrollDown()
{
    if (currentScreen == &screens[SCREEN1])
    {
        for (int i = 0; i < CHAR_HEIGHT * 2; i++)
        {
            for (int j = 0; j < HEIGHT; j++)
            {
                memcpy((void *)((uint64_t)screenData->framebuffer + j * WIDTH * PIXEL_SIZE),
                       (void *)((uint64_t)screenData->framebuffer + (j + 1) * WIDTH * PIXEL_SIZE),
                       WIDTH * PIXEL_SIZE / 2);
            }
        }
    }
    clearLine();
}

void clearLine()
{
    for (int x = 0; x <= currentScreen->width - 2 * CHAR_WIDTH; x++)
    {
        for (int y = currentScreen->currentY; y <= currentScreen->height; y++)
        {
            drawPixel(x + currentScreen->offset, y, BLACK);
        }
    }
}

void cursor()
{
    int changeDetected = 0;
    if (!changeDetected && ticks_elapsed() % 9 == 0)
    {
        changeDetected = 1;
        printChar('_', WHITE, BLACK, 0);
        if (ticks_elapsed() % 18 == 0)
        {
            printChar(' ', WHITE, BLACK, 0);
        }
    }
    if (changeDetected && ticks_elapsed() % 6 != 0)
    {
        changeDetected = 0;
    }
}
void stopCursor()
{
    printChar(' ', BLACK, BLACK, 0);
}

// PRE TP MODO TEXTO

// static uint8_t * currentVideo = (uint8_t*)0xB8000;

// void printChar(char character, int colour) {
// 	*currentVideo = character;
// 	currentVideo += 1;
// 	*currentVideo = colour;
// 	currentVideo += 1;
// }

// void printString(const char * string) {
// 	int i;
// 	for(i=0; string[i] != 0; i++){
// 		printChar(string[i], 0xF2);
// 	}
// }