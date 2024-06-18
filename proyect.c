//pi$gcc -c prj.c 
//pi&gcc -c autof.s
//pi%gcc prj -o autof.o -o prjfinal 
//pi%sudo ./prjfinal 
//#include <ncurses.h>

#define ENTER 13
#define BACKSPACE 8
#define INTENTOS 3
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <fcntl.h>
#include <termios.h>
#include "EasyPIO.h"

int menu(void);
void autof(unsigned long int a);
void disp_binary(int);
void choque(unsigned long int a);
void Sirena(unsigned long int a);
void Semaforo(unsigned long int a);

void retardo(unsigned long int a);
int velocidad(unsigned long int* speed);

void sirena(unsigned long int a);
void semaforo(unsigned long int a);

const char led[]={14,15,18,23,24,25,8,7};
void leds(unsigned int a);

void setEcho(int enable) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (!enable)
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;
    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void setup_nonblocking_input() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VTIME] = 0;
    term.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    setbuf(stdin, NULL);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void restore_input_mode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
}


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
        setEcho(0); 
        scanf("%s", password);
        setEcho(1); 
        printf("\n");

        for (int i = 0; i < 3; i++) {
            if (strcmp(usuarios[i], usuario) == 0 && strcmp(claves[i], password) == 0) {
                ingresa = 1;
                break;
            }
        }

        if (!ingresa) {
            printf("\n\n\tEl usuario y/o password son incorrectos\n");
            getchar(); 
            contador++;
        }

    } while (ingresa == 0 && contador < INTENTOS);

    if (ingresa == 0) {
        printf("\n\tUsted no pudo ingresar al sistema. ADIOS\n");
    } else {
        printf("\n\n\tBienvenido al sistema\n");
        int choice;
        pioInit();

        for (int i = 0; i < 8; i++) {
            pinMode(led[i], OUTPUT);
        }

        unsigned long int speed = 100000000;

        for (;;) {
            restore_input_mode();
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
        restore_input_mode();
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

    setup_nonblocking_input();

    unsigned char output;
    char t,  j=1;
    float on_time = 1;
    int vel =1;

    printf("Comienza. Toque una tecla para terminar \n");
    while(vel == 1){
        output = 0x80;
        for(t=0;t<8;t++){
            leds(output);
            disp_binary(output);
            retardo(speed);
            output = output>>1;
            vel = velocidad(&speed);
            if(vel == 0){
                return;
            }
        }
        output = 0x01;
        for(t=0;t<6;t++){
            leds(output);
            disp_binary(output);
            output = output<<1;
            retardo(speed);
            vel = velocidad(&speed);
            if(vel == 0){
                return;
            }
    
        }
        output = 0x80;
        leds(output);
        disp_binary(output);
    }
    

}

void choque(unsigned long int speed){
    setup_nonblocking_input();
    int vel = 1;
    char a;
    unsigned char tabla[8] = {0x81,0x42,0x24,0x18,0x18,0x24,0x42,0x81};
    while (vel == 1){
        for(int i=0;i<8;i++){
        leds(tabla[i]);
        disp_binary(tabla[i]);
        retardo(speed);
        vel = velocidad(&speed);
        if(vel == 0){
            return;
        }
        }
    }
}
    
void Sirena(unsigned long int speed){
    setup_nonblocking_input();
    int vel = 1;

    unsigned char tabla[] = {0xF0, 0x0F, 0xCC, 0x33};
    while (vel == 1)
    {
        for(int i=0; i<4; i++){

            leds(tabla[i]);
            disp_binary(tabla[i]);
            retardo(speed);
            vel = velocidad(&speed);
            if(vel == 0){
                return;
            }
        }
    }
    
}


void Semaforo(unsigned long int speed) {
    setup_nonblocking_input();
    int vel = 1;
    int pos = 0xC0;

    while(vel == 1){
        for (int i = 0; i < 4; i++) {
            leds(pos); 
            disp_binary(pos);
            retardo(speed);
            pos >>= 2; 
            vel = velocidad(&speed);
            if(vel == 0){
                return;
            }
        }

        pos = 0xFF; 
        leds(pos);
        disp_binary(pos);

        pos = 0x00; 
        leds(pos);
        disp_binary(pos);

    }
}


void retardo(unsigned long int a){
    while (a)
    a--;   
}

void leds(unsigned int a){
    int Led;
    for(int i = 0; i < 8;i++){
        Led = (a>>i) & 0x01;
        digitalWrite(led[i],Led);
    }
}

int velocidad(unsigned long int* speed) {
    char c;
    ssize_t bytesRead = read(STDIN_FILENO, &c, 1);
    if (bytesRead > 0) {
        if (c == 'e') {
            return 0; 
        } else if (c == 'u') { 
            if (*speed > 50000000) { 
                *speed -= 10000000;
            }
        } else if (c == 'd') { 
            *speed += 10000000;
        }
    }
    return 1;
}
