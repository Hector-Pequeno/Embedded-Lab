#include <wiringPi.h>
#include <lcd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//USE WIRINGPI PIN NUMBERS
#define LCD_RS 25 //Register select pin
#define LCD_E 24  //Enable Pin
#define LCD_D4 23 //Data pin 4
#define LCD_D5 22 //Data pin 5
#define LCD_D6 21 //Data pin 6
#define LCD_D7 14 //Data pin 7
#define MAXTIMINGS 85
#define DHTPIN 7

void Read_File();
int lcd;
void read_dht11_dat();

void Read_File()
{
    char c[1];
    int i = 0;
    FILE *Read_file = fopen("CurrentTemperature.txt", "r"); // Write File Mode
    if (Read_file == NULL)
    {

        printf("Error! Could not Open file \n");
    }
    do
    {
        c[0 + i] = fgetc(Read_file);
        i++;
        if (feof(Read_file))
        {
            break;
        }

    } while (1);
    lcdPuts(lcd, "Temp: ");
    lcdPuts(lcd, c);
    lcdPuts(lcd, "*C ");
    fclose(Read_file);
}

int main()
{
    wiringPiSetup();
    lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);

    // Read Temperature from File
    Read_File();
    // Read HUmidity from HTC11 module
    read_dht11_dat();
}

void read_dht11_dat()
{
    uint8_t laststate = HIGH;
    uint8_t counter = 0;
    uint8_t j = 0, i;
    float f;
    char sHumedad[5];
    int dht11_dat[5] = {0, 0, 0, 0, 0};
    dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

    pinMode(DHTPIN, OUTPUT);
    digitalWrite(DHTPIN, LOW);
    delay(18);
    digitalWrite(DHTPIN, HIGH);
    delayMicroseconds(40);
    pinMode(DHTPIN, INPUT);

    for (i = 0; i < MAXTIMINGS; i++)
    {
        counter = 0;
        while (digitalRead(DHTPIN) == laststate)
        {
            counter++;
            delayMicroseconds(1);
            if (counter == 255)
            {
                break;
            }
        }
        laststate = digitalRead(DHTPIN);

        if (counter == 255)
            break;

        if ((i >= 4) && (i % 2 == 0))
        {
            dht11_dat[j / 8] <<= 1;
            if (counter > 16)
                dht11_dat[j / 8] |= 1;
            j++;
        }
    }

    if ((j >= 40) && (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF)))
    {
        //f = dht11_dat[2] * 9. / 5. + 32;
        sprintf(sHumedad, "%d", (dht11_dat[0] - 200));
        printf("Humidity = %d \n", (dht11_dat[0] - 200));
        lcdPuts(lcd, "     Hum: ");
        lcdPuts(lcd, sHumedad);
        lcdPuts(lcd, "% ");
    }
    else
    {
        sprintf(sHumedad, "%d", ((int)dht11_dat[0] - 200));
        printf("Humidity = %d \n", (dht11_dat[0] - 200));
        lcdPuts(lcd, "     Hum: ");
        lcdPuts(lcd, sHumedad);
        lcdPuts(lcd, "% ");
    }
}