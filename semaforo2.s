.data
speed:
    .word 300000000               @ Valor inicial de speed

.text
.global semaforo

semaforo:
    push {lr}                     @ Guarda el registro link (LR) en la pila
    ldr r5, =speed                @ Carga la dirección de speed en r5

    mov r0, #0xC0                 @ Inicializa pos con 0xC0 (11000000)
    mov r1, #4                    @ Inicializa el contador a 4

loop_shift:
    mov r2, r0                    @ Mueve el valor de pos a r2 para disp_binary
    bl disp_binary                @ Llama a disp_binary con el valor en r2
    ldr r3, [r5]                  @ Carga el valor de speed en r3
    mov r0, r3                    @ Pasa el valor de speed a r0
    bl retardo                    @ Llama a retardo con el valor de speed
    lsr r0, r0, #2                @ Realiza un corrimiento a la derecha de 2 bits en pos
    subs r1, r1, #1               @ Decrementa el contador
    bne loop_shift                @ Si el contador no es cero, repite el bucle

    mov r0, #0xFF                 @ Establece pos a 0xFF (11111111)
    bl disp_binary                @ Llama a disp_binary con el valor en r0
    ldr r3, [r5]                  @ Carga el valor de speed en r3
    mov r0, r3                    @ Pasa el valor de speed a r0
    bl retardo                    @ Llama a retardo con el valor de speed

    mov r0, #0x00                 @ Establece pos a 0x00 (00000000)
    bl disp_binary                @ Llama a disp_binary con el valor en r0
    ldr r3, [r5]                  @ Carga el valor de speed en r3
    mov r0, r3                    @ Pasa el valor de speed a r0
    bl retardo                    @ Llama a retardo con el valor de speed

    pop {lr}                      @ Restaura el valor del registro link
    bx lr                         @ Retorna de la función
