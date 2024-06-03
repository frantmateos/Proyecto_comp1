//pi$gcc -c prj.c 
//pi&gcc -c autof.s
//pi%gcc prj -o autof.o -o prjfinal 
//pi%sudo ./prjfinal 


#include <stdio.h>
#include<conio.h>
#include<unistd.h>
#include <iostream>
//#include "EasyPIO.h"

int menu(void);
void autof(void);
void disp_binary(int);
void not_yet(void);
void choque(void);

void paquete(void);

//const char led[]={14,15,18,25,24,6,7};

int main (void) {
   /*pioInit();
    int i;
    for (int i; i<8; i++){
        pinMode(led[i], OUTPUT); // configure los 8 pines para los leds como salidas en main 
    }
    leds(0xFF); // Turn off leds active low

*/
    
    int choice;
    for( ; ; ){
        choice = menu();
        switch(choice){
            case 1: autof();
            break;
            case 2: choque();
            break;
            case 3: paquete();
            break; 

            case 4: not_yet();
            break; 
            case 5: return(-1);
        }
    }
}
int menu(void){
    int s;
    do{
        printf("\n Menu \n");
        printf("\n OPCION 1: Auto Fantastico \n");
        printf("\n OPCION 2: Choque \n");
        printf("\n OPCION 3: Paquete \n");
        printf("\n OPCION 4: ..\n");
        printf("\n OPCION 5: salir\n");
        scanf("%d", &s);
    }while(s<1|| s>5 );
    return s;
}



void disp_binary(int i){
    int t;

    for (t = 128; t > 0; t>>=1){
        if (i & t){
            printf("*");
        }
        else{
            printf("_");
        }
    }
    printf("\n");
}

void autof(void){
    unsigned char output;
    char t,  j=1;
    float on_time = 1;

    printf("Comienza. Toque una tecla para terminar \n");
    do{
        output = 0x80;
        for(t=0;t<8;t++){
            disp_binary(output);
            sleep(on_time);
            output = output>>1;
        }
        output = 0x01;
        for(t=0;t<6;t++){
            output = output<<1;
            disp_binary(output);
            sleep(on_time);
    
        }
    }while(--j);
    output = 0x80;
    disp_binary(output);

}

void choque(void){
    printf("Choque..\n");
    char a;
    unsigned char tabla[8] = {0x81,0x42,0x24,0x18,0x18,0x24,0x42,0x81};
    for(int i=0;i<8;i++){
        disp_binary(tabla[i]);
        sleep(1);
    }
}

void paquete(void) {
    printf("Paquete..\n");
    
    // Define los patrones de LEDs para la animación.
    unsigned char tabla[] = {
        0x03, // 00000011: dos LEDs encendidos desde la izquierda
        0x03, // 00000011: dos LEDs encendidos desde la izquierda
        0x03, // 00000011: dos LEDs encendidos desde la izquierda
        0x81, // 10000001: un LED en cada extremo
        0x42, // 01000010: un LED en cada extremo más cerca del centro
        0x24, // 00100100: un LED en cada extremo más cerca del centro
        0x18, // 00011000: LEDs centrales (chocan)
        0x1C, // 00011100: LEDs centrales, el LED del centro recibe los LEDs de la izquierda
        0x0E, // 00001110: LEDs se desplazan hacia la derecha
        0x07, // 00000111: LEDs se desplazan hacia la derecha
        0x03, // 00000011: LEDs se desplazan hacia la derecha
        0x01, // 00000001: Un LED en el extremo derecho
        0x00  // 00000000: Apagar todos los LEDs
    };
    
    // Iterar sobre la tabla y mostrar cada patrón con un retraso.
    for(int i = 0; i < sizeof(tabla) / sizeof(tabla[0]); i++) {
        disp_binary(tabla[i]);
        sleep(1); // Espera 1 segundo entre cada cambio de patrón.
    }
}

// Ejemplo de función para mostrar los bits (necesitas implementar tu propia función)
void disp_binary(unsigned char byte) {
    for (int i = 7; i >= 0; i--) {
        putchar((byte & (1 << i)) ? '1' : '0');
    }
    putchar('\n');
}


void not_yet(void){
    printf("not yet");
}

