.text
.global pendulo_newton
pendulo_newton:
mov r0 speed
ldr r1, =tabla
mov r2, #2   ;inicializo j=2
mov r3, #7   ;ciclo for para de 0 a 7

while_loop:
    mov r4, #0
    ldrbb r5, [r1, r4]
    do_loop:

        for_loop:
            bl disp_binary
    
            bl retardo
    
            add r4, #1
    
            cmp r4, r3
        
            blt inner_loop

    subs r2, r2, #1
    cmp r2, #0
    bge do_loop

b while_loop

.section .data
tabla:
    .byte 0x3C,0x3A,0x39,0x3A,0x3C,0x5C,0x9C,0x5C