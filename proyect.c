//pi$gcc -c prj.c 
//pi&gcc -c autof.s
//pi%gcc prj -o autof.o -o prjfinal 
//pi%sudo ./prjfinal 
//#include <ncurses.h>

#define ENTER 13
#define BACKSPACE 8
#define INTENTOS 3
#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
//#include "EasyPIO.h"

int menu(void);
void autof(unsigned long int a);
void disp_binary(int);
void choque(unsigned long int a);
void sirena(unsigned long int a);
void semaforo(unsigned long int a);

void retardo(unsigned long int a);
int velocidad(unsigned long int*speed);


const char led[]={14,15,18,23,24,25,8,7};
void leds(unsigned int a);

int main(void) {
    char usuarios[3][10] = {"tomi", "pipe", "fran"};
    char claves[3][10] = {"123", "456", "789"};
    char usuario[10], password[10];

    int contador = 0;
    int ingresa = 0;

    do {
        printf("\t\t\tLOGIN DE USUARIO\n");
        printf("\t\t\t----------------\n");
        printf("\n\tUsuario: ");
        scanf("%s", usuario);

        printf("\tPassword: ");
        for(int j =0;j<9;j++){
            char c = getchar();
            password[j] = c;
            printw("*");
        }

        for (int i = 0; i < 3; i++) {
            int user_match = 1;
            int pass_match = 1;

            for (int j = 0; j < 10; j++) {
                if (usuarios[i][j] != usuario[j]) {
                    user_match = 0;
                }
                if (claves[i][j] != password[j]) {
                    pass_match = 0;
                }
                if (usuarios[i][j] == '\0' && usuario[j] == '\0') {
                    break;
                }
                if (claves[i][j] == '\0' && password[j] == '\0') {
                    break;
                }
            }

            if (user_match && pass_match) {
                ingresa = 1;
                break;
            }
        }

        if (!ingresa) {
            printf("\n\n\tEl usuario y/o password son incorrectos\n");
            getchar(); // Limpiar el buffer del teclado
            contador++;
        }

    } while (ingresa == 0 && contador < INTENTOS);

    if (ingresa == 0) {
        printf("\n\tUsted no pudo ingresar al sistema. ADIOS\n");
    } else {
        printf("\n\n\tBienvenido al sistema\n");
        int choice;
/*
        for (int i = 0; i < 8; i++) {
            pinMode(led[i], OUTPUT);
        }*/

        unsigned long int speed = 300000000;

        for (;;) {
            choice = menu();
            switch (choice) {
                case 1:
                    autof(speed);
                    break;
                case 2:
                    choque(speed);
                    break;
                case 3:
                    semaforo(speed);
                    break;
                case 4:
                    sirena(speed);
                    break;
                case 5:
                    return -1;
            }
        }
    }
    return 0;
}
int menu(void){
    int s;
    do{
        printf("\n Menu \n");
        printf("\n OPCION 1: Auto Fantastico \n");
        printf("\n OPCION 2: Choque \n");
        printf("\n OPCION 3: Semafor \n");
        printf("\n OPCION 4: Sirena \n");
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
            printf("-");
        }
    }
    printf("\n");
}

void autof(unsigned long int speed){
    unsigned char output;
    char t,  j=1;
    float on_time = 1;
    int vel =1;
    printf("Comienza. Toque una tecla para terminar \n");
    while(vel = 1){
        do{
            output = 0x80;
            for(t=0;t<8;t++){
                //leds(output);
                disp_binary(output);
                retardo(speed);
                output = output>>1;
            }
            output = 0x01;
            for(t=0;t<6;t++){
                //leds(output);
                disp_binary(output);
                output = output<<1;
                retardo(speed);
        
            }
        }while(--j);
        output = 0x80;
        //leds(output);
        disp_binary(output);
        vel = velocidad(&speed);
        
    }
    

}

void choque(unsigned long int speed){
    printf("Choque..\n");
    int vel = 1;
    char a;
    unsigned char tabla[8] = {0x81,0x42,0x24,0x18,0x18,0x24,0x42,0x81};
    while (vel == 1){
        for(int i=0;i<8;i++){
        //leds(tabla[i]);
        disp_binary(tabla[i]);
        retardo(speed);
        }
        vel = velocidad(&speed);
    }
}
    
void sirena(unsigned long int speed){
    printf("Sirena...\n");
    int j=1;

    int vel = 1;
    unsigned char tabla[] = {0xF0, 0x0F, 0xCC, 0x33};
    while (vel == 1)
    {
        do{
            for(int i=0; i<4; i++){
            //leds(tabla[i]);
            disp_binary(tabla[i]);
            retardo(speed);
            }
            j--;
        }while(j>=0);
        vel = velocidad(&speed);
    }
    
}


void semaforo(unsigned long int speed) {
    printf("Semaforo...\n");
    int vel =1;
    int pos = 0xC0; // Inicializa con el valor para 11000000
    while(vel =1){
            for (int i = 0; i < 4; i++) {
            //leds(pos); // Ejecuta las primeras cuatro secuencias
            disp_binary(pos);
            retardo(speed);
            pos >>= 2; // Realiza un corrimiento a la derecha de 2 bits
        }

        pos = 0xFF; // Valor para 11111111
        //leds(pos);
        disp_binary(pos);
        retardo(speed);

        pos = 0x00; // Valor para 00000000
        //leds(pos);
        disp_binary(pos);
        retardo(speed);
        vel =velocidad(&speed);
    }
    
    
}


void retardo(unsigned long int a){
    while (a)
    a--;
    
}
/*
void leds(unsigned int a){
    int Led;
    for(int i = 0; i < 8;i++){
        Led = (a>>1)&0x01;
        digitalWrite(led[i],Led);
    }
}*/

int velocidad(unsigned long int* speed) {
    char c;
    ssize_t bytesRead = read(STDIN_FILENO, &c, 1);
    if (bytesRead > 0) {
        if (c == 'e') {
            return 0; // Exit the current function if 'e' is pressed
        } else if (c == 'u') { // Increase speed
            if (*speed > 100000000) { // Ensure speed doesn't go below the minimum threshold
                *speed -= 50000000;
            }
        } else if (c == 'd') { // Decrease speed
            *speed += 50000000;
        }
    }
    return 1; // Continue running
}