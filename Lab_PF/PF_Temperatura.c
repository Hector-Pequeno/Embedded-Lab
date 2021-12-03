#include <bcm2835.h> // Library of module
#include <stdio.h>   //
#include <stdlib.h>  //
#include <string.h>
#include <stdint.h> //
#include <time.h>

#define TC74_ADDR 77    // Direccion modulo TC74 Temperature
#define LECTURA 0       // Constante de Lectura
#define ESCRITURA 1     // Constante de Escritura
#define CLK_DIV 2500    // Frecuencia reloj
#define LONGITUD_MAX 32 // Definimos maxima longitudf
#define TRUE 1          // Definimos constante true
#define FALSE 0         // Definimos constante false

uint8_t tc74_buff[1];

typedef enum
{
    NO_ACTION,
    I2C_BEGIN,
    I2C_END
} i2c_init;

// Configuration
uint8_t init = NO_ACTION;
uint16_t clk_div = BCM2835_I2C_CLOCK_DIVIDER_148;
uint8_t slave_address = 0x00;
uint32_t len = 0;
uint8_t mode = LECTURA;
char buf[LONGITUD_MAX];
int i;
uint8_t data;
int guardados = 0;
char Archivo_Buffer[3][42];
char Archivo_Buffer_Temp[3][28];

int TC74_get();    // Obtenemos datos del modulo TC74
void delay_ms();   // Generar delay
void write_File(); //Escribir en archivo

// Obtenemos Datos del modulo TC74
int TC74_get()
{
    if (!bcm2835_init())
    {
        printf("bcm2835_init failed. Are you running as root??\n");
        return 1;
    }

    if (!bcm2835_i2c_begin())
    {
        printf("bcm2835_i2c_begin failed. Are you running as root??\n");
        return 1;
    }

    bcm2835_i2c_setSlaveAddress(TC74_ADDR);
    bcm2835_i2c_setClockDivider(CLK_DIV);

    data = bcm2835_i2c_read(tc74_buff, 1);

    bcm2835_i2c_end();
    bcm2835_close();

    return tc74_buff[0];
}
// Rutina generar delay
void delay_ms()
{
    int milli_seconds = 1000 * 100;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
    {
        if (TC74_get() > 30)
            break;
    }
}

void write_File()
{

    FILE *in_file = fopen("CurrentTemperature.txt", "w"); // Write File Mode
    if (in_file == NULL)
    {
        printf("Error! Could not Open file \n");
        exit(-1); // Error
    }
    else
    {
        fprintf(in_file, "%d", tc74_buff[0]);
        fclose(in_file);
    }
}

int main(int argc, char **argv)
{

    while (guardados < 1)
    {

        TC74_get(); // Obtenemos informacion modulo TC74
        // Desplegar informacion en Terminal
        printf("Temperature: %d°C\n", tc74_buff[0]);

        guardados++;
        delay_ms(); // Generamos Retardo
        // Almacenamos datos en archivo de texto
        write_File();
    }

    return 0;
}