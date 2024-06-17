.text
.global sirena
.export velocidad
.export disp_binary
.export leds
.export retardo

sirena:
    mov r0, =speed
    ldr r1, =tabla
    mov r2, #1   
    mov r3, #4   

while_loop:
    mov r4, #0
    ldrb r5, [r1, r4]      

    for_loop:
        bl leds

        bl disp_binary

        bl retardo

        add r4, #1

        cmp r4, r3
    
        blt for_loop        

b while_loop 

bx lr

.section .data
tabla:
    .byte 0xF0, 0x0F, 0xCC, 0x33