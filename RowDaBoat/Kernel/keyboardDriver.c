#include <keyboard.h>
#define BUFFER_SIZE 100

char buffer[BUFFER_SIZE] = {0};
int buff_dim = 0;

// https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html pagina de los scancodes
static const char keyCodes[KEYS][2] = {
    {0, 0}, {0, 0}, {'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'}, {'-', '_'}, {'=', '+'}, {'\b', '\b'}, {'\t', '\t'}, {'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'}, {'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'}, {'\n', '\n'}, {0, 0}, {'a', 'A'}, {'s', 'S'}, {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, {'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'}, {'\'', '\"'}, {'`', '~'}, {0, 0}, {'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, {'.', '>'}, {'/', '?'}, {0, 0}, {0, 0}, {0, 0}, {SPACE_BAR, SPACE_BAR}, {0, 0}};

int shift = 0;
int capsLock = 0;

void keyboardHandler()
{
    if (hasKeyboardKey())
    {
        unsigned int key = readKeyboard();

        // Key is pressed
        if (key >= ESC && key <= CAPS_LCK)
        {
            // Flags
            if (key == L_SHIFT || key == R_SHIFT)
            {
                shift = 1;
            }
            else if (key == CAPS_LCK)
            {
                capsLock = !capsLock;
            }
            // Is a letter
            if (IS_LETTER(keyCodes[key][0]))
            {
                if (shift)
                {
                    buffer[buff_dim++] = capsLock ? keyCodes[key][1] : keyCodes[key][0];
                }
                else
                {
                    buffer[buff_dim++] = capsLock ? keyCodes[key][0] : keyCodes[key][1];
                }
                // Is not a letter
            }
            else if (key == SPACE_BAR)
            {
                buffer[buff_dim++] = ' ';
            }
            else if (key != 0) // alphanum
            {
                buffer[buff_dim++] = shift ? keyCodes[key][1] : keyCodes[key][0];
            }
        }
        // Key is released
        else if (key == L_SHIFT_RELEASED || key == R_SHIFT_RELEASED)
        {
            shift = 0;
        }
        return;
    }
}

void checkBuffer()
{
    if (buff_dim == (BUFFER_SIZE - 1))
    {
        clearBuffer();
    }
}

void clearBuffer()
{
    buff_dim = 0;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        buffer[i] = 0;
    }
}

char *getKeyboardBuffer()
{
    return buffer;
}