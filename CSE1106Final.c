#include <stdio.h>
#include <pigpio.h>
#include <stdlib.h>
#include <ctype.h>
#define PIN 17
typedef struct
{
    double MIN_TEMP;
    double MAX_TEMP;
} Range;

double calcAverage(double TempArray[]);
void ChangeTempRange(Range *TempRange);


int main(void)
{

    double temp;
    char status[7];
    double RecTemp[20] = {0};
    char buffer[10];
    gpioInitialise();
    
    Range TempRange = {68, 76};
    FILE *StatusReport;
    int Flag = 1;
    StatusReport = fopen("StatusFile.txt","w+");
    if(StatusReport == NULL)
    {
        printf("failed to open file...");
        exit(0);
    }

    gpioSetMode(PIN, PI_OUTPUT);

    while(Flag)
    {
        gpioWrite(PIN, 0);
        char aw;

        printf("Enter classroom Temperature in Farenheit: ");
        scanf(" %lf", &temp);
        

        if(temp >= TempRange.MIN_TEMP && temp <= TempRange.MAX_TEMP)
        {
            printf("\nTemp: %lf, Status: Normal\n", temp);
            fprintf(StatusReport," %lfF     Normal     OFF",temp);
            gpioWrite(PIN, 0);
        } 
        else 
        {
            printf("\nTemp: %lf, Status: Warning\n", temp);
            fprintf(StatusReport," %lfF     Warning     ON",temp);
            gpioWrite(PIN, 1);
        }

        
        char aws;
        printf("do you want to change the temp Range? \n");
        scanf(" %c", &aws);
        if(toupper(aws) == 'Y')
        {
            ChangeTempRange(&TempRange);
        }

        

        char a;
        printf("\nAre you done modifing the temperature? Y/N \n");
        scanf(" %c", &a);

        if(toupper(a) == 'Y')
        {
            Flag = 0;
        }
    }
    fclose(StatusReport);
    gpioTerminate();
}

double calcAverage(double TempArray[]){
    double sum = 0;
    int i = 0;
    for( i; TempArray[i] != 0; i++ )
    {
        sum += TempArray[i];
        
    }
    double average = sum / i;
    return average;
}

void ChangeTempRange(Range *TempRange)
{
        double temp;
        printf("whats the new minimum range?: ");
        scanf(" %lf", &temp);
        TempRange->MIN_TEMP = temp;

        printf("whats the new maximum range?: ");
        scanf(" %lf", &temp);
        TempRange->MAX_TEMP = temp;

}














/*

#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>
#define PIN 17

int main( int argc, char* argv[])
{
    gpioInitialise();
    gpioSetMode(PIN,PI_OUTPUT);
    gpioWrite(PIN,1);
    getchar();
    gpioWrite(PIN,0);
    getchar();
    gpioTerminate();
    return 0;

}
*/
