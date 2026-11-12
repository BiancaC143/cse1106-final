#include <stdio.h>
#include <pigpio.h>
#include <stdlib.h>
#include <ctype.h>
#define PIN 17
typedef struct
{
    int MIN_TEMP = 68;
    int MAX_TEMP = 76;
} Range;

int calcAverage(int TempArray[]);
int dispayTemps();
void ChangeTempRange(Range *temp_range);


int main(void)
{
    double temp;
    char status[7];
    double RecTemp[20] = {0};
    char buffer[10];
    gpioInitialise();
    Range TempRange;
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
        char aw;
        printf("do you want to change the temp Range? ");
        scanf("%d", to);
        if(aw == 'N')
        {
            Flag = 0;
        }
        else{
            ChangeTempRange(TempRange);
        }
        

        printf("Enter classroom Temperature in Farenheit: ");
        scanf(" %lf", &temp);
        

        if(temp >= TempRange.MIN_TEMP && temp <= TempRange.MAX_TEMP)
        {
            printf("Temp: %lf, Status: Normal\n", temp);
            fprintf(StatusReport,"%lfF     Normal     OFF",temp);
            gpioWrite(PIN, 0);
        } 
        else 
        {
            printf("Temp: %lf, Status: Warning\n", temp);
            fprintf(StatusReport,"%lfF     Warning     ON",temp);
            gpioWrite(PIN, 1);
        }

        fclose(StatusReport);

        
        printf("Are you done modifing the temperature? Y/N");
        scanf("%c", to);

        if(aw == 'N')
        {
            Flag = 0;
        }
    }

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
    return double;
}

void ChangeTempRange(Range *temp_range)
{
    char aw;
    printf("Do you want to change the range? Y/N");
    if(toupper(aw) == 'Y')
    {
        int temp;
        printf("whats the new minimum range?: ");
        scanf("%d", &temp);
        temp_range->MIN_TEMP = temp;

        printf("whats the new maximum range?: ");
        scanf("%d", &temp);
        temp_range->MAX_TEMP = temp;

    }

}
