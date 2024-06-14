.text
.global sirena
sirena:
    mov r0, =speed
    ldr r1, =tabla
    mov r2, #1   ;inicializo j=1 ciclo while
    mov r3, #4   ;ciclo for 4

while_loop:
    mov r4, #0
    ldrb r5, [r1, r4]       ;carga el elemento r3 de la tabla r1, en r4
    do_loop:

        for_loop:
            bl disp_binary
    
            bl retardo
    
            add r4, #1
    
            cmp r4, r3
        
            blt inner_loop          ;branch less than

    subs r2, r2, #1

    cmp r2, #0
    bge do_loop

b while_loop ;esto capaz sacar. 

bx lr

.section .data
tabla:
    .byte 0xF0, 0x0F, 0xCC, 0x33