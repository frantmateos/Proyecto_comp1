//pi$gcc -c prj.c 
//pi&gcc -c autof.s
//pi%gcc prj -o autof.o -o prjfinal 
//pi%sudo ./prjfinal 
#include <string>
#include <cstdlib>
#include <conio.h> // getch
#include <vector>

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
void autof(void);
void disp_binary(int);
void not_yet(void);
void choque(void);
void sirena(void);
void pendulo_newton(void);

void retardo(unsigned long int a);

//const char led[]={14,15,18,25,24,6,7};

int main (void) {
   /*pioInit();
    int i;
    for (int i; i<8; i++){
        pinMode(led[i], OUTPUT); // configure los 8 pines para los leds como salidas en main 
    }
    leds(0xFF); // Turn off leds active low

*/
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
        cout << "\t\t\tLOGIN DE USUARIO" << endl;
        cout << "\t\t\t----------------" << endl;
        cout << "\n\tUsuario: ";
        getline(cin, usuario);

        char caracter;

        cout << "\tPassword: ";
        caracter = getch();

        password = "";

        while (caracter != ENTER)
        {

            if (caracter != BACKSPACE)
            {
                password.push_back(caracter);
                cout << "*";
            }
            else
            {
                if (password.length() > 0)
                {
                    cout << "\b \b";
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
            cout << "\n\n\tEl usuario y/o password son incorrectos" << endl;
            cin.get();
            contador++;
        }

    } while (ingresa == false && contador < INTENTOS);

    if (ingresa == false)
    {
        cout << "\n\tUsted no pudo ingresar al sistema. ADIOS" << endl;
    }
    else
    {
        cout << "\n\n\tBienvenido al sistema" << endl;
        int choice;
         for( ; ; ){
        choice = menu();
        switch(choice){
            case 1: autof();
            break;
            case 2: choque();
            break;
            case 3: pendulo_newton();
            break; 
            case 4: sirena();
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
        printf("\n OPCION 3: Pendulo de Newton \n");
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

void sirena(void){
    printf("Sirena...\n");
    int j=0;
    //unsigned char tabla[] = {0xF0, 0xF};
    unsigned char tabla[8] = {0xF2, 0x12, 0x12, 0xFe, 0x90, 0x90, 0x9E, 0x00};
    do{
       for(int i=0; i<8; i++){
       disp_binary(tabla[i]);
       sleep(1);
     }
     j--; 
    }while(j>=0);
    
}

void pendulo_newton(void) {
    printf("Pendulo de Newton..\n");
    int j=2;

    int tabla[8] = {0x3C,0x3A,0x39,0x3A,0x3C,0x5C,0x9C,0x5C}; 

    do{
        for(int i = 0; i < 8; i++) {
           disp_binary(tabla[i]);
           sleep(1);
        }
        j--;
    }while(j>=0);
}

void retardo(unsigned long int a){
    while (a)
    a--;
    
}