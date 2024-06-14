.data
tabla:
    .byte 0xF0, 0x0F, 0xCC, 0x33  @ Valores de la tabla

speed:
    .word 300000000               @ Valor inicial de speed

.text
.global sirena

sirena:
    push {lr}                    @ Guarda el registro link (LR) en la pila
    ldr r4, =tabla               @ Carga la dirección de la tabla en r4
    ldr r5, =speed               @ Carga la dirección de speed en r5
    mov r6, #1                   @ Inicializa vel en 1
    mov r7, #1                   @ Inicializa j en 1

loop_vel:
    cmp r6, #1                   @ Compara vel con 1
    bne end_function             @ Si vel no es 1, salta al final

loop_j:
    cmp r7, #0                   @ Compara j con 0
    blt end_function             @ Si j < 0, salta al final

    mov r0, r4                   @ Carga la dirección de la tabla en r0
    mov r1, #4                   @ Número de elementos en la tabla

loop_i:
    ldrb r2, [r0], #1            @ Carga el siguiente byte de la tabla en r2 y avanza r0
    mov r0, r2                   @ Pasa el valor a r0 para leds
    bl leds                      @ Llama a leds con el valor en r0
    mov r0, r2                   @ Pasa el valor a r0 para disp_binary
    bl disp_binary               @ Llama a disp_binary con el valor en r0
    ldr r3, [r5]                 @ Carga el valor de speed en r3
    mov r0, r3                   @ Pasa el valor de speed a r0
    bl retardo                   @ Llama a retardo con el valor de speed
    subs r1, r1, #1              @ Decrementa el contador i
    bne loop_i                   @ Si i no es cero, repite el bucle

    subs r7, r7, #1              @ Decrementa j
    bge loop_j                   @ Si j >= 0, repite el bucle

    ldr r0, [r5]                 @ Carga el valor de speed en r0
    bl velocidad                 @ Llama a la función velocidad
    mov r6, r0                   @ Guarda el valor retornado en vel
    b loop_vel                   @ Repite el bucle principal

end_function:
    pop {lr}                     @ Restaura el valor del registro link
    bx lr                        @ Retorna de la función
