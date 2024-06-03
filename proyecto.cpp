//pi$gcc -c prj.c 
//pi&gcc -c autof.s
//pi%gcc prj -o autof.o -o prjfinal 
//pi%sudo ./prjfinal 


#include <stdio.h>
#include<conio.h>
#include<unistd.h>
#include <iostream>

//int menu(void);
void autof(void);
void disp_binary(int);
//void not_yet(void);
void choque(void);

int main() {
    //autof();
    choque();
    /*
    int choice;
    for( ; ; ){
        choice = menu();
        switch(choice){
            case 1: autof();
            break;
            case 2: choque();
            break;
            case 3:not_yet();
            break;
            case 4:not_yet();
            break; 
            case 5:return(-1);
        }
    }*/

    
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
    int on_time =1;

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
    unsigned char tabla[7] = {0x81,0x42,0x24,0x18,0x18,0x24,0x42};
    for(int i=0;i<7;i++){
        disp_binary(tabla[i]);
        sleep(1);
    }
}
