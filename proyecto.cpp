//pi$gcc -c prj.c 
//pi&gcc -c autof.s
//pi%gcc prj -o autof.o -o prjfinal 
//pi%sudo ./prjfinal 
#include <string>
#include <cstdlib>
#include <conio.h> // getch
#include <vector>
#include <ncurses.h>

#define ENTER 13
#define BACKSPACE 8
#define INTENTOS 3

using namespace std;

#include <stdio.h>
#include<conio.h>
#include<unistd.h>
#include <iostream>
#include "EasyPIO.h"

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

int main (void) {

    vector<string> usuarios;
    vector<string> claves;

    usuarios.push_back("tomi");
    usuarios.push_back("pipe");
    usuarios.push_back("fran");

    claves.push_back("123");
    claves.push_back("456");
    claves.push_back("789");

    string usuario, password;

    int contador = 0;
    bool ingresa = false;

    do
    {
        system("cls");
        printf("\t\t\tLOGIN DE USUARIO\n");
        printf("\t\t\t----------------\n");
        printf("\n\tUsuario: \n");
        getline(cin, usuario);

        char caracter;

        printf("\tPassword: \n");
        caracter = getch();

        password = "";

        while (caracter != ENTER)
        {

            if (caracter != BACKSPACE)
            {
                password.push_back(caracter);
                printf("*");
            }
            else
            {
                if (password.length() > 0)
                {
                    printf("\b \b");
                    password = password.substr(0, password.length() - 1);
                }
            }

            caracter = getch();
        }

        for (int i = 0; i < usuarios.size(); i++)
        {
            if (usuarios[i] == usuario && claves[i] == password)
            {
                ingresa = true;
                break;
            }
        }

        if (!ingresa)
        {
            printf("\n\n\tEl usuario y/o password son incorrectos\n");
            cin.get();
            contador++;
        }

    } while (ingresa == false && contador < INTENTOS);

    if (ingresa == false)
    {
        printf("\n\tUsted no pudo ingresar al sistema. ADIOS"\n);
    }
    else
    {
        printf("\n\n\tBienvenido al sistema\n");
        int choice;
    
    for (int i = 0; i<8; i++){
        pinMode(led[i], OUTPUT); // configure los 8 pines para los leds como salidas en main 
    }

        unsigned long int speed = 300000000;

         for( ; ; ){
        choice = menu();
        switch(choice){
            case 1: autof(speed);
            break;
            case 2: choque(speed);
            break;
            case 3: semaforo(speed);
            break; 
            case 4: sirena(speed);
            break; 
            case 5: return(-1);
        }
    }
    }
    cin.get();

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
                leds(output);
                disp_binary(output);
                retardo(speed);
                output = output>>1;
            }
            output = 0x01;
            for(t=0;t<6;t++){
                leds(output);
                disp_binary(output);
                output = output<<1;
                retardo(speed);
        
            }
        }while(--j);
        output = 0x80;
        leds(output);
        disp_binary(output);
        
    }
    

}

void choque(unsigned long int speed){
    printf("Choque..\n");
    int vel = 1;
    char a;
    unsigned char tabla[8] = {0x81,0x42,0x24,0x18,0x18,0x24,0x42,0x81};
    while (vel == 1){
        for(int i=0;i<8;i++){
        leds(tabla[i]);
        disp_binary(tabla[i]);
        retardo(speed);
        vel = velocidad(&speed);
        }
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
            leds(tabla[i]);
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
            leds(pos) // Ejecuta las primeras cuatro secuencias
            disp_binary(pos);
            retardo(speed);
            pos >>= 2; // Realiza un corrimiento a la derecha de 2 bits
        }

        pos = 0xFF; // Valor para 11111111
        leds(pos);
        disp_binary(pos);
        retardo(speed);

        pos = 0x00; // Valor para 00000000
        leds(pos);
        disp_binary(pos);
        retardo(speed);
        vel =velocidad(&speed);
    }
    
    
}


void retardo(unsigned long int a){
    while (a)
    a--;
    
}

void leds(unsigned int a){
    int Led;
    for(int i = 0; i < 8;i++){
        Led = (a>>1)&0x01;
        digitalWrite(led[i],Led);
    }
}

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