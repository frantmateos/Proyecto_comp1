.text
-global_autof
autof:
    PUSH (R4,R5,R6,LR)          //Guarda los registros R4, R5, R6 y el enlace de retorno (LR) en la pila.
    MOV R4,#15                  //; Carga el valor 15 en el registro R4.
    LDR R5, #array              //Carga la dirección base del array en el registro R5. 

loop: LDRB R6, [R5],#1           ;Carga un byte del array en R6 y auto-incrementa R5.
      MOV R0,R6                  ;Carga el valor de R6 en R0. De nuevo
      BL disp_binary             ; Llama a la subrutina disp_binary con R0 como argumento.
      MVN R0,R6                  ; Mueve el complemento bit a bit de R6 a R0.
      BL leds                    ; Llama a la subrutina leds con R0 como argumento.
      MOV R0, #300               ; Carga el valor 300 en R0.
      BL delayMillis             ; Llama a la subrutina delayMillis con R0 como argumento.
      SUBS R4, R4 #1             ; Resta 1 de R4 y actualiza las banderas.
      BNE loop;                  ; Si R4 no es cero, salta de nuevo a la etiqueta 'loop'.
      POP(R4, R5, R6, PC)        // return from autof,  ; Restaura los registros y regresa de la subrutina.

Este es el bucle principal que itera a través del array. Para cada byte del array:

Lo carga en R6.
Llama a disp_binary para mostrar el valor en binario.
Llama a leds con el complemento bit a bit del valor.
Espera 300 milisegundos.
Decrementa el contador de bucles (R4).
Repite hasta que R4 sea 0.


.data
array:
.byte 0x80
.byte 0x40
.byte 0x20
.byte 0x10
.byte 0x08
.byte 0x04
.byte 0x02
.byte 0x01
.byte 0x02
.byte 0x04
.byte 0x08
.byte 0x10
.byte 0x20
.byte 0x30
.byte 0x40


.end
Esta sección define un array de bytes con valores que probablemente representan estados para los LEDs.
El objetivo principal de este código es crear un "jueguito" de LEDs donde los patrones de encendido y apagado de
 los LEDs cambian en función de los valores almacenados en el array. Cada byte del array representa un estado específico 
de los LEDs, y el bucle recorre estos estados, aplicándolos a los LEDs y mostrando sus complementos.