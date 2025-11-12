//=====[Libraries]=============================================================

#include "mbed.h"
#include "display.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    printf("%s\n", "Hello World");
    displayInit(DISPLAY_CONNECTION_GPIO_4BITS);
    displayCharPositionWrite(0, 0);  // Línea 1, Columna 0
    displayStringWrite("HELLO WORLD");

}