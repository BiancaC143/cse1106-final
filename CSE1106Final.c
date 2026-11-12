#include <stdio.h>
#include <pigpio.h>
#define PIN 17
typedef enum
{
    MIN_TEMP = 68,
    MAX_TEMP = 76
} Range;

int main(void)
{
    double temp;
    gpioInitialise();

    gpioSetMode(PIN, PI_OUTPUT);

    Printf("Enter classroom Temperature in Farenheit: ");
    scanf(" %lf", temp);

    if(temp >= MIN_TEMP && temp <= MAX_TEMP)
    {
        printf("Normal status\n");
    } 
    else 
    {
        printf("Warning status\n");
        gpioWrite(PIN, 1);
    }

    gpioTerminate();
}